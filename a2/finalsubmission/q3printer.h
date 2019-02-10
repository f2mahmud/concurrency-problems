#include <vector>
#include <iostream>

using namespace std;

class Printer {
	
	bool schmilblick = false;
  
	unsigned int numberOfPlayers, cardsLeft, numberOfCards;

	struct PlayerMove{
	
		static const char TO_THE_LEFT = '<';
    	static const char TO_THE_RIGHT = '>';
    	static const char PLAYER_TERMINATED = 'X';
    	static const char GAME_OVER = '#';
    	static const char DRINK = 'D';
		static const char TAB = '\t';
    	
    	unsigned int cardsRemaining, playersLeft;
		int cardsTaken;
    	bool schmilblick = false;
    	
    	PlayerMove(int cardsTaken, unsigned int cardsRemaining, unsigned int playersLeft, bool drink);
    	
    	
    	friend ostream &operator<<(ostream &output, const PlayerMove &move){	//TODO::Complete
			//Nobody wins
			if(move.playersLeft == 0 && move.cardsRemaining > 0){
				output << PlayerMove::GAME_OVER << move.cardsRemaining << PlayerMove::GAME_OVER << PlayerMove::TAB;
				return output;
			}
				
			//Schmilblick
			if(move.schmilblick){
    			output << PlayerMove::DRINK << PlayerMove::TAB;
				return output;
    		}
			
			//Normal round
			output << move.cardsTaken << ':' << move.cardsRemaining;
			if(move.cardsRemaining == 0){
					output << PlayerMove::GAME_OVER;
			}else if(move.cardsRemaining % 2 == 0 ){
				output << PlayerMove::TO_THE_RIGHT;
			}else{
				output << PlayerMove::TO_THE_LEFT;
			}
			
			if(move.playersLeft == -1){
				output << PlayerMove::PLAYER_TERMINATED;
			}
			output << PlayerMove::TAB;
			
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