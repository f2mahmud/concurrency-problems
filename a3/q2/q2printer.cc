#include "q2printer.h"
#include <iomanip>

using namespace std;
   
	
void Printer::print(int *Y[] , int *X[], int *Z[] , int xr, int xcyr, int yc){
	
	int Xspacing = (8 * xcyr) + 4;
	int Zspacing = 1 + (8 * yc);
    //printing y
    for(int i = 0; i < xcyr; i++) {
        cout << setw(Xspacing) << "|" << ' ';
        for (int j = 0; j < yc; j++) {
            cout << setw(8) << Y[i][j];
        }
        cout << endl;

    }
    
	cout << setfill('-') << setw(Xspacing) << "*" << setw(Zspacing) << '-' << setfill(' ') << endl;

    //Print x and z
    for(int i = 0; i < xr ; i ++){
        for (int j = 0 ; j < xcyr ; j++){
            cout << setw(8) << X[i][j];
        }
        cout << setw(4) << '|';
		cout << ' ';
        for (int j = 0 ; j < yc; j++){
            cout << setw(8) << Z[i][j];
        }
        cout << endl;
    }
	
}
	
	