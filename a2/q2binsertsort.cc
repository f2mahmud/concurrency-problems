
#include <iostream>
using namespace std;

template<typename T> _Coroutine Binsertsort {

public:
  
    _Event Sentinel {};
    
    Binsertsort(){
    	cout << "New created" << endl;
    }
	
    void sort( T value ) {          // value to be sorted
        Binsertsort::value = value;
        resume();
    }
	
    T retrieve() {                  // retrieve sorted value
        resume();
        return value;
    }
    
private:
	
    T value;                        // communication: value being passed down/up the tree
   
	void main(){
		cout << "********Setting pivot value to " << value << endl;
		T pivot = value;
		cout << "New Binsertsort created with value: " << pivot << endl;
		try{
			_Enable{
				cout <<"Suspending....value: " << pivot << endl;
				suspend();
				cout << "Done with suspend " << pivot << endl;
			}
		}_CatchResume(Sentinel &s){
			value = pivot;
			cout << "catchResume1: " << value << endl;
			suspend();
		}
		// implies vertex node
		Binsertsort<T> less, greater;    
		try{
			_Enable {   
				while(true){
					if(value < pivot){
						less.sort(value);
						cout << ">>>>>>>>>Set value to less: " << pivot << " " << value << endl;
					}else{
						greater.sort(value);
						cout << ">>>>>>>>>Set value to greater: " << pivot << " " << value << endl;
					}
					cout << "Suspending second time : " << pivot << endl;
					suspend();
					cout << "Got out of second suspend : "<< pivot << endl;
				}
			}
		}_CatchResume(Sentinel &s){
			cout << "catch resume 2" << endl;
			if(less !=  ){
				_Resume s _At less;
				value = less.retrieve();
				cout << "<<<<<<<<<Propagated back value from less: " << pivot << " " << value << endl;
				suspend();
			}
			value = pivot;
			suspend();
			if(greater !=) {
				_Resume s _At greater;
				value = greater.retrieve();
				cout << "<<<<<<<<Propagated back value from greater: " << pivot << " " << value << endl;
				suspend();
			}
			_Throw s;
		}//catch(Sentinel &s){
		//	_Throw s;
		//}

	}                    
	
  
};