#ifndef VOTER_H
#define VOTER_H

#include "q1tallyVotes.h"

_Cormonitor Printer;

_Task Voter {
	
	unsigned int id;
	unsigned int maxTrips;
	
	TallyVotes &voteTallier;
	
	Printer &p;
	
	void main();
	
    TallyVotes::Ballot cast();
	
  public:
  
    enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U', Barging = 'b',
                   Complete = 'C', Finished = 'F', Failed = 'X', Terminated = 'T' };
				   
    Voter( unsigned int id, unsigned int nvotes, TallyVotes & voteTallier, Printer & printer );
	
};

#endif
