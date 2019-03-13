#ifndef TALLYVOTES_H
#define TALLYVOTES_H

#include <algorithm>

using namespace std;

_Cormonitor Printer;

#if defined( MC )                    // mutex/condition solution

// includes for this kind of vote-tallier

class TallyVotes {
    // private declarations for this kind of vote-tallier
	uOwnerLock ownerLock;
	uCondLock syncLock, bargeLock;
	
	bool groupFull = false;
	
#elif defined( SEM )                // semaphore solution
	
// includes for this kind of vote-tallier
#include <uSemaphore.h>

class TallyVotes {
    // private declarations for this kind of vote-tallier
	uSemaphore ownerSem, syncSem, bargeSem;
	
	bool groupFull = false;
	
#elif defined( BAR )                // barrier solution

// includes for this kind of vote-tallier
#include <uBarrier.h>

_Cormonitor TallyVotes : public uBarrier {
    // private declarations for this kind of vote-tallier
	unsigned int currentId;
	
	void last();
	void block();
	
#else
    #error unsupported voter type
#endif
//had to restructure public/private to make sure things arent defined in an unwanted time
public:                            // common interface
  
    _Event Failed {};
	
    TallyVotes( unsigned int voters, unsigned int group, Printer & printer );
	
    struct Ballot { unsigned int picture, statue, giftshop; };
	
    enum TourKind { Picture = 'p', Statue = 's', GiftShop = 'g' };
    
	struct Tour { TourKind tourkind; unsigned int groupno; };
	
    Tour vote( unsigned int id, Ballot ballot );
    
	void done();
	
private:
    // common declarations
	unsigned int groupId = 0;
	unsigned int voters, votes = 0;
	unsigned int groupSize, bargingGroupSize = 0;
	unsigned int shopVotes = 0, pictureVotes = 0, statueVotes = 0;
	
	bool quorum = false;
	
	struct Tour chosenTour;
	
	Printer &p;
	
	void setWinningTour(){
		unsigned int highest = max(shopVotes, max(pictureVotes,statueVotes));
		
		chosenTour.groupno = groupId;
		
		groupId += 1;
		
		if(highest == shopVotes){
			chosenTour.tourkind = TourKind::GiftShop;
		} else if(highest == pictureVotes){
			chosenTour.tourkind = TourKind::Picture;
		}else{
			chosenTour.tourkind = TourKind::Statue;
		}
		
	}
	
  
	
};

#endif