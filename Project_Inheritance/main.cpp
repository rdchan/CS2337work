//Rishi Chandna
//rdc180001

#include <iostream> //cout
#include <fstream>  //ifsream, ostream

#include "Creature.h"
#include "Ant.h"
#include "Beetle.h"

#define NUM_ROWS 10
#define NUM_COLS 10

using namespace std;

void OutputHeaderAndBoard(Creature* grid[NUM_ROWS][NUM_COLS], char ant_char, char beetle_char, int turn_num) {
    cout << "TURN " << turn_num << endl;
    for(int row = 0; row < NUM_ROWS; row++) {
        for(int col = 0; col < NUM_COLS; col++) {
            if(grid[row][col] == nullptr) {
                cout << " ";
            }else if(dynamic_cast<Ant*>(grid[row][col])) {
                cout << ant_char;
            } else if(dynamic_cast<Beetle*>(grid[row][col])) {
                cout << beetle_char;
            }
        }
        cout << endl;
    }
    cout << endl;
}

void addCreature(Creature* (&grid)[NUM_ROWS][NUM_COLS], Creature* new_creature) {
    grid[new_creature->getRow()][new_creature->getCol()] = new_creature;
}

void ResetTurn(Creature* (&grid)[NUM_ROWS][NUM_COLS]) {
    //reset the flag that disables creatures from moving twice in one turn
    for(int col = 0;  col < NUM_COLS; col++) {
        for(int row = 0; row < NUM_ROWS; row++) {
            if(grid[row][col] != nullptr) {
                grid[row][col]->setMovedThisTurn(false);
                grid[row][col]->setNewborn(false);
            }
        }
    }
}

void MoveBeetles(Creature* (&grid)[NUM_ROWS][NUM_COLS]) {
    //go through grid from left to right/top to bottom
    for(int col = 0; col < NUM_COLS; col++) {
        for(int row = 0; row < NUM_ROWS; row++) {
            //if the space is a beetle
            if(dynamic_cast<Beetle*>(grid[row][col])) {
                //and that beetle hasn't moved yet this turn
                if(!grid[row][col]->hasMoved()) {
                    //let the beetle move, but make sure it can't move again this turn.
                    grid[row][col]->setMovedThisTurn(true);
                    grid[row][col]->Move(grid);
                }
            }
        }
    }
}

void MoveAnts(Creature* (&grid)[NUM_ROWS][NUM_COLS]) {
    //go through the grid from left to right/top to bottom
    for(int col = 0; col < NUM_COLS; col++) {
        for(int row = 0; row < NUM_ROWS; row++) {
            //if a space is an ant
            if(dynamic_cast<Ant*>(grid[row][col])) {
                //and that ant hasn't moved yet this turn
                if(!grid[row][col]->hasMoved()) {
                    //let the ant move, and make sure it can't move again this turn.
                    grid[row][col]->setMovedThisTurn(true);
                    grid[row][col]->Move(grid);
                }
            }
        }
    }
}

void StarveBeetles(Creature* (&grid)[NUM_ROWS][NUM_COLS]) {
    //Beetles starve
    //go through the grid from left to right/top to bottom
    for(int col = 0; col < NUM_COLS; col++) {
        for(int row = 0; row < NUM_ROWS; row++) {
            //if the space is a beetle
            if(dynamic_cast<Beetle*>(grid[row][col])) {

                //don't starve newborns.
                if(!grid[row][col]->isNewborn()) {
                    //run the starve function on the beetle. this will decrement energy, AND return true if the beetle runs out of energy
                    if(dynamic_cast<Beetle*>(grid[row][col])->Starve()) {
                        //passing the previous statement means that the beetle is out of energy and should die. kill it.
                        grid[row][col] = nullptr;
                    }
                }
            }
        }
    }
}

void BreedAnts(Creature* (&grid)[NUM_ROWS][NUM_COLS], int turn) {

    //on turns 3, 6, 9, 12 etc,...
    if(turn %3 == 0) {
        //Ants breed
        //traverse left to right/top to bottom
        for(int col = 0; col < NUM_COLS; col++) {
            for(int row = 0; row < NUM_ROWS; row++) {
                //if the space is an ant
                if(dynamic_cast<Ant*>(grid[row][col])) {
                    //if the ant wasn't made this turn (actually "survived" the turn)
                    if(!grid[row][col]->isNewborn()) {
                        //let the ant try to breed
                        grid[row][col]->Breed(grid);
                    }
                }
            }
        }
    }
}

void BreedBeetles(Creature* (&grid)[NUM_ROWS][NUM_COLS], int turn) {
    //on turns 8, 16, 24, etc..
    if(turn%8 == 0) {
        //Beetles breed
        //traverse L to R, top to bot
        for(int col = 0; col < NUM_COLS; col++) {
            for(int row = 0; row < NUM_ROWS; row++) {
                //if the space is a beetle..
                if(dynamic_cast<Beetle*>(grid[row][col])) {

                    //and isn't a newborn (actually "survived" the turn)
                    if(!grid[row][col]->isNewborn()) {
                        //let it try to breed.
                        grid[row][col]->Breed(grid);
                    }
                }
            }
        }
    }
}

void PopulateGrid(Creature* (&grid)[NUM_ROWS][NUM_COLS]) {
    //open input file
    string in_data; //acts as filename first, then the row to parse after
    cin >> in_data;

    ifstream input(in_data);

    int row = -1; //keeps track of line number/row number
    //while not eof
    while(!input.eof()) {
        //take in row
        row++;
        getline(input, in_data);

        //go through each individual character
        for(unsigned int col = 0; col < in_data.length(); col++) {
            char poss_creature = in_data.at(col);
            if(poss_creature == 'a') {
                grid[row][col] = new Ant(row, col);
            } else if(poss_creature == 'B') {
                grid[row][col] = new Beetle(row, col);
            }
        }
    }

    //close input file
    input.close();

}

int main()
{
    //create 2d array of creature pointers
    Creature* grid[NUM_ROWS][NUM_COLS] = {nullptr};

    //read in file and fill grid
    PopulateGrid(grid);

    //read in characters to use for output
    char ant_char;
    cin >> ant_char;
    char beetle_char;
    cin >> beetle_char;

    //read in number of turns to simulate
    int num_turns;
    cin >> num_turns;

    //For 1 : number of turns (use 1 to make divisibility easier for breeding)
    for(int i = 1; i <= num_turns; i++) {

        ResetTurn(grid); //deals with flag that prevents creatures from moving twice in one turn and prevents newborn starving

        MoveBeetles(grid);

        MoveAnts(grid);

        StarveBeetles(grid);

        BreedAnts(grid, i);

        BreedBeetles(grid, i);

        OutputHeaderAndBoard(grid, ant_char, beetle_char, i);
    }

    //clean up pointers
    for(int i = 0; i < NUM_ROWS; i++) {
        for(int j = 0; j < NUM_COLS; j++) {
            delete grid[i][j];
        }
    }

    return 0;
}
