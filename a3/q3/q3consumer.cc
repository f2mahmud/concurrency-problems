#include "q3consumer.h"
#include "MPRNG2.h"

extern MPRNG mprng;

Consumer::Consumer(BoundedBuffer<TYPE> &buffer, const int Delay, const int Sentinel, int &sum): buffer(buffer), delay(Delay), Sentinel(Sentinel), sum(sum){}

void Consumer::main(){
	
	TYPE value;
	while(true){
		yield(mprng(0,delay-1));
		value = buffer.remove();
		if(value == Sentinel) break;
		sum += value;
	}
	
}