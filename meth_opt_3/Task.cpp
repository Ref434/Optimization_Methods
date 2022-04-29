#include "Task.h"





void Task::print_vector(vector<double> vec,string name)
{
    cout<<name<<"=[";
    for (auto& v : vec)
    {
        cout<<v<<",";
    }
    cout<<"]"<<endl;
}

double Task::func(double x)
{
    return ((x*x)+3*x*(log(x)-1));
}


int Task::firstMethod(double accuracy)
{
    int num=0;
    interval.a=0.5;
    interval.b=1;

    double min_el;
    double x_result;
    double f_result;
    size_t j;
   // size_t n= (interval.b-interval.a)/epsilon;
   size_t n = 15;
    while(abs(interval.b-interval.a)>=accuracy)
    {
        x.clear();
        func_on_x.clear();
        double h= (interval.b-interval.a)/(n-1);
        for(size_t i=0;i<=n-1;i++)
        {
            x.push_back(interval.a+h*i);
            func_on_x.push_back(func(interval.a+h*i));
            num++;
        }
        print_vector(x,"x");
        print_vector(func_on_x,"f");

        min_el = func_on_x[0];
        j=0;
        for(size_t i=1;i<=n;i++)
        {
            if(min_el>func_on_x[i])
            {
                min_el = func_on_x[i];
                j=i;
            }
        }
        interval.a=x[j-1];
        interval.b=x[j+1];

        cout<<"min_element = "<<min_el<<endl;
        cout<<"new interval = ["<<interval.a<<","<<interval.b<<"]"<<endl;
        cout<<"---------------------------------------------------------------------------------------------------"<<endl;

    }
    x_result=(interval.b+interval.a)/2;
    f_result=func(x_result);
    num++;


    cout<<endl<<endl;
    cout<<"x_result="<<x_result<<endl;
    cout<<"f_result="<<f_result<<endl;

    return num;
}

int Task::secondMethod(double accuracy)
{
    x.clear();
    func_on_x.clear();
    bool method=true,start=true;


    interval.a=0.5;
    interval.b=1;
    int num=0;
    vector<double> coef,X_new,F_new;
    double x_new_1,f_new_1,x_new_2=0,f_new_2=0;

    x.push_back(interval.a);
    x.push_back((interval.a+interval.b)/2);
    x.push_back(interval.b);
    func_on_x.push_back(func(interval.a));
    func_on_x.push_back(func((interval.a+interval.b)/2));
    func_on_x.push_back(func(interval.b));
    num=3;


    do{
        coef.clear();

        coef.push_back(func_on_x[0]);
        coef.push_back((func_on_x[1]-func_on_x[0])/(x[1]-x[0]));
        coef.push_back((1/(x[2]-x[1]))*(((func_on_x[2]-func_on_x[0])/(x[2]-x[0]))-((func_on_x[1]-func_on_x[0])/(x[1]-x[0]))));


        x_new_1 = (0.5)*(x[1]+x[0]-(coef[1]/coef[2]));
        f_new_1=func(x_new_1);
        num++;
        print_vector(x,"X");
        print_vector(func_on_x,"F");

        print_vector(coef,"coef");

        cout<<"x_new="<<x_new_1<<endl;
        cout<<"f_new="<<f_new_1<<endl;


        if(func_on_x[0]>f_new_1 && f_new_1<func_on_x[1] && x[0]<x_new_1 && x[1]>x_new_1)
        {
            x[2]=x[1];
            x[1]=x_new_1;

            func_on_x[2]=func_on_x[1];
            func_on_x[1]=f_new_1;

            cout<<"1 if"<<endl;
        }

        if(func_on_x[1]>f_new_1 && f_new_1<func_on_x[2] && x[1]<x_new_1 && x[2]>x_new_1)
        {
            x[0]=x[1];
            x[1]=x_new_1;

            func_on_x[0]=func_on_x[1];
            func_on_x[1]=f_new_1;

            cout<<"2 if"<<endl;
        }
        if(!start && abs(x_new_1-x_new_2)<accuracy)
            method=false;



        print_vector(x,"X_NEW");
        print_vector(func_on_x,"F_NEW");
        cout<<"---------------------------------------------------------------------------------------------------"<<endl;
        start=false;
        f_new_2=f_new_1;
        x_new_2=x_new_1;
    }while(method);



    cout<<endl<<endl;
    cout<<"x_result="<<x_new_2<<endl;
    cout<<"f_result="<<f_new_2<<endl;


    return num;

}
