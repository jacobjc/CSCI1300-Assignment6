// Author: Jacob Christiansen
// Recitation: 104 – Vipra Gupta
//
// Assignment 6

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//This function will separate each substring of the given string between separator
//characters and place it into an array. The function then returns the number of
//substrings extracted.
int Split(string str, char s, string words[], int arrSize){
    arrSize = 0;
    string temp = "";
    int c=0;

         if(str.length() == 0){
        return 0;
    }

    for(int i=0; i<str.length(); i++){

        if(str[i]==s){
            words[c] = temp;
            arrSize++;
            temp = "";
            c++;
        }
        else{
            temp += str[i];
        }

    }
    words[c] = temp;
    arrSize++;
    return arrSize;
}


//This function takes in a string for the name of a file, reads the file
//line by line, and then takes the length of each line and sums them up.
//Then it divides the sum by the number of lines to find and return the
//average.
float avgCharsPerLine(string filename){
    ifstream fr;
    fr.open(filename.c_str());
    string line;
    float countln=0.0;
    float countch=0.0;


        if(fr.is_open()){

            while(!fr.eof()){
                getline(fr, line, '\n');
                countch+=(line.length());
                countln++;
            }

            fr.close();
            //cout << (countch/countln) << endl;
            return (countch/countln);
        }
    cout<<"ERROR: Unable to open file!"<<endl;
}


//Using the split function, fillArray once again reads in each line of the file,
//with the exception of the first, and takes each piece of the string separated
//by a comma and space and splits them into an array of strings. Then it moves the
//strings from the array(1D) to another array(2D), but of floats. Using stof, it converts
//the strings to floats. Then it repeat for each line, and returns the # of lines.
int fillArray(string filename, float array[][5]){
    ifstream fr;
    fr.open(filename);
    string line;
    int countln=0;
    getline(fr,line,'\n');

    if(fr.is_open()){
        while(getline(fr, line, '\n')){
            string arrStr[5];
            int j = Split(line, ',', arrStr, 5);
            for(int i=0; i<5; i++){
                string strTemp = arrStr[i];

                if(i>0 && strTemp[0] == ' '){

                    strTemp.erase(strTemp.begin());
                }
                array[countln][i] = stof(strTemp);
            }
            countln++;
        }
        fr.close();
        return (countln);
    }
    cout<<"ERROR: Unable to open file!"<<endl;
}


//arrayStats uses fillArray to read a file, and split all the necessary data into a float
//array. Using 2 double sets of for loops, it checks the float values of ODD ROWS and ODD
//COLUMNS. For each odd row, it adds all the values in it and finds the average, then sums
//the row averages. For each odd column, it adds all the values in it and finds the average,
//then sums the column averages. Then it sums all the averages and returns that number.
float arrayStats(string filename, float numbers[][5]){
    float lnum = (fillArray(filename, numbers));
    float meanSum=0.0;

    for(int i=0; i<lnum; i++){ //checking odd ROWS
        if(i%2 != 0){
            float tempMean=0.0;
            for(int j=0; j<5; j++){
                tempMean += numbers[i][j];
            }
            meanSum+=(tempMean/5);
        }
    }

    for(int j=0; j<5; j++){ //checking odd COLUMNS
        if(j%2 != 0){
            float tempMean=0.0;
            for(int i=0; i<lnum; i++){
                tempMean += numbers[i][j];
            }
            meanSum+=(tempMean/lnum);
        }
    }
    //cout <<endl;
    //cout << meanSum <<endl; //print check
    return meanSum;
}

//addBookRatings creates three arrays. 1D arr from Split (for each file line), 1D string arr for
//the 0th spot in the splitarr (user's name), and a 2D arr that's y values = the value that user
//has in the string arr (userID#), who's x values= the 1st spot in the splitarr (bookID#). The
//value at that xy position is the 2nd spot in the splitarr (user's book rating). This function
//will always be checking if the USER'S NAME already exists to spot in the 1D string array. If it
//does, it will keep assigning values in that USERID# row on the 2D arr, if they don't, the next
//avalible ID# will be assigned to them and used in the 2D arr. Also, before any values in the 2D
//array are assigned, a for loop sets all the values equal to 0, so we can tell when a book has
//not been rated.
void addBookRatings(string filename, string users[], int ratings[][50]){
    ifstream fr;
    fr.open(filename.c_str());
    string line;
    getline(fr,line,'\n'); //removes first line of read file

    if(fr.is_open()){

    for(int i=0; i<50; i++){
        for(int j=0; j<100; j++){
            ratings[j][i]=0;
        }
    }
        int nextUserID=0;

        while(getline(fr, line, '\n')){

            bool userExists = false;
            int atLocation;
            string tempArr[3];
            int temp = Split(line,',',tempArr, 3);

            for(int i=0; i<100; i++){
                if(tempArr[0]==users[i]){
                    userExists = true;
                    atLocation = i;
                }
            }
            if(userExists==true){
                ratings[atLocation][stoi(tempArr[1])] = stoi(tempArr[2]);
            }
            else{
                users[nextUserID] = tempArr[0];
                ratings[nextUserID][stoi(tempArr[1])] = stoi(tempArr[2]);
                nextUserID++;
            }
        }
        fr.close();
    }
    else{
    cout<<"ERROR: Unable to open file!"<<endl;
    }
}
