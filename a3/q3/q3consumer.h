#include "q3producer.h"		//TODO:: need to fix this, should be buffer

_Task Consumer {
	BoundedBuffer<TYPE> &buffer;
	const int Sentinel;
	int delay;
	int &sum;
    void main();
  public:
    Consumer( BoundedBuffer<TYPE> &buffer, const int Delay, const int Sentinel, int &sum );
};