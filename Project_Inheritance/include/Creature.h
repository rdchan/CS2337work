//Rishi Chandna
//rdc180001

#ifndef CREATURE_H
#define CREATURE_H
#include <iostream>

#define NUM_ROWS 10
#define NUM_COLS 10

class Creature
{
    public:
        Creature() {}; //default constructor
        Creature(int, int); //constructor with position coordinates
        virtual ~Creature() {}; //no pointer objects in the class, so nothing in the destructor
        enum Direction {NORTH, EAST, SOUTH, WEST}; //used for code readability
        virtual void Breed(Creature* (&)[NUM_ROWS][NUM_COLS]) = 0; //if called, will try to add a new creature
        virtual void Move(Creature* (&)[NUM_ROWS][NUM_COLS]) = 0; //contains logic for where to move, then calls travel
        virtual void Travel(Creature* (&)[NUM_ROWS][NUM_COLS], Creature::Direction) = 0;  //once where to move has been decided, travel moves the creature and deletes its previous spot

        int getRow() const {return row;}
        int getCol() const {return col;}
        void setRow(int _row) {row = _row;} //mostly used for testing
        void setCol(int _col) {col = _col;} //mostly used for testing
        void setPos(int _row, int _col) { row = _row; col = _col;} //mostly used for testing
        void setMovedThisTurn(bool _turn) { moved_this_turn = _turn;} //used to prevent double moves
        bool hasMoved() { return moved_this_turn;} //used to prevent double moves
        void setNewborn(bool _born) { is_newborn = _born; } //used to prevent early starving and infant breeding
        bool isNewborn() { return is_newborn; } //used to prevent early starving and infant breeding
    protected:

    private:
        int row = -1;
        int col = -1;
        bool moved_this_turn;
        bool is_newborn; //used to make sure that baby ants and beetles don't breed, and baby beetles don't lose energy
    public:
        //ValidateMove returns true if the space in the direction is empty. Used in both classes for breeding, used in Ant for moving
        bool ValidateMove(Creature* grid[NUM_ROWS][NUM_COLS], Creature::Direction dir){ // takes in vector of beetles and vector of ants
            //Use direction with this ants position to
            //find 2 integer coordinates representative of the space in the direction away from this ant
            int desired_row;
            int desired_col;
            if(dir == Creature::Direction::NORTH) {
                desired_row = this->getRow()-1;
                desired_col = this->getCol();
            } else if(dir == Creature::Direction::EAST) {
                desired_row = this->getRow();
                desired_col = this->getCol()+1;
            } else if(dir == Creature::Direction::SOUTH) {
                desired_row = this->getRow()+1;
                desired_col = this->getCol();
            } else if(dir == Creature::Direction::WEST) {
                desired_row = this->getRow();
                desired_col = this->getCol()-1;
            }

            //if either row integer or col integer is out of bounds, return false
            if(desired_row < 0 || desired_row > 9 || desired_col < 0 || desired_col > 9) { return false; }

            //check if the pointer at the desired location is free
            //should return true if the desired location is empty/nullptr
            return grid[desired_row][desired_col] == nullptr;
        }

};

#endif // CREATURE_H
