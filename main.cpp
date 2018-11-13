//#include <GL/glut.h>
#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]) {
    /*
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
    (a*2).PrintByRow();
    cout<<"operator ="<<endl;
    Matrix<int> B =a*2;
    (a*3).PrintByCol();
    cout<<endl<<"operator + Matrix-------------------"<<endl;
    B.set(0,0,55);
    (a-B).PrintByCol();
    (a.transposed()).PrintByCol();
*/
    Matrix<int> c(4,3);
    c.set(0,1,2);
    c.set(0,2,14);
    c.set(1,0,15);
    c.set(2,2,29);
    c.set(2,1,60);
    c.set(3,1,30);
    cout<<"print by row: "<<endl;
    c.PrintByRow();
    cout<<"print by col: "<<endl;
    c.PrintByCol();
    cout<<"transpuestas"<<endl;
    (c.transposed()).PrintByRow();
    cout<<endl<<"multiplicacion"<<endl;
    Matrix <int > e(3,3);
    e.set(0,0,2);
    e.set(0,2,1);
    e.set(1,0,3);
    e.set(2,0,5);
    e.set(2,1,1);
    e.set(2,2,1);
    cout<<e(2,2)<<endl;
    Matrix<int> d(3,3);
    d.set(0,0,1);
    d.set(0,2,1);
    d.set(1,0,1);
    d.set(1,1,2);
    d.set(1,2,1);
    d.set(2,0,1);
    d.set(2,1,1);
    cout<<"e: "<<endl;
    e.PrintByRow();
    cout<<"d :"<<endl;
    d.PrintByRow();
    cout<<"c*d :"<<endl;
    (e*d).PrintByRow();



    //system("PAUSE");
    return EXIT_SUCCESS;
}