#include <iostream>

#include "q3producer.h"
#include "MPRNG2.h"

extern MPRNG mprng;

Producer::Producer( BoundedBuffer<TYPE> &buffer, const int Produce, const int Delay): buffer(buffer), produce(Produce),
delay(Delay){}

void Producer::main(){
	
	for(int i = 1; i <= produce; i++){
		yield(mprng(0, delay-1));
		buffer.insert(i);
	}
	
}