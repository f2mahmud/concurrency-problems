#include <iostream>
#include <fstream>

//#include "q3producer.h"	TODO::should be included, but duplicated buffer.h
#include "q3consumer.h"

using namespace std;


int main( int argc, char * argv[] ) {

    unsigned int cons = 5;
	unsigned int prods = 5;
	unsigned int produce = 10;
	unsigned int bufferSize = 10;
	unsigned int delay;
	
    try {
		
        switch ( argc ) {
            case 6:
				cin >> delay;
            case 5:
                cin >> bufferSize;
            case 4:
                cin >> produce;
			case 3:
				cin >> prods;
			case 2:
				cin >> cons;
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
		consumers[i] = new Consumer (buffer, delay, SENTINEL, sum);	//Figure out how to deal with sum
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
	
	//delete buffer;

	cout << "total: " << sum << endl;
}