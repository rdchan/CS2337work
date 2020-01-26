#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct student{
    string studentID = "";
    int num_right = 0;
    int num_wrong = 0;
    double score;
    char grade;
};

int main()
{
    cout << fixed << setprecision(2);
    string data;
    cin >> data;
    ifstream input(data);
    string answer_key;
    getline(input, answer_key);

    int num_students = 0;
    //get number of entries
    while(!input.eof()) {
        getline(input, data);
        if(data != "") {
            num_students++;
        }
    }
    input.clear();
    input.seekg (0);


    // allocate memory:
    student *students = new student[num_students];

    string current;
    string previous = "";
    getline(input, current); //ignore the answer key

    //while not eof
    while(!input.eof()) {
        //read line
        input >> current;

        //break if file got stuck at end with newline
        if(current == previous) { break; }
        //parse name
        //names[player_index] = current;
        (*students).studentID = current;
        //parse batting record
        input.ignore();
        getline(input, current);
        previous = current; //used to check for end of file at next iteration

        if(current.length() != answer_key.length()) {
            cout << "uh oh" << endl;
        }else {
        for(unsigned int i = 0; i < answer_key.length(); i++) {
            //if the answer matches
            if(current.at(i) == answer_key.at(i)) {
                (*students).num_right++;
            } else {
                //the answer doesn't match. either it's wrong, or they left it blank
                //if they answered but it doesn't match, increment wrong
                if(current.at(i) != ' ') {
                    (*students).num_wrong++;
                }
            }
        }
        }

        (*students).score = 100*(2*((*students).num_right)-((*students).num_wrong))/(40.0);
        if((*students).score >= 90) {
            (*students).grade = 'A';
        }else if((*students).score >= 80) {
            (*students).grade = 'B';
        }else if((*students).score >= 70) {
            (*students).grade = 'C';
        }else if((*students).score >= 60) {
            (*students).grade = 'D';
        }else{
            (*students).grade = 'F';
        }


        students++;
    }

    students -= num_students;

    for(int i = 0; i < num_students; i++) {
        cout << (*students).studentID << "\t" << (*students).score << "\t" << (*students).grade << endl;
        students++;
    }
    return 0;
}
