//Rishi Chandna
//rdc180001

#ifndef BEETLE_H
#define BEETLE_H

#include "Creature.h"


class Beetle : public Creature
{
    public: //See Creature.h for more information
        Beetle();
        Beetle(int, int);
        virtual ~Beetle();
        bool Starve(); //decrements energy, is called every turn, returns true if energy hits 0 after the decrement
        virtual void Breed(Creature* (&)[NUM_ROWS][NUM_COLS]);
        virtual void Move(Creature* (&)[NUM_ROWS][NUM_COLS]);
        void setEnergyFull() { this->energy = 5;}
        void eatAnt() { this->energy = 6;} //sets the energy to one higher than full so that after the starve decrement the beetle is at 5 by the end of the turn
    protected:

    private:
        void Travel(Creature* (&)[NUM_ROWS][NUM_COLS], Creature::Direction);
        bool ValidateMove(Creature* [NUM_ROWS][NUM_COLS], Creature::Direction);
        int energy;
};

#endif // BEETLE_H
