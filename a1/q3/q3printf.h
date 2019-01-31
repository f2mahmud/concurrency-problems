_Coroutine Printf {
    char ch;                            // character passed by cocaller
    int charactersParsed = 0;
	std::string line = "";
	
	bool findInArray(const char array[], int sizeOfArray);
	void printResults(bool success);
	void matchFound();

	// YOU ADD MEMBERS HERE
    void main();                        // coroutine main
  public:
    _Event Match {};                    // last character match
    _Event Error {};                    // last character invalid
    void next( char c ) {
        ch = c;                         // communicate input
        resume();                       // activate
    }
};

char static const flags[5] = {'-', '+', ' ', '#', '0'};
char static const lengths[6] = {'h', 'l', 'j', 'z', 't', 'L'};
char static const specifiers[19] = {'d', 'i', 'u', 'o', 'x', 'X', 'f', 'F', 'e', 'E', 'g', 'G', 'a', 'A', 'c', 's',
                                    'p', 'n', '%'};