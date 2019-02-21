#include "q3buffer.h"
#include "MPRNG2.h"

static MPRNG mprng;

_Task Producer {
	BoundedBuffer<TYPE> &buffer;
	int produce;
	int delay;
    void main();
  public:
    Producer( BoundedBuffer<TYPE> &buffer, const int Produce, const int Delay );
};