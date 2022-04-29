
#include <iostream>
#include "Task.h"

using namespace std;

int main()
{
    const vector <double> accuracy{0.1,0.01,0.001};
    const vector <double> accuracy1{0.0001,0.00001,0.000001};
    int num=0;

    Task task;
    cout<<"FIRST METHOD"<<endl<<endl;
    for (size_t i=0;i<3;i++)
    {
        cout<<"accuracy = "<<accuracy[i]<<endl<<endl;
        num=task.firstMethod(accuracy[i]);

        cout<<"number of function calls = "<<num<<endl;
        cout<<"///////////////////////////////////////////////////////////////////////////////////////////////////"<<endl<<endl<<endl;

    }

    cout<<"SECOND METHOD"<<endl;
    for (size_t i=0;i<3;i++)
    {
        cout<<"accuracy = "<<accuracy[i]<<endl<<endl;
        num=task.secondMethod(accuracy[i]);

        cout<<"number of function calls = "<<num<<endl;
        cout<<"///////////////////////////////////////////////////////////////////////////////////////////////////"<<endl<<endl<<endl;

    }



    cout << endl<< endl<< "END";
    return 0;
}
