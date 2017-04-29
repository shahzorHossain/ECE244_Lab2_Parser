/* 
 * File:   main.cpp
 * Author: hossa172
 *
 * Created on September 28, 2016, 5:32 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#define MAX_NODE_NUMBER 5000
#define MIN_NODE_NUMBER 0

using namespace std;

int argumentCheck(stringstream& myStream) {

    //if the stream fails, it means error is present
    if (myStream.fail()) {

        //if the stream reaches the end, 
        // it means that there aren't few arguments 
        // as it didn't stop in between
        if (myStream.eof()) {

            return 2;

        }//if it stops in between, 
            //then it means there is a type mismatch 
            // and invalid argument
        else {

            return 1;

        }
    }
    return 0;

}

void insertR(stringstream& lineStream,stringstream& lineStream2,
        string resistorID,string temp,
        double resistorVal,int nodeid1,int nodeid2){
    
    //parse an insertR command
    
     lineStream >> resistorID;

            lineStream >> resistorVal;

            lineStream >> nodeid1;

            lineStream >> nodeid2;
           
            if (resistorVal < 0) { //if resistance is negative,
                                        //print error
                cout << "Error: negative resistance" << endl;
            }//if any of the nodes are out of bounds, print error
            else if ((nodeid1 > MAX_NODE_NUMBER) ||
                    (nodeid1 < MIN_NODE_NUMBER)) {
                cout << "Error: node " << nodeid1 <<
                        " is out of permitted range "
                        << MIN_NODE_NUMBER << "-" <<
                        MAX_NODE_NUMBER << endl;
            } else if ((nodeid2 > MAX_NODE_NUMBER) ||
                    (nodeid2 < MIN_NODE_NUMBER)) {
                cout << "Error: node " << nodeid2 <<
                        " is out of permitted range "
                        << MIN_NODE_NUMBER << "-" <<
                        MAX_NODE_NUMBER << endl;
            }//if nodes are equal, print error
            else if (nodeid1 == nodeid2) {

                cout << "Error: both terminals of resistors connect to node "
                        << nodeid1 << endl;
            }                //checks for too few arguments
            else if (argumentCheck(lineStream) == 2) {

                cout << "Error: too few arguments" << endl;
            }
            //checks for too many with peek() and seeing if
                //any string is read after any space or tab
            else if (lineStream.peek() <= ' ' && lineStream >> temp) {
                cout << "Error: too many arguments" << endl;
            }
            //checks to see if there is a type mismatch at the end
            // or in the middle of the string
            else if (lineStream.peek() > ' ' ||
                    argumentCheck(lineStream) == 1) {

                cout << "Error: invalid argument" << endl;
            }

            else {// if all errors are checked print it out


                cout << "Inserted: resistor " << resistorID << " " <<
                        setprecision(2) << fixed << resistorVal <<
                        " " << "Ohms " << nodeid1 << " -> " << nodeid2 << endl;
            }
    
}

void modifyR(stringstream& lineStream, stringstream& lineStream2,
        string resistorID,double resistorVal,string temp){
    
    
            lineStream >> resistorID;

            lineStream >> resistorVal;


            //checks for negative resistor value
            if (resistorVal < 0) {
                cout << "Error: negative resistance" << endl;
            }//checks for few arguments
            else if (argumentCheck(lineStream) == 2) {

                cout << "Error: too few arguments" << endl;
            }//checks for too many arguments after space or tab
            else if (lineStream.peek() <= ' ' && lineStream >> temp) {
                cout << "Error: too many arguments" << endl;
            }                //checks for type mismatch at end or in the middle
            else if (lineStream.peek() > ' ' || 
                    argumentCheck(lineStream) == 1) {

                cout << "Error: invalid argument" << endl;
            } else {

                cout << "Modified: resistor " << resistorID <<
                        " to " << setprecision(2) << fixed <<
                        resistorVal << " Ohms" << endl;
            }
    
}

void printR(stringstream& lineStream, string resistorID, string temp){
    
    
            lineStream >> resistorID;
            //checks to see too few
            if (argumentCheck(lineStream) == 2) {

                cout << "Error: too few arguments" << endl;
            }//checks to see if id matches "all" and is the last string
            else if (resistorID == "all" && lineStream.eof()) {
                cout << "Print: all resistors" << endl;
            } 
            else if (lineStream.peek() <= ' ' && lineStream >> temp) {
                cout << "Error: too many arguments" << endl;
            }
                //no peek is needed since it's a string
            else if (argumentCheck(lineStream) == 1) {

                cout << "Error: invalid argument" << endl;
            }
            else {
                cout << "Print: resistor " << resistorID << endl;
            }
    
}

void printNode(stringstream& lineStream, stringstream& lineStream2,
        int nodeid1,int nodeid2, string temp, char c){
    
    lineStream >> temp; //this is for reading the string "all"
            lineStream2 >> nodeid1; //this is for reading integers

            //checks to see if the node is within bounds
            if ((nodeid1 > MAX_NODE_NUMBER) ||
                    (nodeid1 < MIN_NODE_NUMBER)) {
                cout << "Error: node " << nodeid1 <<
                        " is out of permitted range "
                        << MIN_NODE_NUMBER << "-" << MAX_NODE_NUMBER << endl;
            }                //checks to see if argument is inputted
            else if (argumentCheck(lineStream) == 2) {

                cout << "Error: too few arguments" << endl;
            } else if (!lineStream2.fail()) { //if integer value is inputted
                // eg: 234 or 253rxn

                c = lineStream2.peek(); // puts peek into a char type
                //and uses it to see if
                //there is anything after int is read
                //if there is, it is an error
                if (c > ' ') {

                    cout << "Error: invalid argument" << endl;

                }//checks to see if there is a space and string afterwards
                else if (c == ' ' && lineStream >> temp) {
                    cout << "Error: too many arguments" << endl;
                } else {
                    cout << "Print: node " << nodeid1 << endl;
                }

            } else if (!lineStream.fail()) { //if any string is inputted



                if (temp == "all" && lineStream.eof()) { //if its "all" and
                    //end of file
                    cout << "Print: all nodes" << endl;
                } else if (temp != "all") {

                    cout << "Error: invalid argument" << endl;
                } else {
                    cout << "Error: too many arguments" << endl;
                }
            }
            
}

void deleteR(stringstream& lineStream, string resistorID, string temp){
    
            lineStream >> resistorID;


            //same code from printR
            if (argumentCheck(lineStream) == 2) {

                cout << "Error: too few arguments" << endl;
            } else if (resistorID == "all" && lineStream.eof()) {
                cout << "Deleted: all resistors" << endl;
            } else if (lineStream.peek() <= ' ' && lineStream >> temp) {
                cout << "Error: too many arguments" << endl;
            } else if (argumentCheck(lineStream) == 1) {

                cout << "Error: invalid argument" << endl;
            } else {
                cout << "Deleted: resistor " << resistorID << endl;

            }
}

void parser(){
    
    string line;
    string resistorID;
    double resistorVal;
    int nodeid1 = 1;
    int nodeid2 = 0;
    char c; //declaration for the peek() function



    cout << "> ";

    getline(cin, line); //Get a line from standard input

    while (!cin.eof()) {
        //Put the line in a stringstream for parsing
        //Making a new stringstream for each line so flags 
        //etc etc are in a known state

        string command;
        string temp;
        stringstream lineStream(line);
        stringstream lineStream2(line); //I created another stream for
        // reading int in printNode


        lineStream >> command;
        lineStream2 >> command;


        if (command == "insertR") {
            
            insertR(lineStream,lineStream2,resistorID,temp,resistorVal,
                    nodeid1,nodeid2);

        } else if (command == "modifyR") {

            modifyR(lineStream, lineStream2, resistorID, resistorVal,temp);

        } else if (command == "printR") {

            printR(lineStream,resistorID,temp);

           

        } else if (command == "printNode") {

            printNode(lineStream, lineStream2, nodeid1, nodeid2, temp, c);
            
        } else if (command == "deleteR") {

            deleteR(lineStream,resistorID,temp);

        } else {

            cout << "Error: invalid command" << endl;
        }

        cout << "> ";

        getline(cin, line); //gets the next line and loops it
        // puts that line into lineStream in the loop

    }


    
    
}

int main() {

    parser();

    return 0;
}