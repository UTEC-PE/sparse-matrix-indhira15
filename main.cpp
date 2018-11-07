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
    a(3,2);
    cout<<"multiplicacion----------"<<endl;
    (a*2).PrintByCol();



    //system("PAUSE");
    return EXIT_SUCCESS;
}