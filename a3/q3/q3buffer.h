#include <queue>

using namespace std;

template<typename T> class BoundedBuffer {
	
	unsigned int size;
	
	queue<T> items;
	
	//Create locks
	uOwnerLock ownerLock;
	uCondLock pCondLock, cCondLock;
	
#ifdef NOBUSY

	bool producerOccupied = false;
	bool consumerOccupied = false;
	
	//create locks for no busy
	uCondLock pCondLock2, cCondLock2;

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
				pCondLock.wait(ownerLock);
			}
			
			assert(items.size() < size);
			items.push(elem);
			cCondLock.signal();
		}_Finally{
			ownerLock.release();
		}
	};
	
    T remove(){
		ownerLock.acquire();
		T answer;
		try{
			while(items.size() == 0){
				cCondLock.wait(ownerLock);
			}
			assert(items.size() > 0);
			answer = items.front();
			items.pop();
			pCondLock.signal();
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
			
			if(producerOccupied){
				pCondLock2.wait(ownerLock);
			}
			
			if(items.size() == size){
				producerOccupied = true;
				pCondLock.wait(ownerLock);
			}
			
			assert(items.size() < size);
			items.push(elem);
			
			producerOccupied = false;
			
			cCondLock.signal();
			pCondLock2.signal();
			
		}_Finally{
			ownerLock.release();
		}
		
	};
	
    T remove(){
		
		ownerLock.acquire();
		T answer;
		
		try{
			
			if(consumerOccupied){
				cCondLock2.wait(ownerLock);
			}
			
			if(items.size() == 0){
				cCondLock.wait(ownerLock);
			}
			
			
			
			assert(items.size() > 0);
			answer = items.front();
			items.pop();
			
			consumerOccupied = false;
			
			pCondLock.signal();
			cCondLock2.signal();
			
		}_Finally{
			ownerLock.release();
		}
		
		return answer;
		
	}

#endif // NOBUSY

};



