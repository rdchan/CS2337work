//Rishi Chandna
//rdc180001
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

enum Statistic{HIT, OUT, STRIKEOUT, WALK, HIT_BY_PITCH, SACRIFICE, ERROR};
enum DerivedStatistic{BAT_AVG, OB_PERCENT};

class Player
{
    public:
        Player();
        Player(std::string name);
        Player(std::string name, bool homeTeam);
        Player(const Player& to_copy);
        virtual ~Player();
        int getStat(Statistic stat) const; //returns the count of the category of stat passed in
        double getStat(DerivedStatistic stat) const; //returns the unrounded calculation of a derived stat
        void incStat(Statistic stat); //increments the category of stat passed in
        double getBattingAverage() const;  //calculates and returns batting average. BA doesn't get stored
        double getOBPercent() const;      //calculates and returns ob percent. OB% doesn't get stored
        int getAtBats() const;             //counts the stats and returns at bats. at bats aren't stored
        int getPlateAppearances() const;   //counts the stats and returns plate apps. plate apps aren't stored.
        std::string getName() const;
        void print() const;             //nice for debugging, could be used for displaying player results, but would require to much stream garbage
        void setTeam(bool isHome) { this->isHomeTeam = isHome;}
        bool isHome() { return isHomeTeam;}
        bool operator<(const Player&); //used for sorting
        bool operator>(const Player&); //included for if a reverse sort might be helpful later on
    protected:

    private:
        std::string name;
        int hits;
        int outs;
        int strikeouts;
        int walks;
        int hit_by_pitches;
        int sacrifices;
        int errors;
        bool isHomeTeam;

};

#endif // PLAYER_H
