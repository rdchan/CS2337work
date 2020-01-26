//Rishi Chandna
//rdc180001

#include "Ant.h"
#include <iostream> //only for debug, remove in final
#include "Beetle.h"
Ant::Ant()
{
    this->setRow(-1);
    this->setCol(-1);
    this->setNewborn(true);
}

Ant::Ant(int _row, int _col) {
    this->setRow(_row);
    this->setCol(_col);
    this->setNewborn(true);
}
Ant::~Ant()
{

}

void Ant::Breed(Creature* (&grid)[NUM_ROWS][NUM_COLS]) {

        //Using ants location…
            //validate spots in order given
            //add an ant to the grid at the first open spot, checking in order of N, E, S, W
            //exit
        //no need to deallocate what grid[new_row][new_col] was holding, since it was nullptr per Creature::ValidateMove()
        if(this->ValidateMove(grid, Creature::Direction::NORTH)) { //try north spot
            grid[this->getRow()-1][this->getCol()] = new Ant(this->getRow()-1,this->getCol());
        } else if(this->ValidateMove(grid, Creature::Direction::EAST)) { //try east spot
            grid[this->getRow()][ this->getCol()+1] = new Ant(this->getRow(), this->getCol()+1);
        } else if(this->ValidateMove(grid, Creature::Direction::SOUTH)) { // try south spot
            grid[this->getRow()+1][this->getCol()] = new Ant(this->getRow()+1, this->getCol());
        } else if(this->ValidateMove(grid, Creature::Direction::WEST)) { //try west spot
            grid[this->getRow()][this->getCol()-1] = new Ant(this->getRow(), this->getCol()-1);
        }
}

//*REQUIRES SPACE TO BE PREVIOUSLY VALIDATED*
void Ant::Travel(Creature* (&grid)[NUM_ROWS][NUM_COLS], Creature::Direction dir) {
    //Calculate anticipated space using ant's row, col and direction to move
    int desired_row; //uses 16 more bytes of memory than necessary, but makes code more readable. good tradeoff on these machines.
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

    grid[desired_row][desired_col] = this;
    grid[this->getRow()][this->getCol()] = nullptr;
    this->setPos(desired_row, desired_col);
}

//determines logic for where ant will move (if anywhere) and calls Travel to finish off the move
void Ant::Move(Creature* (&grid)[NUM_ROWS][NUM_COLS]) {

    //initialize neaarest distances in each direction to farthest away
    //anything that exists will have a distance less than the farthest away of 10
    //Set north, east, south, west nearest distance to 10 (max board size)
    int nearest_north = NUM_ROWS;
    int nearest_east = NUM_COLS;
    int nearest_south = NUM_ROWS;
    int nearest_west = NUM_COLS;

    //for all beetles..
    for(int beetle_row = 0; beetle_row < NUM_ROWS; beetle_row++) {
        for(int beetle_col = 0; beetle_col < NUM_COLS; beetle_col++) {
            if(dynamic_cast<Beetle*>(grid[beetle_row][beetle_col])) {

                //check if the beetle we found is closer north than the current closest north
                    //this->row - beetle's row > 0 AND this->col == beetle's col
                        //means that  beetle is north
                    //this->row - beetle's row < nearest_north
                        //means that beetle is the new current closest north
                if( (this->getRow() - beetle_row > 0) && (this->getCol() == beetle_col) && (this->getRow() - beetle_col < nearest_north) ) {
                    //set new nearest north
                    nearest_north = this->getRow() - beetle_row;

                //otherwise, check if the beetle we found is closer east than the current closest east
                    //beetle's col - this->col > 0 AND this->row == beetle's row, means beetle is east
                    //beetle's col - this->col < nearest_east, beetle is the new current closest east
                } else if( (beetle_col - this->getCol() > 0) && (this->getRow() == beetle_row) && (beetle_col - this->getCol() < nearest_east) ) {
                    //set new nearest east
                    nearest_east = beetle_col - this->getCol();

                //otherwise, check if the beetle we found is closer south than the current closest south
                    //beetle's row - this->row > 0 AND this->col == beetle's col, means beetle is south
                    //beetle's row - this->row < nearest_south, means beetle is the new current closest south
                } else if( (beetle_row - this->getRow() > 0) && (this->getCol() == beetle_col) && (beetle_row - this->getRow() < nearest_south) ) {
                    //set new nearest south
                    nearest_south = beetle_row - this->getRow();

                //otherwise, check if the beetle we found is closer east than the current closest west
                    //this->col - beetle's col > 0 AND this->row == beetle's row, means beetle is west
                    //this->col - beetle's col < nearest_west, means beetle is the new current closest west
                } else if( (this->getCol() - beetle_col > 0) && (this->getRow() == beetle_row) && (this->getCol() - beetle_col < nearest_west) ) {
                    //set new nearest west
                    nearest_west = this->getCol() - beetle_col;
                }
            }
        }
    }

            /*if there is no orthogonal beetle (all nearest_directions are still the max of 10),
            just don't move. probably safe for now.*/
             if( (nearest_north == NUM_ROWS) && (nearest_east == NUM_COLS) && (nearest_south == NUM_ROWS) && (nearest_west == NUM_COLS) ) {
                return; //don't move
             }
                /*
                    If there is one shortest distance (not max value)
                        Validate moving in the opposite direction.
                            do so if possible, then exit.
                            otherwise, just exit.
                */
                //if north is the shortest distance and isn't max..
                if( (nearest_north < nearest_east) && (nearest_north < nearest_south) && (nearest_north < nearest_west) && (nearest_north != NUM_ROWS) ) {
                    //check that the opposite (south) direction is ok (not out of bounds, not an ant, not a beetle)
                    if(this->Creature::ValidateMove(grid, Creature::Direction::SOUTH)) {
                        //move into the space
                        this->Travel(grid, Creature::Direction::SOUTH);
                    }
                    return;
                }

                //if east is the shortest distance and isn't max
                if( (nearest_east < nearest_north) && (nearest_east < nearest_south) && (nearest_east < nearest_west) && (nearest_east != NUM_COLS) ) {
                    //check that the opposite (west) direction is ok (not out of bounds, not an ant, not a beetle)
                    if(this->Creature::ValidateMove(grid, Creature::Direction::WEST)) {
                        //move into the space
                        this->Travel(grid, Creature::Direction::WEST);
                    }
                    return;
                }

                //if south is the shortest distance and isn't max
                if( (nearest_south < nearest_north) && (nearest_south < nearest_east) && (nearest_south < nearest_west) && (nearest_south != NUM_ROWS) ) {
                    //check that the opposite (north) direction is ok (not out of bounds, not an ant, not a beetle)
                    if(this->Creature::ValidateMove(grid, Creature::Direction::NORTH)) {
                        //move into the space
                        this->Travel(grid, Creature::Direction::NORTH);
                    }
                    return;
                }

                //if west is the shortest distance and isn't max
                if( (nearest_west < nearest_north) && (nearest_west < nearest_east) && (nearest_west < nearest_south) && (nearest_west != NUM_COLS) ) {
                    //check that the opposite (east) direction is ok (not out of bounds, not an ant, not a beetle)
                    if(this->Creature::ValidateMove(grid, Creature::Direction::EAST)) {
                        //move into the space
                        this->Travel(grid, Creature::Direction::EAST);
                    }
                    return;
                }

                //If there are multiple beetles, look for a direction with no beetles in the order N,E,S,W

                    //if north is at max
                    if(nearest_north == NUM_ROWS) {
                        //validate moving north (FREEDOM!) and do so if possible.
                        if(this->ValidateMove(grid, Creature::Direction::NORTH)) {
                            this->Travel(grid, Creature::Direction::NORTH);
                        }
                        return;
                    }

                    //if east is at max
                    if(nearest_east == NUM_COLS) {
                        //validate moving east (FREEDOM!) and do so if possible.
                        if(this->ValidateMove(grid, Creature::Direction::EAST)) {
                            this->Travel(grid, Creature::Direction::EAST);
                        }
                        return;
                    }

                    //if south is at max
                    if(nearest_east == NUM_COLS) {
                        //validate moving east (FREEDOM!) and do so if possible.
                        if(this->ValidateMove(grid, Creature::Direction::SOUTH)) {
                            this->Travel(grid, Creature::Direction::SOUTH);
                        }
                        return;
                    }

                    //if west is at max
                    if(nearest_east == NUM_COLS) {
                        //validate moving east (FREEDOM!) and do so if possible.
                        if(this->ValidateMove(grid, Creature::Direction::WEST)) {
                            this->Travel(grid, Creature::Direction::WEST);
                        }
                        return;
                    }

                /*If we've gotten this far, that means there are beetles in all directions.
                    We need to move, and we'll move in the direction of the farthest beetle, and using N, E, S, W priority in the case of ties.

                    *first find what the max distance is.
                        *then check if north is equal to the max distance, and move there if it is
                        *repeat for east
                        *then for south
                        *finally with west
                */
                    //find the max distance and store it in max distance.
                    int max_distance = nearest_north;
                    if(nearest_east > max_distance) { max_distance = nearest_east; }
                    if(nearest_south > max_distance) { max_distance = nearest_south; }
                    if(nearest_west > max_distance) { max_distance = nearest_west; }

                    //we now have the max distance, let's check the highest priority move, north, first
                    if(nearest_north == max_distance) {
                        //validate moving north and do so if possible.
                        if(this->ValidateMove(grid, Creature::Direction::NORTH)) {
                            this->Travel(grid, Creature::Direction::NORTH);
                        }
                        return;
                    }

                    //check the next highest priority, east
                    if(nearest_east == max_distance) {
                        //validate moving east and do so if possible.
                        if(this->ValidateMove(grid, Creature::Direction::EAST)) {
                            this->Travel(grid, Creature::Direction::EAST);
                        }
                        return;
                    }

                    //then check if south is the best option
                    if(nearest_south == max_distance) {
                        //validate moving south and do so if possible.
                        if(this->ValidateMove(grid, Creature::Direction::SOUTH)) {
                            this->Travel(grid, Creature::Direction::SOUTH);
                        }
                        return;
                    }

                    //finally check west
                    if(nearest_west == max_distance) {
                        //validate moving east (FREEDOM!) and do so if possible.
                        if(this->ValidateMove(grid, Creature::Direction::WEST)) {
                            this->Travel(grid, Creature::Direction::WEST);
                        }
                        return;
                    }

                    //at this point we must have exited, since max distance had to be equal to one of them.

}

//returns number of ant neighbors so that beetles can optimize movement
int Ant::countNeighbors(Creature* grid[NUM_ROWS][NUM_COLS]) const {
    //start neighbors as -1, since we will count the current space as a neighbor
    int num_neighbors = -1;

    //check the 9 spaces by going through the 3 rows and the 3 cols
    for(int neighbor_row = this->getRow() - 1; neighbor_row <= this->getRow() + 1; neighbor_row++) {
        for(int neighbor_col = this->getCol() - 1; neighbor_col <= this->getCol() + 1; neighbor_col++) {

            //first make sure that the space is within the grid.
                //note the negation of the statement. this will be true if the coordinates are properly bounded
            if(!(neighbor_row < 0 || neighbor_row > 9 || neighbor_col < 0 || neighbor_col > 9)) {
                //if the space is an ant, add one to the neighbor count
                //note: obviously, the space that this ant occupies will be counted. the initialization of -1 accounts for this.
                if(dynamic_cast<Ant*>(grid[neighbor_row][neighbor_col])) {
                    num_neighbors++;
                }
            }
        }
    }

    return num_neighbors;
}
