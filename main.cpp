// Author: Jacob Christiansen
// Recitation: 104 – Vipra Gupta
//
// Assignment 6
//MAIN function

#include <iostream>
#include <fstream>
#include <string>
#include "Assignment6.cpp"
using namespace std;



//used for running and testing all the other functions!
int main(){

    cout << avgCharsPerLine("part1.txt") << endl;

    float test[4][5];

    fillArray("part2.txt", test);

    /*(int i=0; i<3; i++){
        for(int j=0; j<5; j++){
            cout << test[i][j] << " ";
        }
        cout << endl;
    }*/ //print array

    float test2[6][5];
    cout << arrayStats("part3.txt", test2) << endl;

    /*for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cout << test2[i][j] << " ";
        }
        cout << endl;
    }*/ //print array


    string users[100];
    int ratings[100][50];
    addBookRatings("part4.txt",users,ratings);

    for(int i=0; i<6; i++){
        for(int j=0; j<5; j++){
            cout<<"Person "<<i<<" ("+users[i]+") gives book "<<j<<" a rating of "<<ratings[i][j]<<endl;
        } //print ratings in readable format, lines 0-4, all USERS
    }

    return 0;
}
