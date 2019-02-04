#include "q3player.h"

using namespace std;

unsigned int Player::REMAINING_PLAYERS;

void Player::start(Player &lp, Player &rp){
	playerOnLeft = &lp;
	playerOnRight = &rp;
	resume();
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

Player::Player(Printer &printer, unsigned int id): printer(printer), playerId(id){}

void Player::passToNextPlayer(){
	if(cardsLeft % 2 == 0){
		playerOnRight->play(cardsLeft);
	}else{
		playerOnLeft->play(cardsLeft);
	}	
}

void Player::knockedPlayerMove(){
	try{
		_Enable{		//TODO::Look into this later
			while(true){
				passToNextPlayer();
			}
		}
	}_CatchResume( Schmilblick &s){
		_Resume s _At *playerOnRight;
		playerOnRight->play(cardsLeft);
	}
}

void Player::main(){
	suspend();

	try{
		_Enable{
			while(Player::REMAINING_PLAYERS > 1){
				unsigned int cardsTaken = prng(1,8);
				unsigned int initialCardCount = cardsLeft;
				
				if(cardsLeft < cardsTaken){
					cardsTaken = cardsLeft;
				}
				
				cardsLeft -= cardsTaken;
				
				printer.prt(playerId, cardsTaken, Player::REMAINING_PLAYERS);
				
				if(initialCardCount % DEATH_DECK_DIVISOR == 0){		//TODO::Need to use enum
					if(cardsLeft == 0){
						return; //TODO:: Comeback to this
					}else{
						players(Player::REMAINING_PLAYERS - 1);
						knockedPlayerMove();
					}	
				}
				
				if(cardsLeft == 0){
					return;
				}
				
				if(prng(1,10) == 1){		//SCHMILBLICK!
					_Resume Schmilblick(playerId) _At *playerOnRight;
					playerOnRight->play(cardsLeft);
				}
				
				passToNextPlayer();
			
			}
			printer.prt(playerId,-1, Player::REMAINING_PLAYERS);
		}
	
	}_CatchResume(Schmilblick &s){
		drink();
		if(s.playerId != playerId){
			_Resume s _At *playerOnRight;
			playerOnRight->play(cardsLeft);
		}
	}
	
}

