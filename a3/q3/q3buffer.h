#include <queue>
#include <iostream>

using namespace std;

template<typename T> class BoundedBuffer {
	
	unsigned int size;
	
	queue<T> items;
	
	//Create locks
	uOwnerLock ownerLock;
	uCondLock producerCL, consumerCL;
	
#ifdef NOBUSY

	bool producerCLOccupied = false;
	bool consumerCLOccupied = false;
	
	//create locks for no busy
	uCondLock producerCL2, consumerCL2;

#endif
	
  public:
    
	BoundedBuffer( const unsigned int size = 10 ) : size(size){
		//items = queue::queue(size);
	};

#ifdef BUSY
    void insert( T elem ){
		ownerLock.acquire();
		
		try{
			while(items.size() == size){
				producerCL.wait(ownerLock);
			}
			
			assert(items.size() <= size);
			items.push(elem);
			consumerCL.signal();
		}_Finally{
			ownerLock.release();
		}
	};
	
    T remove(){
		ownerLock.acquire();
		T answer;
		try{
			while(items.size() == 0){
				consumerCL.wait(ownerLock);
			}
			assert(items.size() >= 0);
			answer = items.front();
			items.pop();
			producerCL.signal();
		}_Finally{
			ownerLock.release();
		}
		return answer;
	}
	
#endif
#ifdef NOBUSY                          
	
void insert( T elem ){
		ownerLock.acquire();
		try{
			
			if(producerCLOccupied){
				producerCL2.wait(ownerLock);
			}
			
			if(items.size() == size || producerCLOccupied){
				producerCLOccupied = true;
				producerCL.wait(ownerLock);
			}
			
			assert(items.size() <= size);
			items.push(elem);
			
			if(producerCL.empty() || items.size() < size ){
				producerCLOccupied = false;
			}
			
			consumerCL.signal();
			producerCL2.signal();	
				
		}_Finally{
			ownerLock.release();
		}
	};
	
    T remove(){
		
		ownerLock.acquire();
		T answer;
		
		try{
			if(consumerCLOccupied){
				consumerCL2.wait(ownerLock);
			}
			
			if(items.size() == 0 || consumerCLOccupied){
				consumerCLOccupied = true;
				consumerCL.wait(ownerLock);
			}
			
			assert(items.size() >= 0);
			answer = items.front();
			items.pop();
			
			if(consumerCL.empty() || items.size() > 0){
				consumerCLOccupied = false;
			}
			
			producerCL.signal();
			consumerCL2.signal();	
			
		}_Finally{
			ownerLock.release();
		}
		
		return answer;
		
	}

#endif // NOBUSY

};



