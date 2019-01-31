#include "q3printf.h"

#include <iostream>
#include <fstream>

using namespace std;                    // direct access to std

int main(int argc, char *argv[]) {

    istream *infile = &cin;                // default value

    cin.exceptions(ios_base::badbit | ios_base::failbit | ios_base::eofbit);
    cout.exceptions(ios_base::badbit | ios_base::failbit);

    try {
        switch (argc) {
            case 2:
                try {                    // open input file first as output creates file
                    infile = new ifstream(argv[1]);    // open input file
                    infile->exceptions(ios_base::badbit | ios_base::failbit | ios_base::eofbit);
                } catch (ios_base::failure) {
                    cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
                    throw 1;
                } // try
            case 1:
                break;
            default:                    // wrong number of options
                throw 1;
        } // switch
    } catch (int x) {
        cerr << "Usage: ./printf [infile-file]" << endl;
        exit(EXIT_FAILURE);                // TERMINATE
    } // try

    *infile >> noskipws;                // turn off white space skipping during input

    try {
        string line;
		while(true){
			getline(*infile,line);
			Printf printf;
			for (char ch: line) {                    // copy input file to output fil
				printf.next(ch);
			} // for
		}
    } catch (...) {
		cout << "Error caught" << endl;
    }

    if (infile != &cin) {
        delete infile;
    }        // close file, do not delete cin!
} // main
