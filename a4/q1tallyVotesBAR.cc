#include "q1tallyVotes.h"
#include "q1printer.h"

TallyVotes::TallyVotes( unsigned int votes, unsigned int group, Printer & printer ) :
	groupSize(group), p(printer), uBarrier(group) {}
	
void TallyVotes::done(){
	voters -= 1;
	if(voters < groupSize){
		quorum = true;
		uBarrier::reset(uBarrier::waiters());
	}
}
	
void TallyVotes::block(){
	p.print(currentId, Voter::States::Block, uBarrier::waiters()+1);
	uBarrier::block();
}

void TallyVotes::last(){
	//once group is ready get the decision and print the complete message
	setWinningTour();
	p.print(currentId, Voter::States::Complete);
}

TallyVotes::Tour TallyVotes::vote( unsigned int id, Ballot ballot ) {
	
	if(quorum){
		_Throw Failed();
	}
	
    shopVotes += ballot.giftshop;
	pictureVotes += ballot.picture;
    statueVotes += ballot.statue;
	
    currentId = id;
	
	uBarrier::block();
	
	if(quorum){
		_Throw Failed();
	}
	
	if (uBarrier::waiters() + 1 < groupSize) {	// if not last task print unblock
		p.print(id, Voter::States::Unblock, uBarrier::waiters());
	}
	
	return chosenTour;	// return the tour that won
}
