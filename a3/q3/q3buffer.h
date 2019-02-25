#ifndef BUFFER_H

#define BUFFER_H

#include <iostream>



template<typename T> class BoundedBuffer {
	
	unsigned int size, used;
	
	T *items;
	
	//Create locks
	uOwnerLock ownerLock;
	uCondLock producerCL, consumerCL;
	
	void push(T item){
		items[used] = item;
		used += 1;
	}
	
	T pop(){
		used -= 1;
		T item = items[used];
		return item;
	}
	
#ifdef NOBUSY
	
	bool noProducerEntry = false;
	bool noConsumerEntry = false;
	
	//create locks for no busy
	uCondLock producerBargerCL, consumerBargerCL;

#endif
	
  public:
    
	BoundedBuffer( const unsigned int size = 10 ) : size(size), used(0) {
		items = new T[size];
	};
	
	~BoundedBuffer() { delete[] items; }
	
#ifdef BUSY
    void insert( T elem ){
		ownerLock.acquire();
		try{
			while(used == size){
				producerCL.wait(ownerLock);
			}
			assert(used < size);
			push(elem);
			consumerCL.signal();
		}_Finally{
			ownerLock.release();
		}
	};
	
    T remove(){
		ownerLock.acquire();
		T answer;
		try{
			while(used == 0){
				consumerCL.wait(ownerLock);
			}
			assert(used > 0);
			answer = pop();
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
			
			if(noProducerEntry){
				producerBargerCL.wait(ownerLock);
			}
			
			if(used == size){
				noProducerEntry = true;
				producerCL.wait(ownerLock);
			}
			
			assert(used < size);
			push(elem);
			
			consumerCL.signal();
			producerBargerCL.signal();
			
			if(producerBargerCL.empty()){
				noProducerEntry = false;
			}
	
		}_Finally{
			ownerLock.release();
		}
	};
	
    T remove(){
		
		ownerLock.acquire();
		T answer;
		
		try{
			
			if(noConsumerEntry){
				consumerBargerCL.wait(ownerLock);
			}
			
			if(used == 0){
				noConsumerEntry = true;
				consumerCL.wait(ownerLock);
			}
			
			assert(used > 0);
			answer = pop();
			
			producerCL.signal();
			consumerBargerCL.signal();
			
			if(consumerBargerCL.empty()){
				noConsumerEntry = false;
			}
			
		}_Finally{
			ownerLock.release();
		}
		
		return answer;
		
	}

#endif // NOBUSY

};

#endif



