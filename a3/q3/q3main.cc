#include <iostream>
#include <fstream>
#include "MPRNG2.h"
#include "q3buffer.h"
#include "q3producer.h"
#include "q3consumer.h"

using namespace std;

MPRNG mprng;

int main( int argc, char * argv[] ) {

    unsigned int cons = 5;
	unsigned int prods = 3;
	unsigned int produce = 10;
	unsigned int bufferSize = 10;
	unsigned int delay;
	
    try {
		
        switch ( argc ) {
            case 6:
				delay = stoi(argv[5]);
            case 5:
                bufferSize = stoi(argv[4]);
            case 4:
                produce = stoi(argv[3]);;
			case 3:
				prods = stoi(argv[2]);;
			case 2:
				cons = stoi(argv[1]);
				break;
			case 1:
				delay = cons+prods;
				break;
            default:					// wrong number of options
                throw 1;
        } // switch

    } catch( ... ) {
        cerr << "Usage: "<< argv[0] << " buffer [ Cons [ Prods [ Produce [ BufferSize [ Delays ] ] ] ] ]" << '\n';
        exit( EXIT_FAILURE );				// TERMINATE

    } // try

#ifdef __U_MULTI__
	uProcessor p[3] __attribute__(( unused )); // create 3 kernel thread for a total of 4
#endif // __U_MULTI__

	//Create the consumers, producers and buffers
	BoundedBuffer<TYPE> buffer(bufferSize);// = new BoundedBuffer(size);
	
	Producer **producers = new Producer*[prods];
	
	for(unsigned int i = 0; i < prods; i++){
		producers[i] = new Producer (buffer, produce, delay);
	}
	
	int sum = 0;
	Consumer **consumers = new Consumer*[cons];
	
	for(unsigned int i = 0; i < cons; i++){
		consumers[i] = new Consumer (buffer, delay, SENTINEL, sum);
	}
	
	//Destroy the consumers producers and buffers
	for(unsigned int i = 0; i < prods; i++){
		delete producers[i];
	}
	
	for(unsigned int i = 0; i < cons; i++){
		buffer.insert(SENTINEL);
	}
	
	for(unsigned int i = 0; i < cons; i++){
		delete consumers[i];
	}
	
	delete[] producers;
	delete[] consumers;

	cout << "total: " << sum << endl;
}