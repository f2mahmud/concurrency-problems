#ifndef PRINTER_H
#define PRINTER_H

#include <vector>
#include <iostream>

#include "q1voter.h"

using namespace std;


_Cormonitor Printer {  

	struct VoterState { 	//for keeping track of voter info
        
		Voter::States state;
		TallyVotes::Tour chosenTour;
        unsigned int giftVote, pictureVote, statueVote;
		unsigned int blockCount;
		
		bool dirty = false;
		
		VoterState();

        void update( Voter::States s, TallyVotes::Tour t, unsigned int gv, unsigned int pv, unsigned int sv, unsigned int bc);
		
		void update( Voter::States s, unsigned int gv, unsigned int pv, unsigned int sv, unsigned int bc);

        friend ostream &operator<<( ostream &output, const VoterState &voterState){
	
			output << char(voterState.state);
			
			switch (voterState.state) {
				case Voter::States::Block:
				case Voter::States::Unblock:    
					cout << " " << voterState.blockCount;
					break;
				case Voter::States::Finished:  
					cout << " " << char(voterState.chosenTour.tourkind) << " " << voterState.chosenTour.groupno;
					break;
				case Voter::States::Vote:   
					cout << " " << voterState.pictureVote << "," << voterState.statueVote << "," << voterState.giftVote;
				default:
					break;
			}
			
			return output;
					
		}
		
    };

    vector<VoterState *> voterStates;  // buffer of VoterState's
	
    unsigned int voters, voterId;

    void flush();
	void main();

  public:
  
    Printer( unsigned int voters );
	
    void print( unsigned int id, Voter::States state );		//used for starting, barging, complete, failed and voter termination
	
    void print( unsigned int id, Voter::States state, TallyVotes::Tour tour );	//for after voting finished and going on tour (F t g)
	
    void print( unsigned int id, Voter::States state, TallyVotes::Ballot ballot );	//Used when voting (Vpsg)
	
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );	//For the blocking and unblocking parts (Bn,Un)
	
	~Printer();
	
};

#endif