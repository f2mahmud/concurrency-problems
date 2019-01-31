
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;                    // direct access to std
#include <cstdlib>                    // exit

char const static flags[5] = {'-', '+', ' ', '#', '0'};
//char static digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

string static const lengths[8] = {"h", "hh", "l", "ll", "j", "z", "t", "L"};
string static const specifiers[19] = {"d", "i", "u", "o", "x", "X", "f", "F", "e", "E", "g", "G", "a", "A", "c", "s",
                                      "p", "n", "%"};

int checkForDigits(string subLine) {
    if (subLine[0] == '*') {
        return 1;
    }
    for (int i = 0; i < subLine.length(); i++) {
        if (!isdigit(subLine[i])) {
            return i;
        }
    }
    return 0;
}

int checkAgainstArray(string subLine, const string array[], int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++) {
        switch (array[i].length()) {
            case 1:
                if (array[i] == subLine.substr(0, 1)) {
                    return 1;
                }
                break;
            case 2:
                if (array[i] == subLine) {
                    return 2;
                }
        }
    }
    return 0;
}

int static lookForFlag(const char ch) {
    for (int i = 0; i < 5; i++) {
        if (flags[i] == ch) {
            return 1;
        }
    }
    return 0;
}

int checkForFlags(const char ch1, const char ch2) {
    int result = 0;
    result += lookForFlag(ch1);
    if (result == 0) {
        return result;
    }
    return result + lookForFlag(ch2);
}

void printResults(string line, int charsParsed, bool success) {
    cout << '\'' << line.substr(0, charsParsed) << '\'';
    if (success) {
        cout << " yes";
    } else {
        cout << " no";
    }
    if (charsParsed != line.length()) {
        cout << ", extraneous characters ’" << line.substr(charsParsed) << '\'';
    }
    cout << endl;
    return;
}


void printf(string line) {

    if (line[line.length() - 1] == '\r') {
        line.erase(line.length() - 1);
    }

    cout << '\'' << line << '\'' << " : ";

    if (line == "") {
        cout << "Warning! Blank line." << endl;
        return;
    }

    int charactersParsed = 0;

    if (line[0] == '%') {
        charactersParsed = 1;

        charactersParsed += checkForFlags(line[charactersParsed], line[charactersParsed + 1]);
        charactersParsed += checkForDigits(line.substr(charactersParsed));          //checking for width
        if (line[charactersParsed] == '.') {                      //checking for precision
            charactersParsed += 1;
            int numberOfPrecisionChars = checkForDigits(line.substr(charactersParsed));
            if (numberOfPrecisionChars == 0) {
                printResults(line, charactersParsed, false);    // TODO:: can be in a catch block
            }
            charactersParsed += numberOfPrecisionChars;
        };
        charactersParsed += checkAgainstArray(line.substr(charactersParsed, charactersParsed + 1), lengths,
                                              8);         // check for length
        int specifierCount = checkAgainstArray(line.substr(charactersParsed, charactersParsed), specifiers,
                                               19);              //check for specifiers
        if (specifierCount == 0) {
            printResults(line, charactersParsed, false);       //TODO:: can be in a catch block
        }

        charactersParsed += specifierCount;
        printResults(line, charactersParsed, true);
        return;
    }

    printResults(line, 1, false);        //TODO:: can be in a catch block

}


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

//    *infile >> noskipws;                // turn off white space skipping during input

    string line;
    char ch;

    try {
        for (;;) {
            ch = infile->get();
            if (ch == '\n') {
                printf(line);
                line = "";
                continue;
            }
            line += ch;
        }
    } catch (ios_base::failure) {} // try

    if (infile != &cin) {
        delete infile;
    }        // close file, do not delete cin!
} // main

// Local Variables: //
// compile-command: "g++ IOexp.cc" //
// End: //
