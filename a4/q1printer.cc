
#include <iostream>
#include "q1printer.h"

using namespace std;

Printer::VoterState::VoterState(){}

void Printer::VoterState::update( Voter::States s, unsigned int gv, unsigned int pv, unsigned int sv, unsigned int bc) {
	state = s;
	giftVote = gv;
	pictureVote = pv;
	statueVote = sv;
	blockCount =bc;
	dirty = true;
}


void Printer::VoterState::update( Voter::States s, TallyVotes::Tour t, unsigned int gv, unsigned int pv, unsigned int sv, unsigned int bc) {
	chosenTour = t;
	update(s,gv,pv,sv,bc);
}

Printer::Printer( unsigned int voters ) : voters(voters) {
	
	for (unsigned int i = 0; i < voters; i++) {	// printing name of voters
        cout << "V" << i << (i != voters-1 ? '\t' : '\n');
    }

    for (unsigned int i = 0; i < voters; i++) {	//divider for each voter
        cout << "*******" << (i != voters-1 ? '\t' : '\n');
		voterStates.push_back(new VoterState());
    }

    resume();	// to main of coroutine
	
}

void Printer::flush() {

    // print moves
    for (unsigned int i = 0; i < voters; i+=1) {
        if (voterStates[i]->dirty) {
            cout << *voterStates[i];
            voterStates[i]->dirty = false;
        } 
        cout << '\t';
    }
    cout << '\n';
}

void Printer::main() {
	suspend(); 	//initial suspend

    for ( ;; ) {
        if (voterStates[voterId]->dirty) {
            flush();
        }	
        suspend();
    }
}

//Used for S/b/C/X/T
void Printer::print( unsigned int id, Voter::States state ) {
    voterId = id;
	if(voterStates[id]->dirty){
		resume();	//head back to main
	}
    voterStates[id]->update(state, 0, 0, 0, 0);	//update values
}

//Used for Ftg
void Printer::print( unsigned int id, Voter::States state, TallyVotes::Tour tour ) {
    voterId = id;
	if(voterStates[id]->dirty){
		resume();	//head back to main
	}
    voterStates[id]->update(state,tour, 0, 0, 0, 0);
}

//Used for  Vpsg
void Printer::print( unsigned int id, Voter::States state, TallyVotes::Ballot ballot ) {
    voterId = id;
	if(voterStates[id]->dirty){
		resume();	//head back to main
	}
    voterStates[id]->update(state, ballot.picture, ballot.statue, ballot.giftshop, 0);		//update
}

//Used for Un/Bn
void Printer::print( unsigned int id, Voter::States state, unsigned int numBlocked ) {
    voterId = id;
	if(voterStates[id]->dirty){
		resume();	//head back to main
	}
    voterStates[id]->update(state, 0, 0, 0, numBlocked);	//update
}

Printer::~Printer() {
	flush();
	//Printing final lines
	cout << "*****************" << endl;
	cout << "All tours started" << endl;
	
	for(unsigned int i = 0; i < voters; i+=1){
		delete voterStates[i];
		voterStates[0] = nullptr;
	}
	
}
