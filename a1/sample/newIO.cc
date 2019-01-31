
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;                    // direct access to std
#include <cstdlib>                    // exit


void printf(string line){
    cout << line ;
}


int main(int argc, char *argv[]) {
    enum {
        DefaultSize = 20, DefaultCode = 5
    };        // global defaults
    int size = DefaultSize, code = DefaultCode;        // default value
    istream *infile = &cin;                // default value
    ostream *outfile = &cout;                // default value

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

    string line;
    char ch;

    try {
        for (;;) {
            ch = infile->get();
            line += ch;
            if(ch == '\n'){
                printf(line);
		line = "";
            }
        }
    } catch (ios_base::failure) {
    } // try

    if (infile != &cin) {
        delete infile;
    }        // close file, do not delete cin!
} // main

// Local Variables: //
// compile-command: "g++ IOexp.cc" //
// End: //
