#include <iostream>
#include <cstdlib>                                      // access: rand, srand
#include <cstring>                                      // access: strcmp
#include <variant>
using namespace std;
#include <unistd.h>                                     // access: getpid

/*
	The BaseEr class is the parent class for the 3 error type classes. Based on the 
	code where each error type had a different type for the code (long/short for Er1/Er2
	respectively), the copy constructor is created in the manner so that it behaves in the 
	same way as before. I have added a field for type so that it helps to distinguish
	which exact BaseEr is being thrown. To be specific:
		-> type -1, means there is currently no error that needs to be handled
		-> type 1, means Er1 is thrown
		-> type 2, means Er2 is thrown
		-> type 3, means Er3 is thrown
*/

struct BaseEr{ 
	BaseEr(int code, int type) : code(code),type(type){}
	public: 
		int code;
		int type;
};

struct Er1 : BaseEr { 
	Er1(short int code) : BaseEr(code,1){}
};

struct Er2 : BaseEr {
	Er2(int code) : BaseEr(code,2){}
};

struct Er3 : BaseEr { 
	Er3(long int code) : BaseEr(code,3){} 
};

int eperiod = 10000;                                    // error period

variant<double, BaseEr> rtn1( double i ) {
    if ( rand() % eperiod == 0 ) return Er1{ (short int)rand() };
    return {i};
}

variant<double, BaseEr> rtn2( double i  ) {
    if ( rand() % eperiod == 0 ) return Er2{ rand() };
	variant<double, BaseEr> result = rtn1(i);
	if(holds_alternative<double>(result)){
		return get<double>(result) + i;
	}
    return get<BaseEr>(result);
}

variant<double, BaseEr> rtn3( double i  ) {
    if ( rand() % eperiod == 0 ) return Er3{ rand() };
	variant<double, BaseEr> result = rtn2(i);
	if(holds_alternative<double>(result)){
		return get<double>(result) + i;
	}
    return get<BaseEr>(result);
}

int main( int argc, char * argv[] ) {
    int times = 100000000, seed = getpid();  	// default values
    
    try {
        switch ( argc ) {
          case 4: if ( strcmp( argv[3], "d" ) != 0 ) {  // default ?
                seed = stoi( argv[3] ); if ( seed <= 0 ) throw 1;
            } // if
          case 3: if ( strcmp( argv[2], "d" ) != 0 ) {  // default ?
                eperiod = stoi( argv[2] ); if ( eperiod <= 0 ) throw 1;
            } // if
          case 2: if ( strcmp( argv[1], "d" ) != 0 ) {  // default ?
                times = stoi( argv[1] ); if ( times <= 0 ) throw 1;
            } // if
          case 1: break;                                // use all defaults
          default: throw 1;
        } // switch
    } catch( ... ) {
        cerr << "Usage: " << argv[0] << " [ times > 0 | d [ eperiod > 0 | d [ seed > 0 ] ] ]" << endl;
        exit( EXIT_FAILURE );
    } // try
	
    srand( seed );

    double rv = 0.0;
    int ev1 = 0, ev2 = 0, ev3 = 0;
    int rc = 0, ec1 = 0, ec2 = 0, ec3 = 0;
	
	BaseEr error = BaseEr(0, -1);
	variant<double, BaseEr> rtn3Result;

    for ( int i = 0; i < times; i += 1 ) {
		rtn3Result = rtn3(i);
		if(holds_alternative<double>(rtn3Result)){
			rv += get<double>(rtn3Result); 
			rc += 1;
		}else{
			error = get<BaseEr>(rtn3Result);
			if(error.type == 1){
				ev1 += error.code;
				ec1 += 1;
			}else if(error.type == 2){
				ev2 += error.code;
				ec2 += 1;
			}else{
				ev3 += error.code;
				ec3 += 1;
			}
		} 
		
    } // for
    cout << "normal result " << rv << " exception results " << ev1 << ' ' << ev2 << ' ' << ev3 << endl;
    cout << "calls "  << rc << " exceptions " << ec1 << ' ' << ec2 << ' ' << ec3 << endl;
}
