#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "math.h";
#include <chrono>
#include <random>
#include <stdlib.h>     /* atoi */

using namespace std;

#define FILENAME "/Users/adamzuiderveld/CLionProjects/NaiveBayes/teacher.csv"
#define COLS 151 // Number of columns in data
//Users/adamzuiderveld/CLionProjects/NaiveBayes/teacher.csv
vector<vector<double> > doubleConvert(vector<vector<string>> data) {
    vector<vector<double> > data1;
    for (int i = 0; i < data.size(); ++i) {
        data1.push_back(vector<double>());
        for(int j=0;j < data[0].size(); ++j){
            string l = data[i][j];
            double r;
            r = stod(l);
            //double col = j;
            data1[i].push_back(r);
        }
    }
    return data1;
}

vector<vector<string> > vector_object(const char *file_name) {
    ifstream fileName;
    fileName.open(file_name);
    string d;
    vector <string> myVec;
    vector<vector<string> > data;
    int i = 0;
    while (!fileName.eof()) {
        fileName >> d;
        stringstream ss(d);
        vector <string> myVec;
        string token;
        while (getline(ss, token, ',')) {
            myVec.push_back(token);
        }
        data.push_back(myVec);
        i += 1;
    }
    data.erase(data.end() - 1);
    return data;
}





//find p(n)
double prob(double number, vector<vector<int>> v){
    //calc P(1);
    double probOne=0;
    double prob1;
    for(int i=0; i<v.size();i++){
        if(v[i][5] == number){
            ++probOne;
        }
    }
    prob1 = probOne / v.size();
    return prob1;
}



double stdDev(vector<vector<int>> v, double ave, int colmn)
{
    double E=0;
    double inverse = 1.0 / static_cast<double>(v.size());
    for(unsigned int i=0;i<v.size();i++)
    {
        E += pow(static_cast<double>(v[i][colmn]) - ave, 2);
    }
    return sqrt(inverse * E);
}


//row 5 must be 1,2 or 3!!!!!!!!!!
double average(vector<vector<int>> v, int col, int row5){
    double avg = 0;
    double counter=0;
    for(int i=0; i < v.size()-1; i++) {
        if (v[i][5] == row5) {
            avg += v[i][col];
            counter++;
        }
    }
    double average;
    average = avg / counter;
    return average;
}

double gaus(double x, double m, double sd){
    double d = x - m;
    return 1/sqrt(2*M_PI*sd)*exp(-1.0 *(d*d)/(2*sd));
}

int naiveBayes(vector<vector<int>> v,vector<vector<int>> v2, int row){
    double p1=log(prob(1,v));
    double p2=log(prob(2,v));
    double p3=log(prob(3,v));
    cout << "log(p1): " << p1 << endl;
    cout << "log(p2): " << p2 << endl;
    cout << "log(p3): " << p3 << endl;

    for(int j=1; j < 4 ; j++){
        for(int i = 0 ; i<5 ; i++){

            double a = average(v,i,j);
            //prob(j,vect) * gaus(2, a, stdDev(vect, a, i) );
            if(j == 1){
                cout <<"log of " <<gaus(v2[row][i], a, stdDev(v, a, i) ) << " = " <<  log( gaus(v2[row][i], a, stdDev(v, a, i) )) << " ";
                p1 += log( gaus(v2[row][i], a, stdDev(v, a, i) ));
            }
            if (j==2){
                cout << log( gaus(v2[row][i], a, stdDev(v, a, i) )) << " ";
                p2 += log( gaus(v2[row][i], a, stdDev(v, a, i) ));
            }
            if(j==3){
                cout << log( gaus(v2[row][i], a, stdDev(v, a, i) )) << " ";
                p3 +=log( gaus(v2[row][i], a, stdDev(v, a, i) ));
            }
        }
        cout << endl;
    }
    cout<< "p1: " << p1 << endl;
    cout<< "p2: " << p2 << endl;
    cout<< "p3: " << p3 << endl;
    if (p1 > p2 && p1 > p3){
        return 1;
    }
    if (p2 > p1 && p2 > p3){
        return 2;
    }
    if(p3>p1 && p3>p2){
        return 3;
    }
}


int main() {

    vector<vector<int>> vect2
            {
                    //60 rows 0 - 59
                    {2, 9,  5,  2, 24, 3},
                    {2, 18, 25, 2, 25, 3},
                    {1, 17, 17, 2, 31, 3},
                    {2, 1,  15, 2, 31, 3},
                    {2, 1,  8,  2, 18, 2},
                    {1, 11, 16, 2, 22, 2},
                    {1, 22, 13, 2, 27, 2},
                    {2, 9,  2,  2, 14, 2},
                    {2, 13, 1,  2, 20, 2},
                    {1, 6,  17, 2, 35, 2},
                    {2, 23, 3,  1, 20, 2},
                    {1, 23, 3,  1, 20, 2},
                    {2, 6,  17, 2, 37, 2},
                    {1, 22, 3,  2, 15, 2},
                    {2, 20, 2,  2, 25, 2},
                    {2, 23, 3,  2, 10, 2},
                    {2, 20, 2,  2, 14, 1},
                    {1, 23, 3,  2, 38, 1},
                    {2, 13, 1,  2, 29, 1},
                    {2, 10, 3,  2, 19, 1},
                    {2, 7,  11, 2, 30, 1},
                    {1, 14, 15, 2, 32, 1},
                    {2, 8,  3,  2, 27, 1},
                    {2, 12, 7,  2, 34, 1},
                    {2, 8,  7,  2, 23, 1},
                    {2, 15, 1,  2, 66, 1},
                    {2, 23, 3,  2, 12, 1},
                    {2, 2,  9,  2, 29, 1},
                    {2, 15, 1,  2, 19, 1},
                    {2, 20, 2,  2, 3,  1},
                    {2, 13, 14, 2, 17, 3},
                    {2, 9,  6,  2, 7,  3},
                    {1, 10, 3,  2, 21, 3},
                    {2, 14, 15, 2, 36, 3},
                    {1, 13, 1,  2, 54, 3},
                    {1, 8,  3,  2, 29, 3},
                    {2, 20, 2,  2, 45, 3},
                    {2, 22, 1,  2, 11, 2},
                    {2, 18, 12, 2, 16, 2},
                    {2, 20, 15, 2, 18, 2},
                    {1, 17, 18, 2, 44, 2},
                    {2, 14, 23, 2, 17, 2},
                    {2, 24, 26, 2, 21, 2},
                    {2, 9,  24, 2, 20, 2},
                    {2, 12, 8,  2, 24, 2},
                    {2, 9,  6,  2, 5,  2},
                    {2, 22, 1,  2, 42, 2},
                    {2, 7,  11, 2, 30, 1},
                    {2, 10, 3,  2, 19, 1},
                    {2, 23, 3,  2, 11, 1},
                    {2, 17, 18, 2, 29, 1},
                    {2, 16, 20, 2, 15, 1},
                    {2, 3,  2,  2, 37, 1},
                    {2, 19, 4,  2, 10, 1},
                    {2, 23, 3,  2, 24, 1},
                    {2, 3,  2,  2, 26, 1},
                    {2, 10, 3,  2, 12, 1},
                    {1, 18, 7,  2, 48, 1},
                    {2, 22, 1,  2, 51, 1},
                    {2, 2,  10, 2, 27, 1}
            };




    vector<vector<int>> vect
            {
        //91 rows... 0 - 90
                    {1, 23, 3,  1, 19, 3},
                    {2, 15, 3,  1, 17, 3},
                    {1, 23, 3,  2, 49, 3},
                    {1, 5,  2,  2, 33, 3},
                    {2, 7,  11, 2, 55, 3},
                    {2, 23, 3,  1, 20, 3},
                    {2, 9,  5,  2, 19, 3},
                    {2, 10, 3,  2, 27, 3},
                    {1, 22, 3,  1, 58, 3},
                    {2, 15, 3,  1, 20, 3},
                    {2, 10, 22, 2, 9,  3},
                    {2, 13, 1,  2, 30, 3},
                    {2, 18, 21, 2, 29, 3},
                    {2, 6,  17, 2, 39, 3},
                    {2, 6,  17, 2, 42, 2},
                    {2, 6,  17, 2, 43, 2},
                    {2, 7,  11, 2, 10, 2},
                    {2, 22, 3,  2, 46, 2},
                    {2, 13, 3,  1, 10, 2},
                    {2, 7,  25, 2, 42, 2},
                    {2, 25, 7,  2, 27, 2},
                    {2, 25, 7,  2, 23, 2},
                    {2, 2,  9,  2, 31, 2},
                    {2, 1,  15, 1, 22, 2},
                    {2, 15, 13, 2, 37, 2},
                    {2, 7,  11, 2, 13, 2},
                    {2, 8,  3,  2, 24, 2},
                    {2, 14, 15, 2, 38, 2},
                    {2, 21, 2,  2, 42, 1},
                    {2, 22, 3,  2, 28, 1},
                    {2, 11, 1,  2, 51, 1},
                    {2, 18, 5,  2, 19, 1},
                    {2, 13, 1,  2, 31, 1},
                    {1, 13, 3,  1, 13, 1},
                    {2, 5,  2,  2, 37, 1},
                    {2, 16, 8,  2, 36, 1},
                    {2, 4,  16, 2, 21, 1},
                    {2, 5,  2,  2, 48, 1},
                    {2, 14, 15, 2, 38, 1},
                    {1, 23, 3,  1, 19, 3},
                    {2, 15, 3,  1, 17, 3},
                    {1, 23, 3,  2, 49, 3},
                    {1, 5,  2,  2, 33, 3},
                    {2, 7,  11, 2, 55, 3},
                    {2, 23, 3,  1, 20, 3},
                    {2, 9,  5,  2, 19, 3},
                    {2, 10, 3,  2, 27, 3},
                    {1, 22, 3,  2, 58, 3},
                    {2, 15, 3,  1, 20, 3},
                    {2, 10, 22, 2, 9,  3},
                    {2, 13, 1,  2, 30, 3},
                    {2, 18, 21, 2, 29, 3},
                    {2, 6,  17, 2, 39, 3},
                    {2, 6,  17, 2, 42, 2},
                    {2, 6,  17, 2, 43, 2},
                    {2, 7,  11, 2, 10, 2},
                    {2, 22, 3,  2, 46, 2},
                    {2, 13, 3,  1, 10, 2},
                    {2, 7,  25, 2, 42, 2},
                    {2, 25, 7,  2, 27, 2},
                    {2, 25, 7,  2, 23, 2},
                    {2, 2,  9,  2, 31, 2},
                    {2, 1,  15, 1, 22, 2},
                    {2, 15, 13, 2, 37, 2},
                    {2, 7,  11, 2, 13, 2},
                    {2, 8,  3,  2, 24, 2},
                    {2, 14, 15, 2, 38, 2},
                    {2, 21, 2,  2, 42, 1},
                    {2, 22, 3,  2, 28, 1},
                    {2, 11, 1,  2, 51, 1},
                    {2, 18, 5,  2, 19, 1},
                    {2, 13, 1,  2, 31, 1},
                    {1, 13, 3,  1, 13, 1},
                    {2, 5,  2,  2, 37, 1},
                    {2, 16, 8,  2, 36, 1},
                    {2, 4,  16, 2, 21, 1},
                    {2, 5,  2,  2, 48, 1},
                    {2, 14, 15, 2, 38, 1},
                    {1, 23, 3,  1, 25, 3},
                    {1, 13, 3,  1, 17, 3},
                    {2, 16, 19, 2, 11, 3},
                    {2, 9,  2,  2, 39, 3},
                    {2, 13, 3,  1, 11, 3},
                    {2, 18, 21, 2, 19, 3},
                    {1, 22, 3,  2, 45, 3},
                    {2, 7,  11, 1, 20, 3},
                    {2, 23, 3,  1, 20, 3},
                    {1, 23, 3,  1, 20, 3},
                    {1, 23, 3,  2, 38, 3},
                    {2, 14, 22, 2, 17, 3},
                    {1, 17, 17, 2, 19, 3},

            };



       // vector<vector<double>> v1 = read_file();
        cout << endl << endl << "FILE VECTOR : " << endl;
    vector <vector <string> > data = vector_object("testing.csv");
    vector<vector<double>> data1;
    data1=doubleConvert(data);



    for (int i = 0; i < data1.size(); ++i) {
        cout << "Line " << i+1 << ": ";
        for(int j=0;j < data1[0].size(); ++j){
            cout << data1[i][j] <<" ";
        }
        cout << endl;
    }

    cout << endl << endl;
cout << "data1[0].size():" << data1[0].size() << endl;
    cout << "data1.size():" << data1.size() << endl;


    //split the double vector into a testing and a training set....60/40
    //699------420 / 279!!!
//    vector<vector<double>> training;
//    vector<vector<double>> testing;
//
//    //training...
//    for (int i = 0; i < 420; ++i) {
//        training.push_back(vector<double>());
//        for(int j=0;j < data1[0].size(); ++j){
//            double r = data1[i][j];
//            //double col = j;
//            training[i].push_back(r);
//        }
//    }
//    //testing
//    for (int i = 0; i < 279; ++i) {
//        testing.push_back(vector<double>());
//        for(int j=0;j < data1[0].size(); ++j){
//            double r = data1[i][j];
//            //double col = j;
//            testing[i].push_back(r);
//        }
//    }
//
//        cout << endl << endl << "TESTING!!!!!: ";
//        for ( vector<vector<int>>::size_type i = 0; i < testing.size(); i++ ) {
//            cout << "Row #" << i+1 << " ";
//            for (vector<int>::size_type j = 0; j < testing[i].size(); j++) {
//                cout << testing[i][j] << ' ';
//            }
//            cout << endl;
//        }
//
//
////        //cout whole vector.....
//    cout << endl << endl << "TRAINING!!!!!: ";
//
//    for ( vector<vector<int>>::size_type i = 0; i < training.size(); i++ ) {
//            cout << "Row #" << i+1 << " ";
//            for (vector<int>::size_type j = 0; j < training[i].size(); j++) {
//                cout << training[i][j] << ' ';
//            }
//            cout << endl;
//        }



        //calc P(1);
        double probOne=0;
        double prob1;
        for(int i=0; i<vect.size();i++){
            if(vect[i][5] == 1){
                ++probOne;
            }
        }
    prob1 = probOne / vect.size();

    cout << "probability of 1 or P(1): " <<  prob1 << endl;
    cout << "log of p1 : " << log(prob1) << endl;
        //calc p(2)
        double probTwo=0;
        double prob2;

    for(int i=0; i<vect.size();i++){
            if(vect[i][5] == 2){
                ++probTwo;
            }
        }
    prob2 = probTwo/vect.size();

    cout << "probability of 2 or P(2): " <<  prob2 << endl;

        //calc p(3)
        double probThree=0;
        double prob3;
        for(int i=0; i<vect.size();i++){
            if(vect[i][5] == 3){
                ++probThree;
            }
        }
    prob3 = probThree/vect.size();

    cout << "probability of 3 or P(3): " <<  prob3 << endl;
        double sum = prob1+prob2+prob3;
    cout << "SUM : " << sum<< endl;



//    double num;
//    cout << "ENTER NUMBER TO TEST PROB OF: " << endl;
//    cin >> num;
//    cout<< prob(num,vect);
//
//
//    int column;
//    cout << " Enter column to get mean and std dev of: " << endl;
//    cin >> column;
//
//    cout << "avg:  " <<average(vect, column,3) << " std dev:  " << stdDev(vect,average(vect,column,3),column) << endl;
//    cout << gaus(vect2[0][0] , average(vect,column,3),stdDev(vect,average(vect,column,3),column));

    cout << "CHECKING : " << endl << endl;
    int success = 0 ;
    for(int i = 0 ; i < vect2.size(); i++) {

        cout << naiveBayes(vect,vect2, i);
        if(naiveBayes(vect,vect2, i) == vect2[i][5]){
            cout << "Success at row " << i << endl;
            ++success;
        }
        else
            cout << "No success at row: " << i << endl;
    }
    cout << "success rate = " << success << "/60" << " = " << success/60;




//    double p1,p2,p3;
//
//    for(int j=1; j < 4 ; j++){
//        for(int i = 0 ; i<5 ; i++){
//
//            double a = average(vect,i,j);
//            //prob(j,vect) * gaus(2, a, stdDev(vect, a, i) );
//            if(j == 1){
//                p1=prob(j,vect) * gaus(2, a, stdDev(vect, a, i) );
//            }
//            else if (j==2){
//                p2=prob(j,vect) * gaus(2, a, stdDev(vect, a, i) );
//            }
//            else if(j==3){
//                p3=prob(j,vect) * gaus(2, a, stdDev(vect, a, i) );
//            }
//            i++;
//        }
//        j++;
//    }

cout << "Size of vect " << vect.size() << "     Size of vect2 : " << vect2.size();


    return 0;
}


/*
 * TODO:
 * have someone enter test case....or make test cases to study (preprogram  5 test cases)
 * liklihood formula is take test number  then subtract the mean, then divide by standard deviation..
 * make sure u are testing likelihood
 * Take the abs value of that number and ln() it!
 *
 * Next do this for all cases vect[i][6] = 1, 2,3
 *iterate through everything all clean
 * multiply all corresponding values to check for....
 * and badam you done!
 * :)
 *
 * FOCUS ON ITERATION CLEANLY AND CHECKING VALUES
 *
 *
 *
 *
 *
 *
 *
 *
 */