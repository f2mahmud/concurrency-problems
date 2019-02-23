#include <uActor.h>

struct MatrixMessage : public uActor::Message { 
	int *X;
	int **Y;
	int &Z;
	unsigned int xcyr;
	int yc;
	MatrixMessage( int *X, int &Z, unsigned int xcyr, int *Y[], int yc ) : Message( uActor::Delete ), X( X ), Z(Z), xcyr(xcyr), Y(Y), yc(yc) {}
};

_Actor MatrixMultiply {
	
	Allocation receive( Message & msg ) { 
		
		Case(MatrixMessage, msg){
			int result = 0;
			for(int i = 0; i < msg_d->xcyr; i++){
				result += msg_d->X[i]*msg_d->Y[i][msg_d->yc];
			}
			msg_d->Z = result;
		}
		
		return Delete;
		
	}
};