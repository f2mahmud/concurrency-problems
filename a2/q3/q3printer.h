#include <vector>
#include <iostream>
#include "PRNG.h"

using namespace std;

PRNG prng(getpid());

class Printer {

	static const char TAB = '\t';
	
	bool schmilblick = false;
  
	unsigned int numberOfPlayers, cardsLeft, numberOfCards;

	struct PlayerMove{
	
		static const char TO_THE_LEFT = '<';
    	static const char TO_THE_RIGHT = '>';
    	static const char PLAYER_TERMINATED = 'X';
    	static const char GAME_OVER = '#';
    	static const char DRINK = 'D';
    	
    	unsigned int cardsRemaining, playersLeft;
		int cardsTaken;
    	int playerTerminated = -1;
    	bool schmilblick = false;
    	
    	PlayerMove(unsigned int cardsTaken, unsigned int cardsRemaining, unsigned int playersLeft);
    	
    	//PlayerMove(unsigned int cardsTaken, unsigned int cardsRemaining, unsigned int playersLeft);
    	
    	friend ostream &operator<<(ostream &output, const PlayerMove move){	//TODO::Complete
    		if(move.schmilblick){
    			output << PlayerMove::DRINK;
    		}else if(move.cardsTaken == -1){		//GAME OVER
    			output << PlayerMove:: GAME_OVER;
    		}
    		
    		return output;
    	}
		
	};
	
	vector<PlayerMove *> playerMoves;
	
	void init();
	void printMoves();

	   
  public:
    
    Printer( const unsigned int NoOfPlayers, const unsigned int NoOfCards );
    
    void prt( unsigned int id, int took, int RemainingPlayers );
	
};