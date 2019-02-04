#include "q2binsertsort.cc"
#include <iostream>
#include <fstream>

#if defined(TYPE)

using namespace std;                    // direct access to std

int main(int argc, char *argv[]) {

    istream *infile = &cin;                // TODO get rid of this
    ostream *outfile = &cout;

    try {
        switch (argc) {
            case 3:
                try{
                    outfile = new ofstream(argv[2]);
                }catch(...){
                    cerr << "Something went wrong when creating the ofstream" << endl;
                }
                throw 1;
            case 2:
                try {                    // open input file first as output creates file
                    infile = new ifstream(argv[1]);    // open input file
                    infile->exceptions(ios_base::badbit | ios_base::failbit | ios_base::eofbit);
                } catch (ios_base::failure) {
                    cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
                    throw 1;
                } // try
                break;
            default:                    // wrong number of options
                throw 1;
        } // switch
    } catch (int x) {
        cerr << "Usage: ./binsertsort unsorted-file [sorted-file]" << endl;
        exit(EXIT_FAILURE);                // TERMINATE
    } // try

    //*infile >> noskipws;                // turn off white space skipping during input

    try {
		int count;
		TYPE ch;			
        Binsertsort<TYPE> root;

		*infile >> count;
		cout << "total Count: " << count << endl;
				
		for(int i = 0; i < count; i++){
			*infile >> ch;
			//TODO::Print values in way that they are sent
        	root.sort(ch);
		}
		
		cout << endl;
		
		root.Binsertsort<TYPE>::Sentinel = Binsertsort<TYPE>::Sentinel{};
				
		for(int i = 0; i < count; i++){
			TYPE result = root.retrieve();
			*outfile << result << endl;
		}
       
   	} catch (...) {
	cout << "Error caught" << endl;
   	}
    
    cout << "done" << endl;

    delete infile;
    
    if ( outfile != &cout ) {
        delete outfile;		// close file, do not delete cout!
    }



} // main

#else
#error TYPE not defined
#endif
