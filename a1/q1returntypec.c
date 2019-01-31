#include <stdio.h>
#include <stdlib.h>                                      // access: rand, srand
#include <string.h>
#include <unistd.h>                                     // access: getpid

union ReturnedValue{
    double normalAnswer;
    short int error1Code;
    int error2Code;
    long int error3Code;
};

struct ReturnedValueTracker{
    int id;
    union ReturnedValue value;
};

struct ReturnedValueTracker tracker;

int eperiod = 10000;                                    // error period

struct ReturnedValueTracker rtn1( double i ) {
    if ( rand() % eperiod == 0 ){
        tracker.value.error1Code = (short int)rand();
        tracker.id = 1;
    }else {
        tracker.value.normalAnswer = i;
        tracker.id = 0;
    }
    return tracker;
}

struct ReturnedValueTracker rtn2( double i  ) {
    if ( rand() % eperiod == 0 ){
        tracker.value.error2Code = rand();
        tracker.id = 2;
    } else{
        tracker = rtn1(i);
        if(	(tracker.id == 0) ){
            tracker.value.normalAnswer += i;
        }
    }
    return tracker;
}

struct ReturnedValueTracker rtn3( double i  ) {
    if ( rand() % eperiod == 0 ){
        tracker.value.error3Code = rand();
        tracker.id = 3;
    }else{
        tracker = rtn2(i);
        if(	(tracker.id == 0) ){
            tracker.value.normalAnswer += i;
        }
    }
    return tracker;
}

int main( int argc, char * argv[] ) {
    int times = 100000000, seed = getpid();   	// default values

    switch ( argc ) {
        case 4:
            if ( strcmp( argv[3], "d" ) != 0 ) {  // default ?
                seed = atoi( argv[3] );
                if ( seed <= 0 ) {
                    goto EXIT;
                }
            } // if
        case 3:
            if ( strcmp( argv[2], "d" ) != 0 ) {  // default ?
                eperiod = atoi( argv[2] );
                if ( eperiod <= 0 ) {
                    goto EXIT;
                }
            } // if
        case 2:
            if ( strcmp( argv[1], "d" ) != 0 ) {  // default ?
                times = atoi( argv[1] );
                if ( times <= 0 ) {
                    goto EXIT;
                }
            } // if
        case 1:
            break;                                // use all defaults
        default:
            goto EXIT;
    } // switch

    goto MAINCODE;

    EXIT:
    fprintf(stderr,"Usage: %s [ times > 0 | d [ eperiod > 0 | d [ seed > 0 ] ] ]\n", argv[0]);
    exit( EXIT_FAILURE );

    MAINCODE:
    srand( seed );

    double rv = 0.0;
    int ev1 = 0, ev2 = 0, ev3 = 0;
    int rc = 0, ec1 = 0, ec2 = 0, ec3 = 0;

    for ( int i = 0; i < times; i += 1 ) {
        rtn3(i);
        switch(tracker.id){
            case 0:
                rv += tracker.value.normalAnswer;
                rc += 1;
                break;
            case 1:
                ev1 += tracker.value.error1Code;
                ec1 += 1;
                break;
            case 2:
                ev2 += tracker.value.error2Code;
                ec2 += 1;
                break;
            case 3:
                ev3 += tracker.value.error3Code;
                ec3 += 1;
                break;
        }
    }

    printf("normal result %g exception results %d %d %d\n",rv,ev1,ev2,ev3);
    printf("calls %d exceptions %d %d %d\n", rc, ec1, ec2, ec3);
}
