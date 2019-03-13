#include "q1tallyVotes.h"
#include "q1printer.h"

TallyVotes::TallyVotes( unsigned int voters, unsigned int group, Printer & printer ): voters(voters), groupSize(group), p(printer) {}

void TallyVotes::done(){
		ownerLock.acquire();
		voters -= 1;
		if(voters < groupSize){
			quorum = true;
			bargeLock.broadcast();
			groupFull =false;
		}
		ownerLock.release();
}
	
TallyVotes::Tour TallyVotes::vote( unsigned int id, Ballot ballot ) {
    
	try{
		
		ownerLock.acquire();
		
		if(quorum){
			_Throw Failed();
		}
		
		if (groupFull) {
			bargingGroupSize += 1;
			p.print(id, Voter::States::Barging);
			bargeLock.wait(ownerLock);			//wait while current group is being taken care of
			bargingGroupSize -=1;	//since one barger moved out from the lock
		}
		
		if(quorum){
			_Throw Failed();
		}
		
		//taking votes into count to make final decision
		shopVotes += ballot.giftshop;
		pictureVotes += ballot.picture;
		statueVotes += ballot.statue;
		votes += 1; 
			
		if (votes == groupSize) {    // group is ready
			groupFull = true;
			votes -= 1;
			setWinningTour();
			p.print(id, Voter::States::Complete);
			//reset
			shopVotes = 0;
			pictureVotes = 0;
			statueVotes = 0;
			syncLock.broadcast();  // call out the whole group
		} else {    // if not the last member of the group
			p.print(id, Voter::States::Block, votes);
			syncLock.wait(ownerLock);		//waiting till group is ready
			votes -= 1;
			p.print(id, Voter::States::Unblock, votes);
		}
		
		//Allowing one voter to get out of bargeLock for one Voter getting out. This makes sure that there are not barging groups
		bargeLock.signal();
		groupFull = !bargeLock.empty(); // allow voters to enter directly

		return chosenTour;  // return winning tour
		
	}_Finally{
		ownerLock.release();
	}
}
