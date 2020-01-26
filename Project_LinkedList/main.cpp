//Rishi Chandna
//rdc180001
#include <iostream> //cout
#include <fstream> //input file, output file
#include <iomanip> //setprecision

#include "LinkList.h"
#include "Node.h"
#include "Player.h"

using namespace std;

Node<Player>* FindStatisticInsertionPosition(Player* data, Statistic stat, LinkedList<Player>* players) {
    Node<Player>* beforeIter = nullptr;
    Node<Player>* iter = players->getHead();
    if(stat == Statistic::STRIKEOUT) {
        while(iter != nullptr && ((iter->getPayload()->getStat(stat)) < (data->getStat(stat)) )) {
            beforeIter = iter;
            iter = iter->getNext();
        }
        return beforeIter;
    } else {
        while(iter != nullptr && ((iter->getPayload()->getStat(stat)) > (data->getStat(stat)) )) {
            beforeIter = iter;
            iter = iter->getNext();
        }
    return beforeIter;
    }
}

Node<Player>* FindStatisticInsertionPosition(Player* data, DerivedStatistic stat, LinkedList<Player>* players) {
    Node<Player>* beforeIter = nullptr;
    Node<Player>* iter = players->getHead();
    while(iter != nullptr && ((iter->getPayload()->getStat(stat)) > (data->getStat(stat)) )) {
        beforeIter = iter;
        iter = iter->getNext();
    }
    return beforeIter;
}

void sortBy(Statistic stat, LinkedList<Player>* players) {
    if(players->getHead() == nullptr) { return; }
    if(players->getHead()->getNext() == nullptr) {return;}
    Node<Player>* beforeCurrent = players->getHead();
    Node<Player>* current = players->getHead()->getNext();
    Node<Player>* afterCurrent = current->getNext();
    Node<Player>* position;
    //For node : list
    while(current != nullptr) {

        //figure out where to put the current node
        afterCurrent = current->getNext();
        position = FindStatisticInsertionPosition(current->getPayload(), stat, players);

        //check if we can just switch easily with previous
        if(position == beforeCurrent) {
            beforeCurrent = current;
        } else {
            //otherwise remove current node from where it is, and insert it where it should go
            players->removeAfter(beforeCurrent);
            //special case of position being nullptr means it is the smallest element and should go at head
            if(position == nullptr) {
                players->prepend(current);
            } else {
                players->insertAfter(position, current);
            }
        }
        current = afterCurrent;
    }
}

void sortBy(DerivedStatistic stat, LinkedList<Player>* players) {
    if(players->getHead() == nullptr) { return; }
    if(players->getHead()->getNext() == nullptr) {return;}
    Node<Player>* beforeCurrent = players->getHead();
    Node<Player>* current = players->getHead()->getNext();
    Node<Player>* afterCurrent = current->getNext();
    Node<Player>* position;
    //For node : list
    while(current != nullptr) {

        //figure out where to put the current node
        afterCurrent = current->getNext();
        position = FindStatisticInsertionPosition(current->getPayload(), stat, players);

        //check if we can just switch easily with previous
        if(position == beforeCurrent) {
            beforeCurrent = current;
        } else {
            //otherwise remove current node from where it is, and insert it where it should go
            players->removeAfter(beforeCurrent);
            //special case of position being nullptr means it is the smallest element and should go at head
            if(position == nullptr) {
                players->prepend(current);
            } else {
                players->insertAfter(position, current);
            }
        }
        current = afterCurrent;
    }
}

//returns pointer to the node with a player with that name, or nullptr if the player doesn't exist yet
Player* PlayerAlreadyExists(LinkedList<Player>* players, string name) {
    //handle case with empty list
    if(players->isEmpty()) { return nullptr; }

    //Create a node pointer to traverse the list, set it to the list's head
    Node<Player>* iter = players->getHead();

    //match case for proper string comparison. don't edit name directly, but have a lowercase version of each.
    string existing_name = iter->getPayload()->getName();
    string new_name = name;
    int i = 0;
    while(existing_name[i]) {
        existing_name[i] = tolower(existing_name[i]);
        i++;
    }
    i = 0;
    while(new_name[i]) {
        new_name[i] = tolower(new_name[i]);
        i++;
    }
    //while the pointer's next's payloads getname isn't the name passed in
    while(existing_name != new_name) {
        //move along
        iter = iter->getNext();
        //if we've moved past the tail, don't move along. player doesn't exist yet
        if(iter == nullptr) {
            return nullptr;
        }
        //set up lowercase string for next iteration comparison
        existing_name = iter->getPayload()->getName();
        i = 0;
        while(existing_name[i]) {
            existing_name[i] = tolower(existing_name[i]);
            i++;
        }

    }

    //only exited the while loop if we found the player to already exist
    return iter->getPayload();
}

void ParsePlayer(Player* player, string record) {
    //for char : input data string
    for(unsigned int i = 0; i < record.length(); i++) {
        //checks letter through the results map
        //updates proper array indexed by results map row and player index col
        char current_letter = record.at(i);

        //check validity of character against possible characters
        //increment corresponding stat
        if(current_letter == 'H') {
            player->incStat(Statistic::HIT);
        } else if(current_letter == 'O') {
            player->incStat(Statistic::OUT);
        } else if(current_letter == 'K') {
            player->incStat(Statistic::STRIKEOUT);
        } else if(current_letter == 'W') {
            player->incStat(Statistic::WALK);
        } else if(current_letter == 'P') {
            player->incStat(Statistic::HIT_BY_PITCH);
        } else if(current_letter == 'S') {
            player->incStat(Statistic::SACRIFICE);
        } //if anything else, not valid character, do nothing.
    }

    //we have all the info necessary to calculate ob% and batting average and whatnot right now, but no need to store them.

}

void ParseFile(ifstream &input, LinkedList<Player>* players) {

    string prev_line = ""; //used to exit when file contains newlines
    string line;
    //While not eof
    while(!input.eof()) {
        //Read name
        input >> line;
        if(line == prev_line) { break; }
        //Create a new player, equal to a call to PlayerAlreadyExists, passing in the name just parsed
        Player* new_player = PlayerAlreadyExists(players, line);
        bool alreadyExists = true;
        //if the player didn't exist, make it
        if(new_player == nullptr) {
            new_player = new Player(line);
            alreadyExists = false;
        }

        //get the rest of the line (the batting record)
        input.ignore(); //skip the space
        getline(input, line);
        prev_line = line; //used to check for end of file at next iteration

        //call parseplayer with the pointer to the player and the rest of the line

        ParsePlayer(new_player, line);

        //append the new player to the list
        if(!alreadyExists) {
            players->append(new_player);
        }
    }
}

void DisplayPlayerStats(LinkedList<Player>* players, ofstream& output) {
    //use player < operator overload and linkedlist sort function to default to sort alphabetically by name
    //players->sort();

    output << fixed << setprecision(3);

    //for player : list
    Node<Player>* iter = players->getHead();
    while(iter != nullptr) {
        //output the fields in the order below with a tab between each field
        //name : at-bats : hits : walks : strikeouts : hit by pitch : sacrifice : batting average : on base percent
        output << iter->getPayload()->getName() <<
        "\t" << iter->getPayload()->getAtBats() <<
        "\t" << iter->getPayload()->getStat(Statistic::HIT) <<
        "\t" << iter->getPayload()->getStat(Statistic::WALK) <<
        "\t" << iter->getPayload()->getStat(Statistic::STRIKEOUT) <<
        "\t" << iter->getPayload()->getStat(Statistic::HIT_BY_PITCH) <<
        "\t" << iter->getPayload()->getStat(Statistic::SACRIFICE) <<
        "\t" << iter->getPayload()->getBattingAverage() <<
        "\t" << iter->getPayload()->getOBPercent() << endl;

        //move along to next player
        iter = iter->getNext();
    }
}

void DisplayStatLeaders(LinkedList<Player>* players, ofstream& output, DerivedStatistic stat, string header) {
    sortBy(stat, players);
    output << endl << header << endl;

    int players_printed = 0;
    string names_to_print = "";
    LinkedList<Player>* to_print = new LinkedList<Player>();
    Node<Player>* next_highest = players->getHead();
    double high_score = players->getHead()->getPayload()->getStat(stat);
    Node<Player>* name_iterator;
    int max_players_to_print = 3;
    if(players->length() < 3) { max_players_to_print = players->length();}

    while(players_printed < max_players_to_print ) {
        //flush printing array
        while(to_print->length() != 0) {
            to_print->removeAfter(nullptr);
        }
        high_score = next_highest->getPayload()->getStat(stat);
        while(next_highest != nullptr && next_highest->getPayload()->getStat(stat) == high_score) {
            to_print->append(next_highest->getPayload());

            next_highest = next_highest->getNext();
            if(next_highest == nullptr) {break;}
        }
        to_print->sort();

        players_printed+= to_print->length();
        name_iterator = to_print->getHead();
        names_to_print = name_iterator->getPayload()->getName();
        while(name_iterator != nullptr) {
            if(to_print->getHead() != name_iterator){
                names_to_print += ", " + name_iterator->getPayload()->getName();
            }

            name_iterator = name_iterator->getNext();
        }
        output << high_score << "\t" << names_to_print << endl;
    }

    //clean up memory! #NoLeaks2k19
    delete to_print;
}
void DisplayStatLeaders(LinkedList<Player>* players, ofstream& output, Statistic stat, string header) {
    sortBy(stat, players); //get the first place at head, second place at head->next etc.
    output << endl << header << endl;

    //prep lots of stuff to use. sad about so much memory, but afaik it's required.
    int players_printed = 0;
    string names_to_print = "";
    LinkedList<Player>* to_print = new LinkedList<Player>(); //collects all first place players/second place players etc.
                                            //handy because we can use the alphabetical sort of our linkedlist
    Node<Player>* next_highest = players->getHead(); //used for moving through the big player array.
    int high_score = players->getHead()->getPayload()->getStat(stat);
    Node<Player>* name_iterator; //used for moving through the to_print list.
    int max_players_to_print = 3; //used as an exit condition

    //want to display UP TO 3, so less is ok if there aren't as many.
    if(players->length() < 3) { max_players_to_print = players->length();} //IF THERE'S 1 PLAYER, DON'T PRINT THEIR NAME 3 TIMES!!

    while(players_printed < max_players_to_print ) {
        //flush printing list
        while(to_print->length() != 0) {
            to_print->removeAfter(nullptr); //uses special case for removing head.
        }

        //figure out what score a player needs to be in nth place
        high_score = next_highest->getPayload()->getStat(stat);

        //go through all players. don't go past the end, stop when we find a player that is below nth place
        while(next_highest != nullptr && next_highest->getPayload()->getStat(stat) == high_score) {
            to_print->append(next_highest->getPayload()); //add it to list of what we need to print
            players_printed++;                      //keep track of going up to 3 places
            next_highest = next_highest->getNext();      //keep going through the list
            if(next_highest == nullptr) {break;}    //stop at the end.
        }

        //get alphabetical order of nth place players to print properly.
        to_print->sort();

        //iterate through to_print, first name as is
        //prepend any other names with comma space
        name_iterator = to_print->getHead();
        names_to_print = name_iterator->getPayload()->getName();
        while(name_iterator != nullptr) {
            if(to_print->getHead() != name_iterator){
                names_to_print += ", " + name_iterator->getPayload()->getName();
            }

            name_iterator = name_iterator->getNext();
        }

        //print the nth place line.
        output << high_score << "\t" << names_to_print << endl;
    }

}

void DisplayLeaders(LinkedList<Player>* players, ofstream& output) {
    output << endl;
    output << "LEAGUE LEADERS";


    DisplayStatLeaders(players, output, DerivedStatistic::BAT_AVG, "BATTING AVERAGE");
    DisplayStatLeaders(players, output, DerivedStatistic::OB_PERCENT, "ON-BASE PERCENTAGE");
    DisplayStatLeaders(players, output, Statistic::HIT, "HITS");
    DisplayStatLeaders(players, output, Statistic::WALK, "WALKS");
    DisplayStatLeaders(players, output, Statistic::STRIKEOUT, "STRIKEOUTS");
    DisplayStatLeaders(players, output, Statistic::HIT_BY_PITCH, "HIT BY PITCH");
    output << endl;
}

void checkMemLeak() {
    for(int i = 0; i < 100000000; i++) {
        LinkedList<int>* integers = new LinkedList<int>();
        integers->append(4);
        integers->removeAfter(nullptr);
        delete integers;
    }
}
int main()
{

    checkMemLeak();
    system("pause");
    cout << "done" << endl;
    return 0;

    //Initialize linked list of players, all empty and clean
    LinkedList<Player>* players = new LinkedList<Player>();

    //Read in input filename and validate until the file can be opened
    string filenames;

    cin >> filenames;
    ifstream input(filenames);

    while(!input.is_open()) {
        cin >> filenames;
        input.open(filenames);
    }

    //create output stream with predefined name "leaders.txt"
    ofstream output("leaders.txt");

    //we now have io setup.

    //Call ParseFile, giving input file stream (by reference) and pass linked list by reference
    ParseFile(input, players);

    //we now have all the data in our linkedlist

    //sort alphabetically
    players->sort();

    //display the individual players
    DisplayPlayerStats(players, output);

    //display the leaders
    DisplayLeaders(players, output);


    //Clean up pointers and streams
    input.close();
    output.close();
    delete players;

    return 0;
}
