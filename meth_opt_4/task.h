#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED
#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <string>

using namespace std;

typedef struct interval
{
    double b;
    double a;
}interval_t;



class Task
{
private:
    size_t num;
    vector <double> x;
    vector<double> func_on_x;
    interval_t interval;
    //const double epsilon = 0.05;
    double func(vector<double> X,vector<double> grad,double lambda);
    double func(double x1,double x2);
    double deriv_x1(double x1,double x2);
    double deriv_x2(double x1,double x2);

    double matrix_11(double x1,double x2);
    double matrix_12(double x1,double x2);
    double matrix_21(double x1,double x2);
    double matrix_22(double x1,double x2);

    vector<vector<double>> inverseMatrix(vector<double> x);
    vector<double> multMatrixOnVector(vector<double> grad,vector<vector<double>> matrix);


    void print_vector(vector<double> vec,string name);
    void print_matrix(vector<vector<double>> matrix);
public:
    double constStepMethod(vector<double> X,vector<double> grad,double accuracy);
    vector<vector<double>> gradMethod_first(double epsilon,double lambda);
    void gradMethod_second(double epsilon);
};

#endif // TASK_H_INCLUDED
