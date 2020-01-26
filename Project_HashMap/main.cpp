//Rishi Chandna
//rdc180001
#include <iostream> //cout
#include <fstream> //input file, output file
#include <iomanip> //setprecision
#include <algorithm> //vector sort with flexible comparison function

#include "HashMap.h"
#include "Player.h"

using namespace std;

void ParseFile(ifstream &input, HashTable<Player> &players, HashTable<Statistic> &decode) {

    string prev_line = ""; //used to exit when file contains newlines
    string line;
    bool isHome; //all of these
    string name; //are used to hold
    Statistic* play; //information parsed from the line
    string play_parse; //and create or update a player

    //go through the file
    while(getline(input, line)) {
        //if some buggy last line repeat happens, ignore it and exit
        if(line == "" || prev_line == line) {
            break;
        }

        //grab the first character for which team the player is on
        if(line.at(0) == 'A') {
            isHome = false;
        } else {
            isHome = true;
        }

        //grab name. starts after the space, and goes to the next space
        name = line.substr(2, line.find(" ", 3)-2);

        //grab the play code. start at the second space, go to the end of the line
        play_parse = line.substr(line.find(" ", 3)+1);

        //clean any garbage at the end of the line, spaces or \r characters
        for(unsigned int i = 0; i < play_parse.length(); i++) {
            if(play_parse.at(i) == ' ' || play_parse.at(i) == '\r') {
                play_parse.erase(i);
                i--;
            }
        }

        //use the decode hash table to quickly look up which statistic the given play corresponds to
        play = decode[play_parse];

        //players[name] will return a pointer to the player with that name.
        //if the player doesn't exist yet, it returns nullptr
        if(players[name] == nullptr) { //in the event of a new player
            Player* to_insert = new Player(name);
            to_insert->incStat(*play);
            to_insert->setTeam(isHome);
            players.Insert(to_insert, name);
        } else { //in the event that we already have a player, just edit the stat that this line deals with
            players[name]->incStat(*play);
        }

        prev_line = line; //used for buggy last line repeat
    }

}

//used for the tabulated print of everyones stats
void DisplayPlayerStats(std::vector<Player*> player_vec, ofstream& output) {
    //use player < operator overload and linkedlist sort function to default to sort alphabetically by name
    //player_vec is already sorted team-alphabetically before it gets passed in

    output << fixed << setprecision(3);

    //take care of the away header first
    output << "AWAY" << endl;
    bool printed_home_header = false; //used to print the home header once and only once

    for(unsigned int i = 0; i < player_vec.size(); i++) {
        //check that we're still on the away team
        if((player_vec.at(i)->isHome() == true) && printed_home_header == false) {
                //if this is the first home player we've encountered, it's time to print the home header
            output << endl << "HOME" << endl;
            printed_home_header = true;
        }

        //send the player stats to the output file.
        output << player_vec.at(i)->getName() <<
         "\t" << player_vec.at(i)->getAtBats() <<
        "\t" << player_vec.at(i)->getStat(Statistic::HIT) <<
        "\t" << player_vec.at(i)->getStat(Statistic::WALK) <<
        "\t" << player_vec.at(i)->getStat(Statistic::STRIKEOUT) <<
        "\t" << player_vec.at(i)->getStat(Statistic::HIT_BY_PITCH) <<
        "\t" << player_vec.at(i)->getStat(Statistic::SACRIFICE) <<
        "\t" << player_vec.at(i)->getBattingAverage() <<
        "\t" << player_vec.at(i)->getOBPercent() << endl;
    }

}


////////////////////////////////////////
//         COMPARISON FUNCTIONS       //
//   these are passed in to std::sort //
//  to sort the vector of players with//
//     respect to different stats     //
////////////////////////////////////////


//strictly face value of the names
bool alphaComparison(Player* i, Player* j) {
//drop both to lower case and then return the comparison
    std::string this_name_lower = i->getName();
    std::string rhs_name_lower = j->getName();
    int name_iterator = 0;

    //convert this->name to lower and store in this_name_lower
    while(this_name_lower[name_iterator]) {
        this_name_lower[name_iterator] = tolower(this_name_lower[name_iterator]);
        name_iterator++;
    }
    name_iterator = 0;

    //convert the argument to lower and store in rhs_name_lower
    while(rhs_name_lower[name_iterator]) {
        rhs_name_lower[name_iterator] = tolower(rhs_name_lower[name_iterator]);
        name_iterator++;
    }

    //use string comparison operator
    return this_name_lower < rhs_name_lower;
}

//determines the order for displayStats. away team first then home team, with alpha in between
bool DisplayStatsComparison(Player* i, Player* j) {
    if(i->isHome() && !j->isHome()) {
        //the first player is home, the second is away
        //the second player should come first
        //so the first player isn't at the front
        return false;
    }
    if(!i->isHome() && j->isHome()) {
        //the first player is away and the second is home
        //the first player does come before the second player
        return true;
    }
    //otherwise, they are on the same team and we need to compare names by face value

    return alphaComparison(i, j);

}

bool BattingAverageComparison(Player* i, Player* j) {
    if(i->getBattingAverage() > j->getBattingAverage()) {
        //if the first player has a higher batting average, bring it up to the top.
        return true;
    }
    if(i->getBattingAverage() < j->getBattingAverage()) {
        //if the first player has a lower batting average, let it fall to the bottom
        return false;
    }

    //if the batting average is the same, sort alphabetically
    return alphaComparison(i, j);
}

bool OBPComparison(Player* i, Player* j) {
    if(i->getOBPercent() > j->getOBPercent()) {
        return true;
    }
    if(i->getOBPercent() < j->getOBPercent()) {
        return false;
    }

    return alphaComparison(i, j);
}

//generic-ish Don't Repeat Yourself.
bool StatComparison(Player* i, Player* j, Statistic stat) {
    if(stat == Statistic::STRIKEOUT) {
        if(i->getStat(stat) > j->getStat(stat)) {
            return false;
        }
        if(i->getStat(stat) < j->getStat(stat)) {
            return true;
        }
    } else {
        if(i->getStat(stat) > j->getStat(stat)) {
            return true;
        }
        if(i->getStat(stat) < j->getStat(stat)) {
            return false;
        }
    }

    return alphaComparison(i, j);
}

bool HitComparison(Player* i, Player* j) {
    return StatComparison(i, j, Statistic::HIT);
}

bool WalkComparison(Player* i, Player* j) {
    return StatComparison(i, j, Statistic::WALK);
}

bool StrikeoutComparison(Player* i, Player* j) {
    return StatComparison(i, j, Statistic::STRIKEOUT);
}

bool HBPComparison(Player* i, Player* j) {
    return StatComparison(i, j, Statistic::HIT_BY_PITCH);
}

//given a derived statistic, does all the logic for determining which leaders to print and in which order
void DisplayStatLeaders(std::vector<Player*> player_vec, ofstream& output, DerivedStatistic stat, string header) {

    //first sort the player vector so we have the top players at the front
    if(stat == DerivedStatistic::BAT_AVG) {
        std::sort(player_vec.begin(), player_vec.end(), BattingAverageComparison);
    } else {
        std::sort(player_vec.begin(), player_vec.end(), OBPComparison);
    }

    output << endl << header << endl;

    int players_printed = 0; //make sure we stop at 3 early if necessary
    string names_to_print = ""; //accumulates the players for that rank, then gets outputted
    std::vector<Player*> to_print; //holds all the players for that rank
    Player* next_highest = player_vec.front();
    unsigned int player_vec_iterator = 0;
    unsigned int print_vec_iterator = 0;
    double high_score = next_highest->getStat(stat);
    int max_players_to_print = 3;
    if(player_vec.size() < 3) { max_players_to_print = player_vec.size();}
    Player* name_iterator;

    while(players_printed < max_players_to_print ) {
        //flush printing vector
        to_print.clear();
        print_vec_iterator = 0;

        high_score = next_highest->getStat(stat);
        //all players in this rank have the same score.
        while(next_highest != nullptr && next_highest->getStat(stat) == high_score) {
            to_print.push_back(next_highest);

            player_vec_iterator++;
            if(player_vec_iterator == player_vec.size()) {
                break;
            }
            next_highest = player_vec.at(player_vec_iterator);
        }

        //sort by team, then alpha
        std::sort(to_print.begin(), to_print.end(), DisplayStatsComparison);

        players_printed += to_print.size();
        name_iterator = to_print.front();
        names_to_print = name_iterator->getName();

        while(name_iterator != nullptr) {
            if(to_print.at(0) != name_iterator){
                names_to_print += ", " + name_iterator->getName();
            }

            print_vec_iterator++;
            if(print_vec_iterator == to_print.size()) {
                break;
            }
            name_iterator = to_print.at(print_vec_iterator);
        }
        output << high_score << "\t" << names_to_print << endl;
    }

}

//same as above, but for statistic instead of derived statistic.
void DisplayStatLeaders(std::vector<Player*> player_vec, ofstream& output, Statistic stat, string header) {

    //sort the player vector accordingly
    if(stat == Statistic::HIT) {
        std::sort(player_vec.begin(), player_vec.end(), HitComparison);
    } else if (stat == Statistic::WALK) {
        std::sort(player_vec.begin(), player_vec.end(), WalkComparison);
    } else if (stat == Statistic::STRIKEOUT) {
        std::sort(player_vec.begin(), player_vec.end(), StrikeoutComparison);
    } else if (stat == Statistic::HIT_BY_PITCH) {
        std::sort(player_vec.begin(), player_vec.end(), HBPComparison);
    } else {
        std::cout << "can't display leaders for stat: " << stat << std::endl;
        return;
    }

    output << endl << header << endl;

    int players_printed = 0; //don't go over 3 if they aren't the same rank
    string names_to_print = "";  //holds the line of players to output
    std::vector<Player*> to_print; //holds the actual players to output for that rank
    Player* next_highest = player_vec.front(); //grabs the high score player for that rank
    unsigned int player_vec_iterator = 0;
    unsigned int print_vec_iterator = 0;
    int high_score = next_highest->getStat(stat);
    int max_players_to_print = 3;
    if(player_vec.size() < 3) { max_players_to_print = player_vec.size();}
    Player* name_iterator;

    while(players_printed < max_players_to_print ) {
        //flush printing array
        to_print.clear();
        print_vec_iterator = 0;
        high_score = next_highest->getStat(stat);
        while(next_highest != nullptr && next_highest->getStat(stat) == high_score) {
            to_print.push_back(next_highest);

            player_vec_iterator++;
            if(player_vec_iterator == player_vec.size()) {
                break;
            }
            next_highest = player_vec.at(player_vec_iterator);
        }
        //sort by team, then alpha
        std::sort(to_print.begin(), to_print.end(), DisplayStatsComparison);

        //some housekeeping
        players_printed += to_print.size();
        name_iterator = to_print.front();
        names_to_print = name_iterator->getName();

        //now that we have all the proper players to print, and they're sorted
        //we can append to the string with commas as necessary
        while(name_iterator != nullptr) {
            if(to_print.at(0) != name_iterator){
                names_to_print += ", " + name_iterator->getName();
            }

            print_vec_iterator++;
            if(print_vec_iterator == to_print.size()) {
                break;
            }
            name_iterator = to_print.at(print_vec_iterator);
        }
        output << scientific; //scientific is the opposite of fixed. no unnecessary decimal points
        output << (int)(high_score) << "\t" << names_to_print << endl;
    }
}

void DisplayLeaders(std::vector<Player*> player_vec, ofstream& output) {
    output << endl;
    output << "LEAGUE LEADERS";

    //easy easy calls to the helper functions.
    DisplayStatLeaders(player_vec, output, DerivedStatistic::BAT_AVG, "BATTING AVERAGE");
    DisplayStatLeaders(player_vec, output, DerivedStatistic::OB_PERCENT, "ON-BASE PERCENTAGE");
    output << scientific;
    DisplayStatLeaders(player_vec, output, Statistic::HIT, "HITS");
    DisplayStatLeaders(player_vec, output, Statistic::WALK, "WALKS");
    DisplayStatLeaders(player_vec, output, Statistic::STRIKEOUT, "STRIKEOUTS");
    DisplayStatLeaders(player_vec, output, Statistic::HIT_BY_PITCH, "HIT BY PITCH");
    output << endl;

}

//reads in the keyfile and returns a hashtable with keys being the play codes and values being statistics
HashTable<Statistic> HashKeyfile() {

    ifstream input("keyfile.txt");
    string line;
    HashTable<Statistic> codes(10);

    getline(input, line); //throw away first "outs" header garbage
    Statistic current_stat = Statistic::OUT;

    while(getline(input, line)) {

        if(line == "" || line.at(0) == ' ') {
            continue;
        }

        //when you get to a header, change the value of the play codes you read in.
        //don't bother parsing the header for what it should be, that's harder than it needs to be
        if(line.at(0) == '#') {
            if(current_stat == Statistic::OUT) {
                current_stat = Statistic::STRIKEOUT;
            } else if (current_stat == Statistic::STRIKEOUT) {
                current_stat = Statistic::HIT;
            } else if (current_stat == Statistic::HIT) {
                current_stat = Statistic::WALK;
            } else if (current_stat == Statistic::WALK) {
                current_stat = Statistic::SACRIFICE;
            } else if (current_stat == Statistic::SACRIFICE) {
                current_stat = Statistic::HIT_BY_PITCH;
            } else if (current_stat == Statistic::HIT_BY_PITCH) {
                current_stat = Statistic::ERROR;
            } else {
                std::cout << "keyfile broke." << std::endl;
            }
            continue;
        }

        //remove whitespace and hidden characters
        for(unsigned int i = 0; i < line.length(); i++) {
            if(line.at(i) == ' ' || line.at(i) == '\r') {
                line.erase(i, 1);
                i--;
            }
        }

        //some error handling ish. probably unnecessary
        if(line == "" || line.length() <= 0) {
            continue;
        }

        //more checks just in case. really no valid reason to do it besides redundancy ?
        if(line != "" && line != " ") {
            //actually put it in the hash table
            codes.Insert(new Statistic(current_stat),line);
        }


    }

    return codes;
}

int main()
{
    //generate the hash table to decode play codes into statistics
    HashTable<Statistic> decode = HashKeyfile();

    //read filename and create the input stream
    string filename;
    cin >> filename;
    ifstream input(filename);

    //validate that it's actually open
    if(!input.is_open()) {
        std::cout << "couldn't find " << filename << std::endl;
        return -1;
    }

    //create a hash table of players, start it at size 20
    HashTable<Player> players(20);

    //parse file will fill the players hash table
    ParseFile(input, players, decode);

    //now we can take the hash table of players (fast to create) and form a vector of players from it
    std::vector<Player*> player_vec;
    players.copyToVector(player_vec);

    //the advantage of the vector of players is that we can sort and manipulate them cleanly
    std::sort(player_vec.begin(), player_vec.end(), DisplayStatsComparison);

    //create the output file
    ofstream output("leaders.txt");

    //first start with tabulated stats
    DisplayPlayerStats(player_vec, output);

    //then output the leaders
    DisplayLeaders(player_vec, output);

    //no pointers to clean up, but there are files to close.
    input.close();
    output.close();
}
