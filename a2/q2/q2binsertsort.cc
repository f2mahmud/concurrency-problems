
#include <iostream>
using namespace std;

template<typename T> _Coroutine Binsertsort {

public:
  
    _Event Sentinel {};
    
    Binsertsort(){			//TODO::REmove
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
	
			//To avoid null edges being read
			//if(value == Sentinel){
			//	suspend();
			//	return;
			//}
			
			cout << "********Setting pivot value to " << value << endl;
			T pivot = value;
			try{
				
				_Enable{
					suspend();
				}
				
			}_CatchResume(Sentinel &s){
				
				try{
					_Enable{
						value = pivot;
						suspend();
					}
				}_CatchResume(Sentinel &s){
					cout << "About to Catch Resume to resumer " << pivot << endl;
					_Throw s;
				}
				
			}
		
		// implies vertex node
		Binsertsort<T> less, greater;  
		
		try{
			//Storing values
			_Enable {   
				while(true){
					if(value < pivot){
						less.sort(value);
						cout << "Set less from " << pivot << " to " << value << endl;
					}else{
						greater.sort(value);
						cout << "Set greater from " << pivot << " to " << value << endl;
					}
					suspend();
				}
			}
			
		}_CatchResume(Sentinel &s){
			
			//Getting values less than pivot 
			//FIXME:: Cant do more than 1 value
		
			try{
				//while(true){
					_Enable{
						cout << "Getting less value from " << pivot << endl;
						_Resume s _At less;
						value = less.retrieve();
						cout << "<<<<<<<<<Propagated back value from less: " << pivot << " " << value << endl;
						suspend();
					}
				//}
			}_CatchResume(Sentinel &s){
				_Resume s;
			}catch(Sentinel &s){
				cout << "Here" << endl;
			}
			
			//Getting pivot 
			
			try{
				
				cout << "Outside sending root value " << pivot << endl;
				_Enable{
					cout << "Sent root value : " << pivot << endl;
					value = pivot;
					suspend();
				}
				
			}_CatchResume(Sentinel &s){
				_Throw s;
			}catch (Sentinel &s){
				
			}
			
			try{
				//while(true){
						_Enable{	
							cout << "Greater outer ccatch resume :: " << pivot << endl;
							_Resume s _At greater;
							value = greater.retrieve();
							cout << "<<<<<<<<Propagated back value from greater: " << pivot << " " << value << endl	;					
							suspend();
						}
					//}
			}_CatchResume(Sentinel &s){
				_Resume s;
			}catch(Sentinel &s){
			}
			
		}
		
	}                    
	
  
};