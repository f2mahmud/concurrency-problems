#include "q2binsertsort.h"
#include <iostream>
#include <fstream>
#define TYPE

#if defined(TYPE)

using namespace std;                    // direct access to std

int main(int argc, char *argv[]) {

    istream *infile = &cin;                // default value
    ostream *outfile = &cout;

    try {
        switch (argc) {
            case 2:
                try{
                    outfile = new ofstream(argv[2]);
                }catch(...){
                    cerr << "Something went wrong when creating the ofstream" << endl;
                }
                throw 1;
            case 1:
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
        int ch;					//TODO::Need to change types here once done to make it take 'T'
        Binsertsort<int> bInsertSort;
        while(true){
            *infile >> ch;
            if(infile->fail()){
                break;
            }
            bInsertSort.sort(ch);
        }
    } catch (...) {
        cout << "Error caught" << endl;
    }

    if (infile != &cin) {
        delete infile;
    }        // close file, do not delete cin!
    if ( outfile != &cout ) {
        delete outfile;		// close file, do not delete cout!
    }



} // main

#else
#error TYPE not defined
#endif
