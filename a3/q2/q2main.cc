#include "q2matrixmultiply.h"
#include "q2printer.h"
#include <iostream>

#include <fstream>

using namespace std;

int main( int argc, char * argv[] ) {

    istream * infile;

    unsigned int xr, xcyr, yc;
    int processors = 1;

    int **X, **Y, **Z;

    try {

        xr = stoi(argv[1]);
        xcyr = stoi(argv[2]);
        yc = stoi(argv[3]);

        Z = new int*[xr];
		for (int i = 0 ; i < xr; i++){
			Z[i] = new int[yc];
		}

        switch ( argc ) {
            case 6:
				
				X = new int*[xr];
				Y = new int*[xcyr];
				
                //Reading matrix Y
                try{
                    infile = new ifstream(argv[5]);
                    for(int i = 0; i < xcyr; i++){
                        Y[i] = new int[yc];
                        for (int j = 0; j < yc; j++){
                            *infile >> Y[i][j];
                        }
                    }
                    delete infile;
                }catch(...){
                    cerr << "Error! Cannot open y-matrix input-file " << argv[5] << '\n';
                    throw 1;
                }
                try{
                    infile = new ifstream(argv[4]);
                    for(int i = 0; i < xr; i++){
                        X[i] = new int[xcyr];
                        for (int j = 0; j < xcyr ; j++){
                            *infile >> X[i][j];
                        }
                    }
                    delete infile;
                }catch(...){
                    cerr << "Error! Cannot open x-matrix input-file " << argv[4] << '\n';
                    throw 1;
                }
                break;
            case 5:
                processors = stoi(argv[4]);
            case 4:
                break;
            default:					// wrong number of options
                throw 1;
        } // switch

    } catch( ... ) {
        cerr << "Usage: "<< argv[0] << " xrows (> 0) xycols (> 0) ycols (> 0) [ processors (> 0) | x-matrix-file  y-matrix-file ]" << '\n';
        //exit( EXIT_FAILURE );				// TERMINATE

    } // try

    uProcessor p[processors - 1];  // number of kernel threads

    matrixmultiply( Z, X, xr, xcyr, Y, yc );
	
	//Printer p;
	
	//p.print(Y);
	//p.print(X,Z);
	
	for(int i = 0; i < xr; i++){
        delete [] X[i];
		delete [] Z[i];
    }
	delete [] X;
	delete [] Z;
					
	for(int i = 0; i < xcyr; i++){
		delete [] Y[i];
	}
	delete[] Y;
	
	//delete all the matrices

}