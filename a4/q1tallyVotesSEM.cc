#include "q1tallyVotes.h"
#include "q1printer.h"

TallyVotes::TallyVotes( unsigned int voters, unsigned int group, Printer & printer ) :
    voters(voters), ownerSem(1), syncSem(0), bargeSem(0), groupSize(group), p(printer) {}

void TallyVotes::done(){
		voters -= 1;
		if(voters < groupSize){
			quorum = true;
			groupFull = false;
			bargeSem.V(bargingGroupSize);
		}
}

TallyVotes::Tour TallyVotes::vote( unsigned int id, Ballot ballot ) {
	
	try{
		ownerSem.P();
		
		if(quorum){
			_Throw Failed();
		}
		
		if (groupFull) {
			bargingGroupSize += 1;
			p.print(id, Voter::States::Barging);
			bargeSem.P(ownerSem);
			bargingGroupSize -= 1;
		} 

		if(quorum){
			_Throw Failed();
		}
		
		//taking votes into count to make final decision
		shopVotes += ballot.giftshop;
		pictureVotes += ballot.picture;
		statueVotes += ballot.statue;
		votes += 1;

		if (votes == groupSize) {	// group is ready
			groupFull = true;
			votes -= 1;
			setWinningTour();
			p.print(id, Voter::States::Complete);
			//reset
			shopVotes = 0;
			pictureVotes = 0;
			statueVotes = 0;
			syncSem.V(groupSize);	// broadcast blocked voters TODO::need to calculate value
		} else {	// if not last voter in group
			p.print(id, Voter::States::Block, votes);
			syncSem.P(ownerSem);	// wait till group is ready
			votes -= 1;
			p.print(id, Voter::States::Unblock, votes);
		}

		if (bargeSem.counter() < 0) {
			bargeSem.V();
		}
		
		groupFull = !bargeSem.empty();		// allow extra voters in once there are no more bargers
		
		return chosenTour;	// return winning tour
	
	}_Finally{
		ownerSem.V();
	}
}