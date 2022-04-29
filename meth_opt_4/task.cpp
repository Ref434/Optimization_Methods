#include "task.h"





void Task::print_vector(vector<double> vec,string name)
{
    cout<<name<<"=[";
    for (auto& v : vec)
    {
        cout<<v<<",";
    }
    cout<<"]"<<endl;
}

void Task::print_matrix(vector<vector<double>> matrix)
{
    cout<<"------MATRIX-------"<<endl;

    for(size_t i=0;i<2;i++)
    {
        for(size_t j=0;j<2;j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}


double Task::func(vector<double> X,vector<double> grad,double lambda)
{
    return ((X[0]-lambda*grad[0])*(X[0]-lambda*grad[0])+(3*(X[1]-lambda*grad[1])*(X[1]-lambda*grad[1]))+cos((X[0]-lambda*grad[0])+2*(X[1]-lambda*grad[1])));
}

double Task::func(double x1,double x2)
{
    return ((x1*x1)+(3*x2*x2)+cos(x1+2*x2));
}


double Task::deriv_x1(double x1,double x2)
{
    return ((2*x1)-sin(x1+(2*x2)));
}

double Task::deriv_x2(double x1,double x2)
{
    return ((6*x2)-2*sin(x1+(2*x2)));
}

double Task::matrix_11(double x1,double x2)
{
    return (2-cos(x1+2*x2));
}

double Task::matrix_12(double x1,double x2)
{
    return ((-2)*cos(x1+2*x2));
}

double Task::matrix_21(double x1,double x2)
{
    return ((-2)*cos(x1+2*x2));
}

double Task::matrix_22(double x1,double x2)
{
    return (6-(4*cos(x1+2*x2)));
}





vector<vector<double>> Task::gradMethod_first(double epsilon,double lambda)
{

    int n=0;
    vector<double> x1={0,0},x2={5,5};
    vector<vector<double>> my_x;
    cout << "accuracy = " <<epsilon << endl;
    cout << "const step = " <<lambda << endl<< endl;
    while (sqrt(deriv_x1(x2[0],x2[1])*deriv_x1(x2[0],x2[1])+(deriv_x2(x2[0],x2[1])*deriv_x2(x2[0],x2[1])))> epsilon)
    {
        x1[0]=x2[0], x1[1]=x2[1];
        x2[0]=x1[0]-lambda*deriv_x1(x1[0],x1[1]); // находим новое значение х1
        x2[1]=x1[1]-lambda*deriv_x2(x1[0],x1[1]); // находим новое значение х2
        //my_x.push_back(x2);
        n++; // наращиваем итерации
    }
    cout << "min: (" << x2[0] << ";" << x2[1] << ")" << endl;
    cout << "min func: " << func(x2[0],x2[1]) << endl;
    cout << "num iterations: " << n << endl << endl;
    return my_x;
}

vector<vector<double>> Task::inverseMatrix(vector<double> x)
{
    vector<vector<double>> matrix={{0,0},{0,0}};
    matrix[0][0]=matrix_11(x[0],x[1]);
    matrix[0][1]=matrix_12(x[0],x[1]);
    matrix[1][0]=matrix_21(x[0],x[1]);
    matrix[1][1]=matrix_22(x[0],x[1]);
    double det =  matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
    double tmp=matrix[0][0];
    matrix[0][0]=matrix[1][1];
    matrix[1][1]=tmp;
    matrix[0][1]=-1*matrix[0][1];
    matrix[1][0]=-1*matrix[1][0];
    matrix[0][0]=matrix[0][0]/det;
    matrix[0][1]=matrix[0][1]/det;
    matrix[1][0]=matrix[1][0]/det;
    matrix[1][1]=matrix[1][1]/det;
    return matrix;
}

vector<double> Task::multMatrixOnVector(vector<double> grad,vector<vector<double>> matrix)
{
    vector<double> result={0,0};
    result[0]=(matrix[0][0]*grad[0]+matrix[0][1]*grad[1]);
    result[1]=(matrix[1][0]*grad[0]+matrix[1][1]*grad[1]);


    return result;
}

void Task::gradMethod_second(double epsilon)
{
    int n=0;
    double lambda;
    vector<double> x1={0,0},x2={5,5};
    vector<double> grad;
    vector<vector<double>> matrix;
    cout << "accuracy = " <<epsilon << endl<< endl;
    while (sqrt(deriv_x1(x2[0],x2[1])*deriv_x1(x2[0],x2[1])+(deriv_x2(x2[0],x2[1])*deriv_x2(x2[0],x2[1])))> epsilon)
    {
        //cout<<  epsilon<<endl;
        x1[0]=x2[0];
        x1[1]=x2[1];



        matrix=inverseMatrix(x1);
        grad={deriv_x1(x1[0],x1[1]),deriv_x2(x1[0],x1[1])};
        grad=multMatrixOnVector(grad,matrix);
        lambda = constStepMethod(x2,grad,0.0001);

        x2[0]=x1[0]-lambda*grad[0];
        x2[1]=x1[1]-lambda*grad[1];
        cout << "x: (" << x2[0] << ";" << x2[1] << ")" <<"  alpha="<<lambda<<"        1-e/r=0.6"<< endl;
        n++;
    }

    cout << "min: (" << x2[0] << ";" << x2[1] << ")" << endl;
    cout << "min func: " << func(x2[0],x2[1]) << endl;
    cout << "num iterations: " << n << endl << endl;


}






double Task::constStepMethod(vector<double> X,vector<double> grad,double accuracy)
{
    interval.a=0;
    interval.b=1;

    double min_el;
    double x_result;
    size_t j;
    size_t n = 10;
    while(abs(interval.b-interval.a)>=accuracy)
    {
        x.clear();
        func_on_x.clear();
        double h= (interval.b-interval.a)/(n-1);
        for(size_t i=0;i<=n-1;i++)
        {
            x.push_back(interval.a+h*i);
            func_on_x.push_back(func(X,grad,interval.a+h*i));
        }


        min_el = func_on_x[0];
        j=0;
        for(size_t i=1;i<n;i++)
        {
            if(min_el>func_on_x[i])
            {
                min_el = func_on_x[i];
                j=i;
            }
        }
        interval.a=x[j-1];
        interval.b=x[j+1];

    }
    x_result=(interval.b+interval.a)/2;

    return x_result;
}

