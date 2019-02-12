#include <vector>
#include <iostream>

using namespace std;

class Printer {
  
	const unsigned int xr,xcyr,yc;
	   
  public:
    
    Printer( const unsigned int xr, const unsigned int xcyr, const unsigned int yc );
   
	void print(int *Y[]);
	
	void print(int *X[], int *Z[]);
	
};