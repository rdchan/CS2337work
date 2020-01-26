//Rishi Chandna
//rdc180001
#include "Player.h"

#include <iostream> //easy printing of player for scalability
#include <iomanip> //setprecision and fixed for pretty printing

Player::Player()
{
    this->hits = 0;
    this->outs = 0;
    this->strikeouts = 0;
    this->walks = 0;
    this->hit_by_pitches = 0;
    this->sacrifices = 0;
}

Player::Player(std::string name) : Player(){
    this->name = name;
}

Player::Player(const Player& to_copy) {
    //could we use the assignment operator here? it would copy over all member variables.
    this->name = to_copy.name;
    this->hits = to_copy.hits;
    this->outs = to_copy.outs;
    this->strikeouts = to_copy.strikeouts;
    this->walks = to_copy.walks;
    this->hit_by_pitches = to_copy.hit_by_pitches;
    this->sacrifices = to_copy.sacrifices;

}
Player::~Player()
{
    //dtor
}

//returns the count of the category of stat passed in
int Player::getStat(Statistic stat) const {
    if(stat == Statistic::HIT) {
        return this->hits;
    } else if( stat == Statistic::OUT) {
        return this->outs;
    } else if( stat == Statistic::STRIKEOUT) {
        return this->strikeouts;
    } else if( stat == Statistic::WALK) {
        return this->walks;
    } else if( stat == Statistic::HIT_BY_PITCH) {
        return this->hit_by_pitches;
    } else if( stat == Statistic::SACRIFICE) {
        return this->sacrifices;
    } else {
        std::cout << "ERROR: Statistic enum invalid in Player::getStatByEnum(" << stat << ")" << std::endl;
        return -1;
    }
}

//overloaded version for int and double compatibility.
double Player::getStat(DerivedStatistic stat) const {
    if(stat == DerivedStatistic::BAT_AVG) {
        return getBattingAverage();
    } else if (stat == DerivedStatistic::OB_PERCENT) {
        return getOBPercent();
    } else {
        std::cout << "ERROR: Statistic enum invalid in Player::getStatByEnum(" << stat << ")" << std::endl;
        return -1;
    }
}

//increments the category of stat passed in
void Player::incStat(Statistic stat) {
    if(stat == Statistic::HIT) {
        this->hits++;
    } else if( stat == Statistic::OUT) {
        this->outs++;
    } else if( stat == Statistic::STRIKEOUT) {
        this->strikeouts++;
    } else if( stat == Statistic::WALK) {
        this->walks++;
    } else if( stat == Statistic::HIT_BY_PITCH) {
        this->hit_by_pitches++;
    } else if( stat == Statistic::SACRIFICE) {
        this->sacrifices++;
    } else {
        std::cout << "ERROR: Statistic enum invalid in Player::incStatByEnum(" << stat << ")" << std::endl;
        return;
    }
}

//counts the stats and returns at bats. at bats aren't stored
int Player::getAtBats() const {
    //at bats is hits + outs + strikeouts
    return this->hits + this->outs + this->strikeouts;
}

//counts the stats and returns plate apps. plate apps aren't stored.
int Player::getPlateAppearances() const {
    //plate appearances is sum of all stats
    return this->hits + this->outs + this->strikeouts + this->walks + this->hit_by_pitches + this->sacrifices;
}

//calculates and returns batting average. BA doesn't get stored
double Player::getBattingAverage() const {
    //batting average = hits/at-bats
    //prevent division by 0. if at-bats is 0, return 0.
    if(this->getAtBats() == 0) { return 0; }
    return ((double)this->hits/this->getAtBats());
}

//calculates and returns ob percent. OB% doesn't get stored
double Player::getOBPercent() const {
    //ob% = (hits + walks + hitbypitches)/(plate appearances)
    //prevent division by 0. if plate apps is 0, return 0.
    if(this->getPlateAppearances() == 0) { return 0; }
    return ((double)(this->hits+this->walks+this->hit_by_pitches)/(this->getPlateAppearances()));
}

std::string Player::getName() const {
    return this->name;
}

void Player::print() const {
    std::cout << std::fixed << std::setprecision(3) << this->name << "\t" << this->getAtBats() << "\t" << this->hits << "\t" << this->walks << "\t" << this->strikeouts << "\t" << this->hit_by_pitches << "\t" << this->sacrifices << "\t" << this->getBattingAverage() << "\t" << this->getOBPercent() << std::endl;
}


bool Player::operator<(const Player& rhs) {
    //face value comparison
    //take the names, convert to lowercase, and then compare

    //set up
    std::string this_name_lower = this->name;
    std::string rhs_name_lower = rhs.getName();
    int i = 0;

    //convert this->name to lower and store in this_name_lower
    while(this_name_lower[i]) {
        this_name_lower[i] = tolower(this_name_lower[i]);
        i++;
    }
    i = 0;

    //convert the argument to lower and store in rhs_name_lower
    while(rhs_name_lower[i]) {
        rhs_name_lower[i] = tolower(rhs_name_lower[i]);
        i++;
    }
    //use string comparison operator
    return this_name_lower < rhs_name_lower;
}

bool Player::operator>(const Player& rhs) {
    //face value comparison
    //take the names, convert to lowercase, and then compare

    //set up
    std::string this_name_lower = this->name;
    std::string rhs_name_lower = rhs.getName();
    int i = 0;

    //convert this->name to lower and store in this_name_lower
    while(this_name_lower[i]) {
        this_name_lower[i] = tolower(this_name_lower[i]);
        i++;
    }
    i = 0;

    //convert the argument to lower and store in rhs_name_lower
    while(rhs_name_lower[i]) {
        rhs_name_lower[i] = tolower(rhs_name_lower[i]);
        i++;
    }
    //use string comparison operator
    return this_name_lower > rhs_name_lower;
}
