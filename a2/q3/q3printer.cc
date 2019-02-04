#include "q3printer.h"

using namespace std;

Printer::PlayerMove::PlayerMove(unsigned int cardsTaken, unsigned int cardsRemaining, unsigned int playersLeft)


void Printer::init(){
	cout << "Players: " << numberOfPlayers << Printer::TAB << "Cards: " << numberOfCards << '\n';
	for(int i = 0 ; i < numberOfPlayers - 1 ; i++){
		cout << 'P' << i << '\t';
	}
	cout << 'P' << numberOfPlayers-1 << '\n';
}

Printer:: Printer( const unsigned int NoOfPlayers, const unsigned int NoOfCards):
	numberOfPlayers(NoOfPlayers), numberOfCards(NoOfCards){
	init();
}

void Printer::printMoves(){
	
	int indexOfLastMove = numberOfPlayers-1;
	
	while(playerMoves[indexOfLastMove] != nullptr){
		indexOfLastMove -= 1;
	}
	
	for(int i = 0; i <= indexOfLastMove; i++){
		if(playerMoves[i] != nullptr){
			cout << *(playerMoves[i]);
			delete playerMoves[i];
			playerMoves[i] = nullptr;
		}
		cout << Printer::TAB;
	}
	
	cout << endl;
	
}
	
void Printer::prt(unsigned int id, int took, int RemainingPlayers){

	if(schmilblick && took != 0){
		schmilblick = false;			
	}else if(!schmilblick && took == 0){
		printMoves();
		schmilblick = true;
	}
	
	if(playerMoves[id] != nullptr){
		printMoves();
	}
	
	playerMoves[id] = new Printer::PlayerMove(took, numberOfCards - took, RemainingPlayers);
	cardsLeft -= took;
	
	if(RemainingPlayers == 1 || cardsLeft == 0){
		printMoves();
	}

}

