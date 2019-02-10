#include "q3printer.h"
#include "PRNG.h"

static PRNG prng;

_Event Schmilblick {
  public:
    unsigned int playerId;
    Schmilblick( unsigned int playerId ) : playerId(playerId) {};
};

_Coroutine Player {

	static unsigned int REMAINING_PLAYERS;
	
	unsigned int totalCards, cardsLeft, playerId;

	Player *playerOnLeft, *playerOnRight;
	Printer &printer;

	void main();
	void passToNextPlayer();
	
  public:
    enum { DEATH_DECK_DIVISOR = 7 };
    static void players( unsigned int num );
    Player( Printer &printer, unsigned int id );
    void start( Player &lp, Player &rp );
    void play( unsigned int deck );
    void drink();
	
};

