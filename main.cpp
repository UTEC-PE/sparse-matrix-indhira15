//#include <GL/glut.h>
#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]) {
    Matrix<int> a(5, 5);
    a.set(2,1,12);
    a.set(1,1,30);
    a.set(1,0,11);
    a.set(3,2,5);
    a.set(3,1,6);
    a.set(4,1,1);
    a.set(0,2,4);
    a.set(1,3,5);
    cout<<"print ------------------"<<endl;
    a.PrintByCol();
    cout<<"print inv---------------"<<endl;
    a.PrintByRow();
    cout<<a(3,1);
    cout<<endl<<"operator * T ----------"<<endl;
    (a*2).PrintByCol();
    cout<<"operator ="<<endl;
    Matrix<int> B =a*2;
    (a*3).PrintByCol();
    cout<<endl<<"operator + MAtrix-------------------"<<endl;
    (a+B).PrintByCol();



    //system("PAUSE");
    return EXIT_SUCCESS;
}