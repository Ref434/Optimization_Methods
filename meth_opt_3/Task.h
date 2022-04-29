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
    const double epsilon = 0.05;
    double func(double x);

    void print_vector(vector<double> vec,string name);
public:
    int firstMethod(double accuracy);
    int secondMethod(double accuracy);
};

#endif // TASK_H_INCLUDED
