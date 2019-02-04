#include "q2binsertsort.cc"
#include <iostream>
#include <fstream>

#if defined(TYPE)

using namespace std;                    // direct access to std

	//Example TYPE
	
	class  ExampleType{
		
		int x;
		char y;
		
		public:
		
		ExampleType(char y1 = 'a', int x1 = 0){
			x = x1;
			y = y1;
		}
		
		bool operator<(const ExampleType &other){
			if(y > other.y){
				return true;
			} 
			return x < other.x;
		}
		
		bool operator==(const ExampleType &other){
			return x == other.x && y == other.y;
		}
		
		friend istream &operator >> (istream &input, ExampleType &exampleType){
			input >> exampleType.y >> exampleType.x;
			return input;
		}
		
		friend ostream &operator << (ostream &output, const ExampleType &exampleType){
			output << exampleType.y << '-' << exampleType.x;
			return output;
		}
		
	};

int main(int argc, char *argv[]) {

    istream *infile;
    ostream *outfile = &cout;

    try {
        switch (argc) {
            case 3:
                try{
                    outfile = new ofstream(argv[2]);
                }catch(...){
                    cerr << "Something went wrong when creating the ofstream" << endl;
					throw 1;
                }
            case 2:
                try {                    // open input file first as output creates file
                    infile = new ifstream(argv[1]);    // open input file
                    infile->exceptions(ios_base::badbit | ios_base::failbit);
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


    try {
		int count;
		
		*infile >> count;
		
		if(count != 0){
			TYPE ch;				
			Binsertsort<TYPE> root;

			for(int i = 0; i < count; i++){
				*infile >> ch;
				*outfile << ch << ' ';
				root.sort(ch);
			}
		
			*outfile << '\n';
		
			_Resume Binsertsort<TYPE>::Sentinel{} _At root;
				
			for(int i = 0; i < count; i++){
				TYPE result = root.retrieve();
				*outfile << result << ' ';
			}
		}else{
			*outfile << '\n';
		}
		
		*outfile << '\n';
       
   	} catch (...) {
		cout << "Error caught" << endl;
   	}
    
    delete infile;
    
    if ( outfile != &cout ) {
        delete outfile;		// close file, do not delete cout!
    }



} // main

#else
#error TYPE not defined
#endif
