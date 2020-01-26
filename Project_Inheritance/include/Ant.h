//Rishi Chandna
//rdc180001

#ifndef ANT_H
#define ANT_H

#include "Creature.h"


class Ant : public Creature
{
    public: //see Creature.h for more information
        Ant();
        Ant(int, int);
        virtual ~Ant();
        int countNeighbors(Creature* [NUM_ROWS][NUM_COLS]) const;
        virtual void Breed(Creature* (&)[NUM_ROWS][NUM_COLS]); //when called, tries to place an ant orthogonally using NESW priority
        virtual void Move(Creature* (&)[NUM_ROWS][NUM_COLS]); //figures out where to move, then calls travel
    protected:

    private:
        virtual void Travel(Creature* (&)[NUM_ROWS][NUM_COLS], Creature::Direction); //actually manipulates grid pointers

};

#endif // ANT_H
