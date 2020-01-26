//Rishi Chandna
//rdc180001

#include "Beetle.h"
#include "Ant.h"

#include <iostream>

Beetle::Beetle() //could move setNewborn to creature constructor/actually use creature constructor
{
    this->setRow(-1);
    this->setCol(-1);
    this->setEnergyFull();
    this->setNewborn(true);
}

Beetle::Beetle(int _row, int _col) {
    this->setRow(_row);
    this->setCol(_col);
    this->setEnergyFull();
    this->setNewborn(true);
}


Beetle::~Beetle() //no real need for a destructor
{
    //dtor
}

//differs from Creature::ValidateMove in that Creature's implementation is strictly empty/nullptr
//the beetle version is ok with having an ant in the space, since beetles can eat ants. used for beetle movement
bool Beetle::ValidateMove(Creature* grid[NUM_ROWS][NUM_COLS], Creature::Direction dir) {
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

    //if the pointer in the grid at the desired position is a beetle, return false
    //ie, return true if the pointer isn't a beetle. ants and nullptrs are all good.
    return !dynamic_cast<Beetle*>(grid[desired_row][desired_col]);

}

//actually handles moving the grid pointers so that it appears as though the beetle has moved (and also didn't duplicate)
void Beetle::Travel(Creature* (&grid)[NUM_ROWS][NUM_COLS], Creature::Direction dir) {
    //Calculate anticipated space using beetles row, col and direction to move
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

    //if ant is in desired space..

    if(dynamic_cast<Ant*>(grid[desired_row][desired_col])) {
        //we eat the ant, so refill energy to full+1, so that we survive the starve phase properly
        this->eatAnt();
    }

    grid[desired_row][desired_col] = this;
    grid[this->getRow()][this->getCol()] = nullptr;
    this->setPos(desired_row, desired_col);

}
/** \brief
 *
 * @param p1 ants vector is all the ants that are on the game board. Breed uses the positions held in this vector to make sure that this ant doesn't breed on top of another ant. also the breeded ant gets pushed to this vector
 * @param p1 beetles vector is all the beetles that are on the game board. Breed uses the positions held in this vector to make sure that this ant doesn't breed on top of a beetle
 * @return doesn't return anything, modifies the ants vector directly if this ant can breed
 *
 */

void Beetle::Breed(Creature* (&grid)[NUM_ROWS][NUM_COLS]) { //takes in vector of beetles and vector of ants

        //Using beetle's location…
            //validate spots in order given (N, E, S, W)
            //add an ant to the vector at the first open spot
            //exit
        if(this->Creature::ValidateMove(grid, Creature::Direction::NORTH)) { //try north spot
            Beetle* babyBeetle = new Beetle(this->getRow()-1, this->getCol());
            grid[babyBeetle->getRow()][babyBeetle->getCol()] = babyBeetle;
            //delete babyAnt;
        } else if(this->Creature::ValidateMove(grid, Creature::Direction::EAST)) { //try east spot
            Beetle* babyBeetle = new Beetle(this->getRow(), this->getCol()+1);
            grid[babyBeetle->getRow()][babyBeetle->getCol()] = babyBeetle;
            //delete babyAnt;
        } else if(this->Creature::ValidateMove(grid, Creature::Direction::SOUTH)) { // try south spot
            Beetle* babyBeetle = new Beetle(this->getRow()+1, this->getCol());
            grid[babyBeetle->getRow()][babyBeetle->getCol()] = babyBeetle;
            //delete babyAnt;
        } else if(this->Creature::ValidateMove(grid, Creature::Direction::WEST)) { //try west spot
            Beetle* babyBeetle = new Beetle(this->getRow(), this->getCol()-1);
            grid[babyBeetle->getRow()][babyBeetle->getCol()] = babyBeetle;
            //delete babyAnt;
        }
}

void Beetle::Move(Creature* (&grid)[NUM_ROWS][NUM_COLS]) { //takes in vector of beetles and vector of ants
    //initialize neaarest distances in each direction to farthest away
    //anything that exists will have a distance less than the farthest away of 10
    int nearest_north = NUM_ROWS;
    int nearest_east = NUM_COLS;
    int nearest_south = NUM_ROWS;
    int nearest_west = NUM_COLS;

    //define number of neighbors in each direction
    int north_neighbors = 0, east_neighbors = 0, south_neighbors = 0, west_neighbors = 0;

    //for all ants...
    for(int ant_row = 0; ant_row < NUM_ROWS; ant_row++) {
        for(int ant_col = 0; ant_col < NUM_COLS; ant_col++) {
            if(dynamic_cast<Ant*>(grid[ant_row][ant_col])) {
                Ant ant_in_question = *dynamic_cast<Ant*>(grid[ant_row][ant_col]);

                //check if the ant in question is closer north than the current closest north
                    //this->row - ant's row > 0 AND this->col == ant's col, ant is north
                    //this->row - ant's row < nearest_north, ant is the new current closest north
                if( (this->getRow() - ant_row > 0) && (this->getCol() == ant_col) && (this->getRow() - ant_row < nearest_north) ) {
                    //set new nearest north
                    nearest_north = this->getRow() - ant_row;
                    //set north neighbors
                    north_neighbors = ant_in_question.countNeighbors(grid);

                //otherwise, check if the ant in question is closer east than the current closest east
                    //ant's col - this->col > 0 AND this->row == ant's row, means ant is east
                    //ant's col - this->col < nearest_east, ant is the new current closest east
                } else if( (ant_col - this->getCol() > 0) && (this->getRow() == ant_row) && (ant_col - this->getCol() < nearest_east) ) {
                    //set new nearest east
                    nearest_east = ant_col - this->getCol();
                    //set east neighbors
                    east_neighbors = ant_in_question.countNeighbors(grid);

                //otherwise, check if the ant in question is closer south than the current closest south
                    //ant's row - this->row > 0 AND this->col == ant's col, means ant is south
                    //ant's row - this->row < nearest_south, means ant is the new current closest south
                } else if( (ant_row - this->getRow() > 0) && (this->getCol() == ant_col) && (ant_row - this->getRow() < nearest_south) ) {
                    //set new nearest south
                    nearest_south = ant_row - this->getRow();
                    //set south neighbors
                    south_neighbors = ant_in_question.countNeighbors(grid);

                //otherwise, check if the ant in question is closer east than the current closest west
                    //this->col - ant's col > 0 AND this->row == ant's row, means ant is west
                    //this->col - ant's col < nearest_west, means ant is the new current closest west
                } else if( (this->getCol() - ant_col > 0) && (this->getRow() == ant_row) && (this->getCol() - ant_col < nearest_west) ) {
                    //set new nearest west
                    nearest_west = this->getCol() - ant_col;
                    //set west neighbors
                    west_neighbors = ant_in_question.countNeighbors(grid);
                }
            }
        }
    }

            /*if there is no ant, move to farthest edge using priority N, E, S, W for ties */
             if( (nearest_north == NUM_ROWS) && (nearest_east == NUM_COLS) && (nearest_south == NUM_ROWS) && (nearest_west == NUM_COLS) ) {
                //distance to north wall is this->row+1
                //distance to east wall is NUM_COLS - this->col
                //distance to south wall is NUM_ROWS - this->row
                //distance to west wall is this->col+1

                //if north is the most or tied..
                if( ((this->getRow()+1) >= (NUM_COLS - this->getCol())) && ((this->getRow()+1) >= (NUM_ROWS - this->getRow())) && ((this->getRow()+1) >= (this->getCol()+1)) ) {
                    //move north
                    //check that the space is either empty or an ant
                    if(this->Beetle::ValidateMove(grid, Creature::Direction::NORTH)) {
                        //move into the space and eat the ant if there is one
                        this->Travel(grid, Creature::Direction::NORTH);
                    }
                    return;
                }

                //if east is the most or tied with south and west
                if( ((NUM_COLS - this->getCol()) > (this->getRow()+1)) && ((NUM_COLS - this->getCol()) >= (NUM_ROWS - this->getRow())) && ((NUM_COLS - this->getCol()) >= (this->getCol()+1)) ) {
                    //move east
                    //check that the space is either empty or an ant
                    if(this->Beetle::ValidateMove(grid, Creature::Direction::EAST)) {
                        //move into the space and eat the ant if there is one
                        this->Travel(grid, Creature::Direction::EAST);
                    }
                    return;
                }

                //if south is the most or tied with west
                if( ((NUM_ROWS - this->getRow()) > (this->getRow()+1)) && ((NUM_ROWS - this->getRow()) > (NUM_COLS - this->getCol())) && ((NUM_ROWS - this->getRow()) >= (this->getCol()+1)) ) {
                    //move south
                    //check that the space is either empty or an ant
                    if(this->Beetle::ValidateMove(grid, Creature::Direction::SOUTH)) {
                        //move into the space and eat the ant if there is one
                        this->Travel(grid, Creature::Direction::SOUTH);
                    }
                    return;
                }

                //if west is the most
                if( ((this->getCol()+1) > (this->getRow()+1)) && ((this->getCol()+1) > (NUM_COLS - this->getCol())) && ((this->getCol()+1) > (NUM_ROWS - this->getRow())) ) {
                    //move west
                    //check that the space is either empty or an ant
                    if(this->Beetle::ValidateMove(grid, Creature::Direction::WEST)) {
                        //move into the space and eat the ant if there is one
                        this->Travel(grid, Creature::Direction::WEST);
                    }
                    return;
                }

             }
                /*
                    If there is one shortest distance (not max value)
                        Beetle::Validate space in that direction
                            If true, Beetle::Travel with that direction
                            Otherwise exit
                */
                //if north is the shortest distance and isn't max..
                if( (nearest_north < nearest_east) && (nearest_north < nearest_south) && (nearest_north < nearest_west) && (nearest_north != NUM_ROWS) ) {
                    //check that the space is either empty or an ant
                    if(this->Beetle::ValidateMove(grid, Creature::Direction::NORTH)) {
                        //move into the space and eat the ant if there is one
                        this->Travel(grid, Creature::Direction::NORTH);
                    }
                    return;
                }
                //if east is the shortest distance and isn't max
                if( (nearest_east < nearest_north) && (nearest_east < nearest_south) && (nearest_east < nearest_west) && (nearest_east != NUM_COLS) ) {
                    //check that the space is either empty or an ant
                    if(this->Beetle::ValidateMove(grid, Creature::Direction::EAST)) {
                        //move into the space and eat the ant if there is one
                        this->Travel(grid, Creature::Direction::EAST);
                    }
                    return;
                }
                //if south is the shortest distance and isn't max
                if( (nearest_south < nearest_north) && (nearest_south < nearest_east) && (nearest_south < nearest_west) && (nearest_south != NUM_ROWS) ) {
                    //check that the space is either empty or an ant
                    if(this->Beetle::ValidateMove(grid, Creature::Direction::SOUTH)) {
                        //move into the space and eat the ant if there is one
                        this->Travel(grid, Creature::Direction::SOUTH);
                    }
                    return;
                }
                //if west is the shortest distance and isn't max
                if( (nearest_west < nearest_north) && (nearest_west < nearest_east) && (nearest_west < nearest_south) && (nearest_west != NUM_COLS) ) {
                    //check that the space is either empty or an ant
                    if(this->Beetle::ValidateMove(grid, Creature::Direction::WEST)) {
                        //move into the space and eat the ant if there is one
                        this->Travel(grid, Creature::Direction::WEST);
                    }
                    return;
                }

                //If there 2 or 3 or 4 shortest distances, not max board size
                    //if there is a direction with a unique highest neighbor count
                        //try to move there
                        //north, east. east, south. south, west. west, north. north, south. east, west.
                        //3 way tie: N lose, E lose, S lose, W lose
                    //if a distance tie between north and east
                    if( (nearest_north == nearest_east) && (nearest_north < nearest_south) && (nearest_north < nearest_west) ) {
                        //move north if there's more neighbors, OR if there's a tie
                        if(north_neighbors >= east_neighbors) {
                            //move north
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::NORTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::NORTH);
                            }
                            return;

                        } else {
                            //move east
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::EAST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::EAST);
                            }
                            return;
                        }
                    }

                    //if a distance tie between east and south
                    if( (nearest_east == nearest_south) && (nearest_east < nearest_north) && (nearest_east < nearest_west) ) {
                        //move east if there's more neighbors, OR if there's a tie
                        if(east_neighbors >= south_neighbors) {
                            //move east
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::EAST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::EAST);
                            }
                            return;

                        } else {
                            //move south
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::SOUTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::SOUTH);
                            }
                            return;
                        }
                    }

                    //if a distance tie between south and west
                    if( (nearest_south == nearest_west) && (nearest_south < nearest_north) && (nearest_south < nearest_east) ) {
                        //move south if there's more neighbors, OR if there's a tie
                        if(south_neighbors >= west_neighbors) {
                            //move south
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::SOUTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::SOUTH);
                            }
                            return;

                        } else {
                            //move west
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::WEST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::WEST);
                            }
                            return;
                        }
                    }

                    //if a distance tie between north and west
                    if( (nearest_north == nearest_west) && (nearest_north < nearest_east) && (nearest_north < nearest_south) ) {
                        //move north if there's more neighbors, OR if there's a tie
                        if(north_neighbors >= west_neighbors) {
                            //move north
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::NORTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::NORTH);
                            }
                            return;

                        } else {
                            //move west
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::WEST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::WEST);
                            }
                            return;
                        }
                    }

                    //if a distance tie between north and south
                    if( (nearest_north == nearest_south) && (nearest_north < nearest_east) && (nearest_north < nearest_west) ) {
                        //move north if there's more neighbors, OR if there's a tie
                        if(north_neighbors >= south_neighbors) {
                            //move north
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::NORTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::NORTH);
                            }
                            return;

                        } else {
                            //move south
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::SOUTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::SOUTH);
                            }
                            return;
                        }
                    }

                    //if a distance tie between east and west
                    if( (nearest_east == nearest_west) && (nearest_east < nearest_north) && (nearest_east < nearest_south) ) {
                        //move north if there's more neighbors, OR if there's a tie
                        if(east_neighbors >= west_neighbors) {
                            //move east
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::EAST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::EAST);
                            }
                            return;

                        } else {
                            //move west
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::WEST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::WEST);
                            }
                            return;
                        }
                    }

                    //3 way tie, north is the farthest away
                    if( (nearest_east == nearest_south) && (nearest_south == nearest_west) && (nearest_east < nearest_north) ) {
                        //if east neighbors is the most, or tied
                        if( (east_neighbors >= south_neighbors) && (east_neighbors >= west_neighbors) ) {
                            //move east
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::EAST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::EAST);
                            }
                            return;
                            //otherwise, if south neighbors is the most, or tied
                        } else if( (south_neighbors > east_neighbors) && (south_neighbors >= west_neighbors) ) {
                            //move south
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::SOUTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::SOUTH);
                            }
                            return;
                        } else {
                            //move west
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::WEST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::WEST);
                            }
                            return;
                        }
                    }

                    //3 way tie, east is the farthest away
                    if( (nearest_north == nearest_south) && (nearest_south == nearest_west) && (nearest_north < nearest_east) ) {
                        //if north neighbors is the most, or tied
                        if( (north_neighbors >= south_neighbors) && (north_neighbors >= west_neighbors) ) {
                            //move north
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::NORTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::NORTH);
                            }
                            return;
                            //otherwise, if south neighbors is the most, or tied
                        } else if( (south_neighbors > north_neighbors) && (south_neighbors >= west_neighbors) ) {
                            //move south
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::SOUTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::SOUTH);
                            }
                            return;
                        } else {
                            //move west
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::WEST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::WEST);
                            }
                            return;
                        }
                    }

                    //3 way tie, south is the farthest away
                    if( (nearest_north == nearest_east) && (nearest_east == nearest_west) && (nearest_north < nearest_south) ) {
                        //if north neighbors is the most, or tied
                        if( (north_neighbors >= east_neighbors) && (north_neighbors >= west_neighbors) ) {
                            //move north
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::NORTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::NORTH);
                            }
                            return;
                            //otherwise, if east neighbors is the most, or tied
                        } else if( (east_neighbors > north_neighbors) && (east_neighbors >= west_neighbors) ) {
                            //move east
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::EAST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::EAST);
                            }
                            return;
                        } else {
                            //move west
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::WEST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::WEST);
                            }
                            return;
                        }
                    }

                    //3 way tie, west is the farthest away
                    if( (nearest_north == nearest_east) && (nearest_east == nearest_south) && (nearest_north < nearest_west) ) {
                        //if north neighbors is the most, or tied
                        if( (north_neighbors >= east_neighbors) && (north_neighbors >= south_neighbors) ) {
                            //move north
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::NORTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::NORTH);
                            }
                            return;
                            //otherwise, if east neighbors is the most, or tied
                        } else if( (east_neighbors > north_neighbors) && (east_neighbors >= south_neighbors) ) {
                            //move east
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::EAST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::EAST);
                            }
                            return;
                        } else {
                            //move south
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::SOUTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::SOUTH);
                            }
                            return;
                        }
                    }

                    //4 way tie
                    if( (nearest_north == nearest_east) && (nearest_east == nearest_south) && (nearest_south == nearest_west) ) {
                        //if north neighbors is the most, or tied
                        if( (north_neighbors >= east_neighbors) && (north_neighbors >= south_neighbors) && (north_neighbors >= west_neighbors)) {
                            //move north
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::NORTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::NORTH);
                            }
                            return;
                            //otherwise, if east neighbors is the most, or tied
                        } else if( (east_neighbors > north_neighbors) && (east_neighbors >= south_neighbors) && (east_neighbors >= west_neighbors)) {
                            //move east
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::EAST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::EAST);
                            }
                            return;
                            //otherwise, if south neighbors is the most, or tied
                        } else if( (south_neighbors > north_neighbors) && (south_neighbors > east_neighbors) && (south_neighbors >= west_neighbors)) {
                            //move south
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::SOUTH)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::SOUTH);
                            }
                            return;
                        } else {
                            //move west
                            if(this->Beetle::ValidateMove(grid, Creature::Direction::WEST)) {
                                //move into the space and eat the ant if there is one
                                this->Travel(grid, Creature::Direction::WEST);
                            }
                            return;
                        }
                    }



}

//gets called on every beetle every turn (except newborns)
bool Beetle::Starve() {
    energy--;
    return energy == 0;
}

