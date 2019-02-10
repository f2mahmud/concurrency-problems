
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
		
		try{
			_Enable{}
		}_CatchResume(Sentinel &s){
			_Resume s _At resumer();
			suspend();
		}
		
		T pivot = value;
			
		try{		
			_Enable{
				suspend();
			}
		}catch(Sentinel &s){
			value = pivot;
			suspend();
			_Resume s _At resumer();
			suspend();
		}
		
		// implies vertex node
		Binsertsort<T> less, greater;  
		
		try{
			//Storing values
			_Enable {   
				while(true){
					if(value < pivot){
						less.sort(value);
					}else{
						greater.sort(value);
					}
					suspend();
				}
			}
			
		}_CatchResume(Sentinel &s){
		
			try{
				_Enable{
					_Resume s _At less;
					while(true){
						value = less.retrieve();
						suspend();
					}						
				}
			}_CatchResume(Sentinel &s){
				_Throw s;
			}
			catch(Sentinel &s){}
			
			//Getting pivot 	
			value = pivot;
			suspend();
			
			try{
				_Enable{	
					_Resume s _At greater;
					while(true){
						value = greater.retrieve();
						suspend();
					}
				}
			}_CatchResume(Sentinel &s){
				_Throw s;	
			}catch(Sentinel &S){
				_Resume s _At resumer();
				suspend();
			}
			
		}
		
	}
	  
};