#include "q3buffer.h"

_Task Consumer {
	BoundedBuffer<TYPE> &buffer;
	const int Sentinel;
	int delay;
	TYPE &sum;
    void main();
  public:
    Consumer( BoundedBuffer<TYPE> &buffer, const int Delay, const int Sentinel, TYPE &sum );
};