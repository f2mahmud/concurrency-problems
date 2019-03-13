#include <unistd.h> 
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "q1tallyVotes.h"
#include "q1printer.h"
#include "q1voter.h"
#include "MPRNG2.h"

using namespace std;

MPRNG mprng;

bool convert( unsigned int & val, char * buffer ) {		// convert C string to integer
    std::stringstream ss( buffer );			// connect stream and buffer
    string temp;
    ss >> dec >> val;					// convert integer from buffer
    return ! ss.fail() &&				// conversion successful ?
	! ( ss >> temp );				// characters after conversion all blank ?
} // convert



int main( int argc, char * argv[] ) {

    unsigned int voters = 6;
	unsigned int groupSize = 3;
	unsigned int maxTrips = 1;
	unsigned int seed = getpid();
	unsigned int processors = 1;
	
    try {
		
        switch ( argc ) {
            case 6:
				if ( (!convert( processors ,argv[5]) && strcmp(argv[5], "d") != 0 ) || processors <= 0 ) {
					throw 1;
				} 
            case 5:
				if ( (!convert(seed,argv[4]) && strcmp(argv[4], "d") != 0 ) || seed <= 0 ) {
					throw 1;
				} 
            case 4:
                if ( (!convert(maxTrips,argv[3]) && strcmp(argv[3], "d") != 0 ) || maxTrips <= 0 ) {
					throw 1;
				} 
			case 3:
				if ( (!convert(groupSize,argv[2]) && strcmp(argv[2], "d") != 0 ) || groupSize <= 0 ) {
					throw 1;
				} 
			case 2:
				if ( (!convert(voters,argv[1]) && strcmp(argv[1], "d") != 0 ) || voters <= 0 ) {
					throw 1;
				} 
			case 1:
				break;
            default:					// wrong number of options
                throw 1;
        } // switch

    } catch( ... ) {
        cerr << "Usage: "<< argv[0] << " vote [ voters | ’d’ [ group | ’d’ [ votes | ’d’ [ seed | ’d’ [ processors | ’d’ ] ] ] ] ]" << '\n';
        exit( EXIT_FAILURE );				// TERMINATE

    } // try

	uProcessor p[processors - 1]; // number of kernel threads

    mprng.set_seed(seed);  

	Printer printer(voters);
	
	TallyVotes tallyVotes(voters,groupSize, printer);
	
	Voter *votersArr[voters];
	
	//create the voters
	for(unsigned int i = 0; i < voters; i+=1){
		votersArr[i] = new Voter(i, maxTrips, tallyVotes, printer);
	}
	
	//vanquish the voters
	for (unsigned int i = 0; i < voters; i++) {
        delete votersArr[i];
    }  
	
}




