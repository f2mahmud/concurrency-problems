#include "q3printer.h"

using namespace std;

Printer::PlayerMove::PlayerMove(int cardsTaken, unsigned int cardsRemaining, 
	unsigned int playersLeft, bool drink): cardsTaken(cardsTaken),cardsRemaining(cardsRemaining),
					playersLeft(playersLeft), schmilblick(drink){}


void Printer::init(){
	cardsLeft = numberOfCards;
	cout << "Players: " << numberOfPlayers << '\t' << "Cards: " << numberOfCards << '\n';
	for(int i = 0 ; i < numberOfPlayers - 1 ; i++){
		cout << 'P' << i << '\t';
	}
	cout << 'P' << numberOfPlayers-1 << '\n';
}

Printer:: Printer( const unsigned int NoOfPlayers, const unsigned int NoOfCards):
	numberOfPlayers(NoOfPlayers), numberOfCards(NoOfCards){
		playerMoves = vector<PlayerMove *>(NoOfPlayers);
	init();
}

void Printer::printMoves(){
	
	for(int i = 0; i < numberOfPlayers; i++){
		if(playerMoves[i] == nullptr){
			cout << '\t';
			continue;
		}
		cout << *(playerMoves[i]);
		delete playerMoves[i];
		if(schmilblick){
			playerMoves[i] = new Printer::PlayerMove(0, 0, 0, true);
			continue;
		}
		playerMoves[i] = nullptr;
	}
	
	cout << endl;
	
	if(schmilblick && cardsLeft != 0){
		for(int i = 0; i < numberOfPlayers; i++){
			if(playerMoves[i] != nullptr){
				cout << *(playerMoves[i]);
				delete playerMoves[i];
				playerMoves[i] = nullptr;
			}
		}
		schmilblick = false;
		cout << endl;
	}
	
}
	
void Printer::prt(unsigned int id, int took, int RemainingPlayers){

	if(took == 0){
		schmilblick = true;
		return;
	}
	
	cardsLeft -= took;
	
	playerMoves[id] = new Printer::PlayerMove(took, cardsLeft, RemainingPlayers, false);
	
	if(cardsLeft == 0 || id == numberOfPlayers - 1){
		printMoves();
	}

}

