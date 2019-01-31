#include <iostream>                                     // access: strcmp

using namespace std;

#include <unistd.h>                                     // access: getpid
#include <csetjmp>
#include <cstring>

#define DNOOUTPUT

#ifdef NOOUTPUT
#define PRT( stmt )
#else
#define PRT(stmt) stmt
#endif // NOOUTPUT

struct E {
};                                            // exception type
PRT(struct T {
        ~T() { cout << "~"; }
    };)

jmp_buf nonLocalBuf;

long int eperiod = 100, excepts = 0, calls = 0;        // exception period

long int Ackermann(long int m, long int n) {
    calls += 1;
    jmp_buf localBuf;
    jmp_buf backUpBuf;
    memcpy(localBuf, nonLocalBuf, sizeof(jmp_buf));
    int localBufCode = 0;

    if (m == 0) {
        if (rand() % eperiod == 0) {
            PRT(T t;)
            excepts += 1;
            longjmp(nonLocalBuf, 4);
        }
        return n + 1;

    } else if (n == 0) {

        localBufCode = setjmp(nonLocalBuf);
        if (localBufCode == 4) {
            PRT(cout << "E1 " << m << " " << n << endl);
            if (rand() % eperiod == 0) {
                PRT(T t;)
                excepts += 1;
                memcpy(nonLocalBuf, localBuf, sizeof(jmp_buf));
                longjmp(nonLocalBuf, 4);
            }
            return 0;
        }
        return Ackermann(m - 1, 1);

    } else {

        localBufCode = setjmp(nonLocalBuf);
        if (localBufCode == 4) {
            PRT(cout << "E2 " << m << " " << n << endl);
            if (rand() % eperiod == 0) {
                PRT(T t;)
                excepts += 1;
                memcpy(nonLocalBuf, localBuf, sizeof(jmp_buf));
                longjmp(nonLocalBuf, 4);
            }
            return 0;
        }
        memcpy(backUpBuf, nonLocalBuf, sizeof(jmp_buf));
        long int helperAckerman = Ackermann(m, n - 1);
        memcpy(nonLocalBuf, backUpBuf, sizeof(jmp_buf));
        return Ackermann(m - 1, helperAckerman);

    } // if
    return 0;                                           // recover by returning 0
}

int main(int argc, char *argv[]) {
    long int m = 4, n = 6, seed = getpid();             // default values
    try {                                               // process command-line arguments
        switch (argc) {
            case 5:
                if (strcmp(argv[4], "d") != 0) {  // default ?
                    eperiod = stoi(argv[4]);
                    if (eperiod <= 0) throw 1;
                } // if
            case 4:
                if (strcmp(argv[3], "d") != 0) {  // default ?
                    seed = stoi(argv[3]);
                    if (seed <= 0) throw 1;
                } // if
            case 3:
                if (strcmp(argv[2], "d") != 0) {  // default ?
                    n = stoi(argv[2]);
                    if (n < 0) throw 1;
                } // if
            case 2:
                if (strcmp(argv[1], "d") != 0) {  // default ?
                    m = stoi(argv[1]);
                    if (m < 0) throw 1;
                } // if
            case 1:
                break;                                // use all defaults
            default:
                throw 1;
        } // switch
    } catch (...) {
        cerr << "Usage: " << argv[0] << " [ m (>= 0) | d [ n (>= 0) | d"
                " [ seed (> 0) | d [ eperiod (> 0) | d ] ] ] ]" << endl;
        exit(EXIT_FAILURE);
    } // try

    srand(seed);                                      // seed random number

    int bufCode = setjmp(nonLocalBuf);

    if (bufCode == 4) {
        PRT(cout << "E3" << endl);
    } else {
        PRT(cout << m << " " << n << " " << seed << " " << eperiod << endl);
        long int val = Ackermann(m, n);
        PRT(cout << val << endl);
    }

    cout << "calls " << calls << ' ' << " exceptions " << excepts << endl;


}

