
#include <iostream>
using namespace std;


template<typename T> _Coroutine Binsertsort {

public:
  
    _Event Sentinel {};
	
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
		
		T pivot = value;
		cout << "New Binsertsort created with value: " << pivot << endl;
		try{
			cout <<"Suspending....value: " << pivot << endl;
			suspend();
			cout << "Done with suspend" << endl;
		}catch(Sentinel &s){	//Getting here means that this is a leaf node
		
		}
		// implies vertex node
		Binsertsort<T> less, greater;    
		try{   
			while(true){
				if(value < pivot){
					less.sort(value);
					cout << "Set value to less: " << value << endl;
				}else{
					greater.sort(value);
					cout << "Set value to greater: " << value << endl;
				}
				suspend();
			}
		}_CatchResume(Sentinel &s){
			cout << "Getting from less : " << pivot << endl;
			_Resume s _At less;
			cout << "Propagated back value: " << pivot << endl;
			//TODO:: Need to get value from thing itself
			cout << "Getting from greater : " << pivot << endl;
			_Resume s _At less;
			cout << "Propagated back value: " << pivot << endl;
		}		//catch Resume end
		
	}                    
	
  
};