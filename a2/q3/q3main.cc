#include "q3player.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
	
	string arg;
	
	int seed;
	
	unsigned int games = 5;
	unsigned int numberOfPlayers;
	unsigned int numberOfCards;
	
	if(argc < 5){
		seed = getpid();
		prng.seed(seed);
		numberOfPlayers = prng(2,10);
		numberOfCards = prng(10, 200);
	}
	
	try {
		switch ( argc ) {
			case 5:
				//For seed
				arg = argv[4];
				if(arg != "d" && stoi(arg) > 0){
					seed = stoi(arg);
					prng.seed(seed);		
				}else if(arg != "d"){
					throw 1;
				}
			case 4: 
				//For number of cards
	    		arg = argv[3];
	    		if(arg != "d" && stoi(arg) > 0 ){
	    			numberOfCards = stoi(arg);
	    		}else if(arg != "d"){
	    			throw 1;
	    		}
	  		case 3:
	  			// For players
	  			arg = argv[2];
	  			if(arg != "d" && stoi(arg) > 1){
	  				numberOfPlayers = stoi(arg);
	  			}else if(arg != "d"){
	  				throw 1;
	  			}
	  		case 2:
	  			//For games
	   			arg = argv[2];
	  			if(arg != "d" && stoi(arg) > -1){
	  				games = stoi(arg);
	  			}else if(arg != "d"){
	  				throw 1;
	  			}
	   		case 1:					// defaults
	    		break;
	  		default:					// wrong number of options
	    		throw 1;
		} // switch
    } catch( ... ) {
		cerr << "Usage: " << argv[0]
			<< " [ games | 'd' (games >= 0)" 
			<< " [ players | 'd' (players >= 2)"
			<< " [ cards | 'd' (cards > 0)"
			<< " [ seed | 'd' (seed > 0) ] ] ] ]" << endl;
		exit( EXIT_FAILURE );				// TERMINATE
    } // try/catch block
    
    vector<Player *> currentGamePlayers;
    int startingPlayerIndex;
	
	Printer printer = Printer(numberOfPlayers, numberOfCards);
    
	// Let the games begin!
	for (int i = 0 ; i < games; i++){
	
		//Setting up game environment
		Player::players(numberOfPlayers);	
		startingPlayerIndex = prng(1,numberOfPlayers) - 1;
		
	
		//Creating players for current game
		for(int j = 0 ; j < numberOfPlayers; j++){
			currentGamePlayers.push_back(new Player(printer,j));
		}
		
		//Assigning positions and initializing coroutines
		int leftPlayerIndex, rightPlayerIndex;
		
		for(int j = 0 ; j < numberOfPlayers; j++){
			leftPlayerIndex = (j + (numberOfPlayers -1)) % numberOfPlayers;
			rightPlayerIndex = (j + 1) % numberOfPlayers;
			currentGamePlayers[j] -> start(*currentGamePlayers[leftPlayerIndex], *currentGamePlayers[rightPlayerIndex]); 
		}
		
		currentGamePlayers[startingPlayerIndex]->play(numberOfCards);
			
		//GG:: Current game cleanup	
		for(int j = 0; j < numberOfPlayers; j++){
			delete currentGamePlayers[j];
		}
		currentGamePlayers.clear();
				
		if(i != games){
			cout << '\n' << '\n';
		}
	
	
	} //for loop for the games    
    
	
}





