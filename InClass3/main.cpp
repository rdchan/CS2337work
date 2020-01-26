//Rishi Chandna
//rdc180001

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    cout << fixed << setprecision(2);
    string filename;
    cin >> filename;
    ifstream input(filename);


    int data;
    int num_entries = 0;

    //get number of entries
    while(input>>data) {
        num_entries++;
    }

    //flush any flags and set input position back to beginning
    input.clear();
    input.seekg (0);


    // allocate memory:
    int *entries = new int[num_entries];

    //use first value to initialize stats. could use integer minimum and maximum, doesn't really matter
    input >> data;
    int lowest = data;
    int highest = data;
    int sum = 0; //isn't calculated until later.
    (*entries) = data; //make sure first value goes into the array also
    entries++;

    //fill out the array now that we know the size
    while(input >> data) {
        (*entries) = data;
        entries++;
    }

    //go back to beginning
    entries -= num_entries;

    //do the math/stats (could've done it while reading in, but is more interesting pointer arithmetic after)
    for(int i = 0; i < num_entries; i++) {

        //check if it's the lowest
        if((*entries) < lowest) {
            lowest = (*entries);
        }

        //check if it's the highest
        if((*entries) > highest) {
            highest = (*entries);
        }

        //keep running total of the sum
        sum += (*entries);
        //shift to the next element afterwards
        entries++;
    }

    //reset incase we want to add to the code. would be ugly bug to try to find.
    entries -= num_entries;

    //print out summary statistics
    cout << "Highest: " << highest << endl;
    cout << "Lowest: " << lowest << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << (double)sum / num_entries;
    return 0;
}
