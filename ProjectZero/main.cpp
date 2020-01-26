/*  Project Zero
    Rishi Chandna
    rdc180001
    Due 4 September 2019
*/
#include <iostream> //cout, fixed
#include <fstream>  //ifsream, ostream
#include <string>   //strings for names and parsing ifstream
#include <map>      //maps for label based lookup
#include <iomanip> //setprecision

#define HIT 0
#define STRIKEOUT 1
#define WALK 2
#define HIT_BY_PITCH 3
#define BA 0
#define OB_PERCENT 1
#define NUM_STATS 4 //number of raw recorded stats + at bats + plate appearances
#define NUM_CALS 2 //number of calculated stats (BA and OB%)
#define K_VERY_SMALL 1E-9 //used to overcome bankers rounding of decimals, where equidistant decisions like 0.5265 or .5275 are rounded to the even side (.526 and .528)
#define MAX_PLAYERS 30 //defined in project description

using namespace std;

const string OUTPUT_NAME = "leaders.txt";

//Prototypes
void ParseBattingRecord(string, int[][MAX_PLAYERS], double[][MAX_PLAYERS], int);
void DisplayPlayerData(ofstream&, string[MAX_PLAYERS], int[][MAX_PLAYERS], double[][MAX_PLAYERS]);
int FindLeaderValue(int[], string[], bool);
double FindLeaderValue(double[], string[]);
string LeaderNames(int[], string[], int);
string LeaderNames(double[], string[], double);
void DisplayLeaders(ofstream&, string[], int[][MAX_PLAYERS], double[][MAX_PLAYERS]);

int main()
{
    //stores the names of the players, with indices that line up with stat arrays
    string names[MAX_PLAYERS];

    //flush names so that we can check validity later
    for(int i = 0; i < MAX_PLAYERS; i++) {
        names[i] = "";
    }

    int statistics[NUM_STATS][MAX_PLAYERS];
    double secondary_statistics[NUM_CALS][MAX_PLAYERS];

    /*STATISTICS ARRAY
                       player0     player1     ...     player30
            HIT   (H)
      STRIKEOUT   (K)
           WALK   (W)
   HIT_BY_PITCH   (P)
    */

    /*SECONDARY STATISTICS ARRAY
                                player0     player 1    ...     player30
        Batting Average (BA)
On-Base Percent (OB_PERCENT)
    */

    //zero out statistics arrays since we will be incrementing instead of assigning
    for(int i = 0; i < NUM_STATS; i++) {
        for(int j = 0; j < MAX_PLAYERS; j++) {
            statistics[i][j] = 0;
        }
    }

    //open input file
    string current;
    string previous = ""; //used to exit when file contains newlines

    int player_index = 0;
    cin >> current;
    ifstream input(current);


    //input file must be open before proceeding. otherwise, continue to prompt user
    while(!input.is_open()) {
        cout << "Error opening file " << current << endl;
        cout << "Enter input filename: ";
        cin >> current;
        input.open(current);
    }

    //if(!input.is_open()) { cout << "Error opening file " << current << endl; return 1; }


    //while not eof
    while(!input.eof()) {
        //read line
        input >> current;

        //break if file got stuck at end with newline
        if(current == previous) { break; }
        //parse name
        names[player_index] = current;

        //parse batting record
        input.ignore();
        getline(input, current);
        previous = current; //used to check for end of file at next iteration

        ParseBattingRecord(current, statistics, secondary_statistics, player_index);

        player_index++;
    }

    //close input file
    input.close();

    //open output file
    ofstream output;
    output.open(OUTPUT_NAME);
    if(!output.is_open()) { cout << "Error writing to file " << OUTPUT_NAME << endl; return 2;}

    //display individual player data
    DisplayPlayerData(output, names, statistics, secondary_statistics);

    //display leaders
    DisplayLeaders(output, names, statistics, secondary_statistics);

    //close output file
    output.close();

    return 0;
}

void ParseBattingRecord(string batting_record, int stats[][MAX_PLAYERS], double secondary_stats[][MAX_PLAYERS], int player_index) {

    //first validate at-bat and plate-appearance variables
    int plate_appearances = 0;
    int at_bats = 0;

    //for 0 : string length
    for(unsigned int i = 0; i < batting_record.length(); i++) {
        //checks letter through the results map
        //updates proper array indexed by results map row and player index col
        char current_letter = batting_record.at(i);

        //check validity of character against possible characters
        if(current_letter == 'H') {
            //Hits are stored, are at bat, are plate appearance
            stats[HIT][player_index]++;
            at_bats++;
            plate_appearances++;
        } else if(current_letter == 'O') {
            //outs aren't stored, are at bat, are plate appearance
            at_bats++;
            plate_appearances++;
        } else if(current_letter == 'K') {
            //strikeouts are stored, are at bat, are plate appearance
            stats[STRIKEOUT][player_index]++;
            at_bats++;
            plate_appearances++;
        } else if(current_letter == 'W') {
            //walks are stored, aren't at bat, are plate appearance
            stats[WALK][player_index]++;
            plate_appearances++;
        } else if(current_letter == 'P') {
            //hbp are stored, aren't at bat, are plate appearance
            stats[HIT_BY_PITCH][player_index]++;
            plate_appearances++;
        } else if(current_letter == 'S') {
            //sacrifice aren't stored, aren't at bat, are plate appearance
            plate_appearances++;
        } //if anything else, not valid character, do nothing.

    }

    //at this point, we have all the information to calculate BA and OB%
    //batting average = hits/at bats !!Caution, don't divide by 0!!
    if(at_bats == 0) {
        secondary_stats[BA][player_index] = 0;
    } else {
        secondary_stats[BA][player_index] = K_VERY_SMALL + (double)stats[HIT][player_index] / at_bats;
    }

    // OB% = (hits + walks + hit by pitch) / plate appearances
    secondary_stats[OB_PERCENT][player_index] =  K_VERY_SMALL + //k_very_small is used to circumvent bakers rounding issues
    (double)( (stats[HIT][player_index] + stats[WALK][player_index] + stats[HIT_BY_PITCH][player_index]) ) / (plate_appearances);
}

void DisplayPlayerData(ofstream &output, string names[MAX_PLAYERS], int stats[][MAX_PLAYERS], double secondary_stats[][MAX_PLAYERS]) {
    //for 0 : number of batters. could keep track of number of batters while reading in file.
    output << fixed << setprecision(3);
    for(int player_index = 0; player_index < MAX_PLAYERS; player_index++) {
        if(names[player_index] == "") { break; }
        output << names[player_index] << endl; //display name
        output << "BA: " << secondary_stats[BA][player_index] << endl;//batting average
        output << "OB%: " << secondary_stats[OB_PERCENT][player_index] << endl; //on base percentage
        output << "H: " << stats[HIT][player_index] << endl; //hits
        output << "BB: " << stats[WALK][player_index] << endl; //walks
        output << "K: " << stats[STRIKEOUT][player_index] << endl;//strikeouts
        output << "HBP: " << stats[HIT_BY_PITCH][player_index] << endl; //hit by pitch
        output << endl;//newline
    }
}

int FindLeaderValue(int stat[MAX_PLAYERS], string names[MAX_PLAYERS], bool strikeout_reverse) {

    //set first batter's value as highest/leading (strikeout leading is lowest)
    int leading_stat = stat[0];

    //for 1 : number of batters
    for(int i = 1; i < MAX_PLAYERS; i++) {
        if(names[i] == "") { break; }
        //if we're looking for strikeout leader, we want the lowest!
        if(strikeout_reverse) {
            //if value more leading, store it
            if(stat[i] < leading_stat) {
                leading_stat = stat[i];
            }
        } else {
            //if value more leading, store it
            if(stat[i] > leading_stat) {
                leading_stat = stat[i];
            }
        }
    }

    //return leading value
    return leading_stat;
}

//the double version doesn't need to have a strikeout_reverse flag, since strikeout is an int
double FindLeaderValue(double stat[MAX_PLAYERS], string names[MAX_PLAYERS]) {
    //set first value as highest
    double highest_stat = stat[0];

    //for 1 : number of batters
    for(int i = 1; i < MAX_PLAYERS; i++) {
        if(names[i] == "") { break; }
        //if value higher, store it
        if(stat[i] > highest_stat) {
            highest_stat = stat[i];
        }
    }
    //return highest value
    return highest_stat;
}

string LeaderNames(int stat[MAX_PLAYERS], string names[MAX_PLAYERS], int leading_stat) {

    //start with empty string to concatenate to
    string leader_names = "";

    bool first_player_found = false; //flag for knowing whether to use a ", "

    //for 0 : number of batters
    for(int i = 0; i < MAX_PLAYERS; i++) {

        //if the current player's index holds the high score, print either <name> or ", "<name>
        if((stat[i] == leading_stat) && (names[i] != "")) {
            if(!first_player_found) {
                first_player_found = true;
                leader_names += names[i];
            } else {
                leader_names += ", ";
                leader_names += names[i];
            }
        }
    }

    //return leader names
    return leader_names;
}

string LeaderNames(double stat[MAX_PLAYERS], string names[MAX_PLAYERS], double leading_stat) {

    //start with empty string to concatenate names to
    string leader_names = "";

    //find the leading value to look for

    bool first_player_found = false; //flag for knowing whether to use a ", "

    //for 0 : number of batters
    for(int i = 0; i < MAX_PLAYERS; i++) {

        //if the current player's index holds the high score, print either <name> or ", "<name>
        if((stat[i] == leading_stat) && (names[i] != "")) {
            if(!first_player_found) {
                first_player_found = true;
                leader_names += names[i];
            } else {
                leader_names += ", ";
                leader_names += names[i];
            }
        }
    }

    //return leader names
    return leader_names;
}

void DisplayLeaders(ofstream &output, string names[MAX_PLAYERS], int stats[][MAX_PLAYERS], double secondary_stats[][MAX_PLAYERS]) {
    //display league leaders headers
    output << "LEAGUE LEADERS" << endl;
    //for each category
        //find leader -- pass in corresponding stat array
        //search stat array for value
            //if match, display name from name array with same index
        //display value with 3 digit rounding
        output << fixed << setprecision(3);
    //BA:
        double leading_secondary_stat = FindLeaderValue(secondary_stats[BA], names);
        output << "BA: " << LeaderNames(secondary_stats[BA], names, leading_secondary_stat) << " " << leading_secondary_stat << endl;
    //OB%:
        leading_secondary_stat = FindLeaderValue(secondary_stats[OB_PERCENT], names);
        output << "OB%: " << LeaderNames(secondary_stats[OB_PERCENT], names, leading_secondary_stat) << " " << leading_secondary_stat << endl;
    //H:
        int leading_stat = FindLeaderValue(stats[HIT], names, false);
        output << "H: " << LeaderNames(stats[HIT], names, leading_stat) << " " << leading_stat << endl;
    //BB:
        leading_stat = FindLeaderValue(stats[WALK], names, false);
        output << "BB: " << LeaderNames(stats[WALK], names, leading_stat) << " " << leading_stat << endl;
    //K:
        leading_stat = FindLeaderValue(stats[STRIKEOUT], names, true);
        output << "K: " << LeaderNames(stats[STRIKEOUT], names, leading_stat) << " " << leading_stat << endl;
    //HBP:
        leading_stat = FindLeaderValue(stats[HIT_BY_PITCH], names, false);
        output << "HBP: " << LeaderNames(stats[HIT_BY_PITCH], names, leading_stat) << " " << leading_stat << endl;
}
