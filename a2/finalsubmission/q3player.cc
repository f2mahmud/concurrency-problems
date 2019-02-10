#include "q3player.h"

using namespace std;

unsigned int Player::REMAINING_PLAYERS;

void Player::start(Player &lp, Player &rp){
	playerOnLeft = &lp;
	playerOnRight = &rp;
}

void Player::play(unsigned int dec){
	cardsLeft = dec;
	resume();
}

void Player::drink(){
	printer.prt(playerId, 0, Player::REMAINING_PLAYERS);
}

void Player:: players(unsigned int num){
	Player::REMAINING_PLAYERS = num;
}

Player::Player(Printer &printer, unsigned int id): printer(printer), playerId(id){
	resume();
}

void Player::passToNextPlayer(){
	if(cardsLeft % 2 == 0){
		playerOnRight->play(cardsLeft);
	}else{
		playerOnLeft->play(cardsLeft);
	}	
}

void Player::main(){
	suspend();

	try{
		_Enable{
			
			while(Player::REMAINING_PLAYERS > 1){
				
				//Regular play
				unsigned int cardsTaken = prng(1,8);
				unsigned int initialCardCount = cardsLeft;	
				
				if(cardsLeft < cardsTaken){
					cardsTaken = cardsLeft;
				}
				
				cardsLeft -= cardsTaken;
				
				//Check for Death deck
				if(initialCardCount % DEATH_DECK_DIVISOR == 0){		//TODO::Need to use enum
					players(Player::REMAINING_PLAYERS - 1);
					if(cardsLeft != 0){
						playerOnLeft->start(*playerOnLeft->playerOnLeft, *playerOnRight);
						playerOnRight->start(*playerOnLeft, *playerOnRight->playerOnRight);
					}
					printer.prt(playerId, cardsTaken, -1);
					passToNextPlayer();
				}
				
				//SCHMILBLICK!
				if(prng(1,10) == 1){		
					_Resume Schmilblick(playerId) _At *playerOnRight;
					playerOnRight->play(cardsLeft);
				}
				
				//Everything went as normal
				printer.prt(playerId, cardsTaken, Player::REMAINING_PLAYERS);
				passToNextPlayer();
			
			}
		}
	
	}_CatchResume(Schmilblick &s){
		drink();
		if(s.playerId != playerId){
			_Resume s _At *playerOnRight;
			playerOnRight->play(cardsLeft);
		}
	}
	
}


