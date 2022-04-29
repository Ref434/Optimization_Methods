
#include <iostream>
#include "task.h"

using namespace std;

int main()
{

    Task task;
    Task task2;
    cout<<"FIRST METHOD"<<endl<<endl;
    vector<vector<double>> x1,x2;
    x1=task.gradMethod_first(0.1,0.01);
    x2=task.gradMethod_first(0.1,0.15);
    for(int i =0; i < x1.size(); ++i){
        if(i < x2.size())
            cout<<x1[i][0] <<","<<x1[i][1] <<"   "<< x2[i][0]<<","<<x2[i][1]<<endl;
        else
            cout<<x1[i][0]<<","<<x1[i][1]  <<"   "<<endl;
    }

    task.gradMethod_first(0.01,0.01);
    //task.gradMethod_first(0.001,0.01);

    cout<<"SECOND METHOD"<<endl<<endl;
    task2.gradMethod_second(0.000001);



    cout << endl<< endl<< "END";
    return 0;
}

