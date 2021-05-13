#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
//#include "math.h";
#include <cmath>
using namespace std;

//#define FILENAME "/Users/adamzuiderveld/CLionProjects/NaiveBayes/teacher.csv"
//#define COLS 151 // Number of columns in data
//Users/adamzuiderveld/CLionProjects/NaiveBayes/teacher.csv
vector<vector<double> > doubleConvert(vector<vector<string>> data) {
    vector<vector<double> > data1;
    double r;

    for (int i = 0; i < data.size(); ++i) {
        data1.push_back(vector<double>());
        for(int j=0;j < data[0].size(); ++j){
            string l = data[i][j];
            r = stod(l);
            data1[i].push_back(r);
        }
    }
    return data1;
}

vector<vector<string> > vector_file(const char *file) {
    ifstream fileName;
    fileName.open(file);
    string d;
    vector <string> data1;
    vector<vector<string> > data;
    while (!fileName.eof()) {
        fileName >> d;
        stringstream ss(d);
        vector <string> data1;
        string token;
        while (getline(ss, token, ',')) {
            //stod(token);
            data1.push_back(token);
        }
        data.push_back(data1);
    }
    data.erase(data.end() - 1);
    return data;
}





//find p(n)
double prob(double number, vector<vector<double>> v){
    //calc P(1);
    double probOne=0;
    double prob1;
    for(int i=0; i<v.size();i++){
        if(v[i][9] == number){
            ++probOne;
        }
    }
    prob1 = probOne / v.size();
    return prob1;
}



double stdDev(vector<vector<double>> v, double ave, int colmn)
{
    double E=0;
    double inverse = 1.0 / static_cast<double>(v.size());
    for(unsigned int i=0;i<v.size();i++)
    {
        E += pow(static_cast<double>(v[i][colmn]) - ave, 2);
    }
    return sqrt(inverse * E);
}


//row 9 must be 2 or 4!!!!!!!!!!
double average(vector<vector<double>> v, int col, int row9){
    double avg = 0;
    double counter=0;
    for(int i=0; i < v.size()-1; i++) {
        if (v[i][9] == row9) {
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

int naiveBayes(vector<vector<double>> v,vector<vector<double>> v2, int row){
    double p2=log(prob(2,v));
    double p4=log(prob(4,v));
    //double p3=log(prob(3,v));
    cout << "log(p2): " << p2 << endl;
    cout << "log(p4): " << p4 << endl;
    //cout << "log(p3): " << p3 << endl;
    //check j==2 && j==4, get naive bayes of both at once, compare which is larger and output 2 or 4 depending on result
    for(int j=2; j < 5 ; j+=2){
        for(int i = 0 ; i<9 ; i++){

            double a = average(v,i,j);
            //prob(j,vect) * gaus(2, a, stdDev(vect, a, i) );
            if(j == 2){
                cout <<"log of " <<gaus(v2[row][i], a, stdDev(v, a, i) ) << " = " <<  log( gaus(v2[row][i], a, stdDev(v, a, i) )) << " ";
                p2 += log( gaus(v2[row][i], a, stdDev(v, a, i) ));
            }
            if (j==4){
                cout << log( gaus(v2[row][i], a, stdDev(v, a, i) )) << " ";
                p4 += log( gaus(v2[row][i], a, stdDev(v, a, i) ));
            }
        }
        cout << endl;
    }
    cout<< "p2: " << p2 << endl;
    cout<< "p4: " << p4 << endl;
    //cout<< "p3: " << p3 << endl;
    if (p2 > p4){
        return 2;
    }
    if (p4>p2){
        return 4;
    }

}


int main() {

    // vector<vector<double>> v1 = read_file();
    cout << endl << endl << "FILE VECTOR : " << endl;
    vector <vector <string> > data = vector_file("bcwisc.csv");
    vector<vector<double>> data1;
    data1=doubleConvert(data);



    for (int i = 0; i < data1.size(); i++) {
        cout << "Line " << i+1 << ": ";
        for(int j=0;j < data1[0].size(); j++){
            cout << data1[i][j] <<" ";
        }
        cout << endl;
    }

    cout << endl << endl;
    cout << "data1[410][1]" << data1[410][1] << endl;

    cout << "data1[0].size():" << data1[0].size() << endl;
    cout << "data1.size():" << data1.size() << endl;

    //split the double vector into a testing and a training set....60/40
    //683------410 / 273!!!
    vector<vector<double>> training;
    vector<vector<double>> testing;
    training.clear();
//    training.shrink_to_fit();
    testing.clear();
//    testing.shrink_to_fit();
//    //training...
    testing.reserve(273);
    training.reserve(410);


    for (int i = 0; i < data1.size() - 273; i++) {
        training.push_back(vector<double>());
        for (int j = 0; j < data1[0].size(); j++) {
            double r;
            r = data1[i][j];
            //double col = j;
            training[i].push_back(r);
        }
    }


//    //testing
    int h = 0;
    for (int k = data1.size()-273; k  < data1.size(); k++) {
        testing.push_back(vector<double>());
        for (int l = 0; l < data1[0].size(); l++) {
            double d;
            d = data1[k][l];
            //double col = j;
            testing[h].push_back(d);
        }
        h++;
    }

    cout << endl << endl << "TESTING!!!!!: " << endl;
    for ( int i = 0; i < testing.size(); i++ ) {
        cout << "Row #" << i+1 << " ";
        for (int j = 0; j < testing[i].size(); j++) {
            cout << testing[i][j] << ' ';
        }
        cout << endl;
    }


    cout << endl << endl << "TRAINING!!!!!: " << endl;

    for (int i = 0; i < training.size(); i++ ) {
        cout << "Row #" << i+1 << " ";
        for (int j = 0; j < training[i].size(); j++) {
            cout << training[i][j] << ' ';
        }
        cout << endl;
    }

//        //calc P(4);
    double probTwo=0;
    double prob2;
    for(int i=0; i<training.size();i++){
        if(training[i][9] == 2){
            ++probTwo;
        }
    }
    prob2 = probTwo / training.size();

    cout << "probability of 2 or P(2): " <<  prob2 << endl;
    cout << "log of p1 : " << log(prob2) << endl;
    //calc p(4)
    double probFour=0;
    double prob4;

    for(int i=0; i<training.size();i++){
        if(training[i][9] == 4){
            ++probFour;
        }
    }
    prob4 = probFour/training.size();

    cout << "probability of 4 or P(4): " <<  prob4 << endl;

    double sum = prob2+prob4;
    cout << "SUM : " << sum<< endl;
//used to make graphs and find avgs and std deviations
//for(int i=0;i<training.size();i++){
//    for(int j=0;j<training[i].size();j++){
//        cout<< "average for 2, col: "<< j<< " :"<< average(training,j,2)<<endl;
//        cout<< "SD for 2, col: "<< j<< " :"<< stdDev(training,average(training,j,2),j)<<endl;
//        cout<< "average for 4, col: "<< j<< " :"<< average(training,j,4)<<endl;
//        cout<< "SD for 4, col: "<< j<< " :"<< stdDev(training,average(training,j,4),j)<<endl;
//
//    }
//}
    //commented code below used to test functions
//    double num;
//    cout << "ENTER NUMBER TO TEST PROB OF: " << endl;
//    cin >> num;
//    cout<< prob(num,training);
//
//
//    int column;
//    cout << " Enter column to get mean and std dev of: " << endl;
//    cin >> column;
//
//    cout << "avg(training,column,2):  " <<average(training, column,2) << " std dev:  " << stdDev(training,average(training,column,2),column) << endl;
//    cout << "avg(training,column,4):  " <<average(training, column,4) << " std dev:  " << stdDev(training,average(training,column,4),column) << endl;
//    cout << gaus(testing[0][0] , average(training,column,4),stdDev(training,average(training,column,4),column)) << endl;
//
    cout << "CHECKING : " << endl << endl;
    int success = 0 ;
    for(int i = 0 ; i < testing.size(); i++) {

        cout << naiveBayes(training,testing, i);
        if(naiveBayes(training,testing, i) == testing[i][9]){
            cout << "Success at row " << i << endl;
            ++success;
        }
        else
            cout << "No success at row: " << i << endl;
    }
    cout << "success rate = " << success << "/273" << " = " << success/273;

//cout << "Size of vect " << vect.size() << "     Size of vect2 : " << vect2.size();


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