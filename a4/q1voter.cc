#include "q1voter.h"
#include "q1printer.h"

#include "MPRNG2.h"

extern MPRNG mprng;
	
Voter::Voter( unsigned int id, unsigned int nvotes, TallyVotes & voteTallier, Printer & printer ): id(id), maxTrips(nvotes), voteTallier(voteTallier), p(printer){} 

 TallyVotes::Ballot Voter::cast() {        // cast 3-way vote
        // O(1) random selection of 3 items without replacement using divide and conquer.
        static const unsigned int voting[3][2][2] = { { {2,1}, {1,2} }, { {0,2}, {2,0} }, { {0,1}, {1,0} } };
		
        unsigned int picture = mprng( 2 ), statue = mprng( 1 );
		
        return (TallyVotes::Ballot){ picture, voting[picture][statue][0], voting[picture][statue][1] };
		
}

void Voter::main(){
	
	try{
		
		yield(mprng(19));
		
		for(unsigned int i = 0; i < maxTrips; i+=1){
			p.print(id, States::Start);			//print start
			yield(4);
			TallyVotes::Ballot votes = cast();
			p.print(id, States::Vote, votes);
			TallyVotes::Tour finalDecision = voteTallier.vote(id, votes);	//sending vote to tallier
			yield(4);
			p.print(id, States::Finished, finalDecision );	//print finish
		}
		
		voteTallier.done();
		
	}catch(TallyVotes::Failed &f){
		p.print(id, States::Failed);
	}_Finally{
		p.print(id, States::Terminated);
	}
}


