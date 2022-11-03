#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <tuple>

using namespace std;

class SeatAssignment{
private:
    string csvFile;
    string studentFile;
    vector<tuple<int, int>> coordinates;
    vector<vector<string>> Students;
    vector<vector<string>> layout; // here we sae content as well as num rows and num cols
    int rows{};
    int columns{};


public:
    void setFiles(string filename1, string filename2){
        this->csvFile = std::move(filename1);
        this->studentFile = std::move(filename2);
    }

    void getLayout(){
        // let's read the csv file to see what kind of layout we are given
        vector<string> row;
        string line, word;

        fstream file (this->csvFile, ios::in);
        if(file.is_open())
        {
            while(getline(file, line))
            {
                row.clear();

                stringstream str(line);

                while(getline(str, word, ','))
                    row.push_back(word);
                this->layout.push_back(row);
            }
            this->columns = this->layout[0].size();
            this->rows = this->layout.size();
        }
        else
            cout<<"Could not open the file\n";
    }

    void setStudents(){
        vector<string> row;
        string line, word;

        fstream file (this->studentFile, ios::in);
        if(file.is_open())
        {
            while(getline(file, line))
            {
                row.clear();

                stringstream str(line);

                while(getline(str, word, ','))
                    row.push_back(word);
                this->Students.push_back(row);
            }
        }
        else
            cout<<"Could not open the file\n";

    }

    bool checkSize(){
        this->setStudents();
        // get number of students and see if they fit in room
        int studentNumber = this->Students.size()-1;
        // count number of X and 0 to see how many are allowed
        int allowed{};

        for(auto & i : this->layout)
        {
            for(auto & j : i)
            {
                if(j == "X"){
                    allowed++;
                }
            }
        }

        if(studentNumber > allowed || studentNumber == 0){
            cout << "Students do not fit in Class" << endl;
            return false;
        }
        cout << "Max number of students fitting: " << allowed << endl;
        return true;
    }

    // Function which calculates possible seating positions for x number of students
    void calculatePossiblePositions(){
        if(this->checkSize()){
            int studentNumber = this->Students.size()-1;

            cout << "Number of students: " << studentNumber << endl;
            cout << "Number of Rows: " << this->rows << endl;
            cout << "Number of Columns: " << this->columns << endl;

            if(this->layout[0][2] == "X") {
            }

            //change the layout for each student until  every student is seated
            for(auto & i : this->layout)
            {
                for(auto & j : i)
                {
                    if(j == "X"){
                        // place student on X , O is staying empty
                        j = "S";
                        studentNumber--;
                    }
                    if(studentNumber == 0) break;
                }
                if(studentNumber == 0) break;
            }

            for(auto & i : this->layout)
            {
                for(auto & j : i)
                {
                    cout<<j<<" ";
                }
                cout<<"\n";
            }

        }
    }

    void setCoordinates(){
        // look for the s
        // check which placement it has and save the coordinates
        for(auto & i : this->layout)
        {
            for(auto & j : i)
            {
                if(j == "S"){
                    tuple<int, int> cur_coordinate = reinterpret_cast<const tuple<int, int> &>(i, j);
                    this->coordinates.push_back(cur_coordinate);
                }
            }
        }
    }

    // Function to seat the students
    void seatStudents(){

    }

};

int main(int argc, char **argv) {
    SeatAssignment seatAssignment;
    string filename;

    // fetch argument from program arguments
    if(argc == 1) {
        cout << "Please input .csv file" << endl;
        return 0;
    } else {
        // arg[0] => program name
        seatAssignment.setFiles(argv[1], argv[2]);
    }

    // step 1: get the layout of room
    seatAssignment.getLayout();
    // step 2: possible positions
    seatAssignment.calculatePossiblePositions();
    // step 3: assign students to seat and write to a csv file
    seatAssignment.seatStudents();

    return 0;
}
