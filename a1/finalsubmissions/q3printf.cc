#include "q3printf.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;                    // direct access to std
#include <cstdlib>                    // exit

bool Printf::findInArray(const char array[], int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++) {
        if (array[i] == ch) {
            return true;
        }
    }
    return false;
}

void Printf::printResults(bool success) {
	charactersParsed += 1;
	if (ch!= '\n'){
		suspend();
	}
	while (ch != '\n') {
        line += ch;
        suspend();
    }
	
    cout << '\'' << line << '\'' << " : ";
    cout << '\'' << line.substr(0, charactersParsed) << '\'';

    if (success) {
        cout << " yes";
    } else {
        cout << " no";
    }
    if (charactersParsed != line.length()) {
        cout << ", extraneous characters ’" << line.substr(charactersParsed) << '\'';
    }
    cout << endl;
	charactersParsed = 0;
	line = "";
    return;
}

void Printf::matchFound() {
	suspend();
	if(ch != '\n'){
		charactersParsed += 1;
		line += ch;
	}
}

void Printf::main() {
		
		while(true){
        line += ch;
        try {

            if (ch == '\n') {        //For the first character of the line
                cout << "'' : Warning! Blank line." << endl;
				charactersParsed = 0;
				line = "";
                continue;
            }
            if (ch != '%') {
                throw Error();
            }
            matchFound();

            for (int i = 0; i < 2; i++) {            //To resolve flags
                if (findInArray(flags, 5)) {
                    matchFound();
                    continue;
                }
                break;
            }

            if (ch == '*') {                    //To resolve width
                matchFound();
            } else {
                while (isdigit(ch)) {
					matchFound();
                }
            }
			
            if (ch == '.') {                    //To resolve precision
                matchFound();
                if (ch == '*') {
                    matchFound();
                } else if (isdigit(ch)) {
					while (isdigit(ch)) {
						matchFound();
					}
                }else{
					throw Error();    //There will be an error if there is only a perioud	
				}    
            }
			
            if (findInArray(lengths, 6)) {        //Resolving length
				charactersParsed += 1;
                if (ch == 'l' || ch == 'h') {
                    char old = ch;
                    suspend();
					line += ch;
                    if (ch == old) {
                        matchFound();
                    }
                }
            }
			
            if (findInArray(specifiers, 19)) {        //To resolve specifier
                throw Match();
            }
            throw Error();                    //Specifier not found
			
        } catch (Match m) {
            printResults(true);
        } catch (Error e) {
            printResults(false);

        }
		
		}
        
	
}