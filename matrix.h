#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"

using namespace std;

template <typename T>
class Matrix {
    private:
        Node<T>* hRows;
        Node<T>* hColumns;
        int columns;
        int rows;

    public:
        Matrix(){
            hRows= nullptr;
            hColumns= nullptr;
            columns=0;
            rows=0;
        }

        Matrix(int sizeX, int sizeY){
                columns = sizeY;
                rows = sizeX;

                hRows = new Node<T>{-1, -1, 0, nullptr, nullptr};
                Node<T> **auxrows = &(hRows->down);
                for (int i = 1; i < sizeX; ++i) {
                    Node<T> *aux2 = new Node<T>{-i, -1, i, nullptr, nullptr};
                    (*auxrows) = aux2;
                    //cout<<(*auxrows)->data;
                    auxrows = &(aux2->down);
                }


                hColumns = new Node<T>{0, -1, 0, nullptr, nullptr};
                Node<T> **auxCol = &(hColumns->next);
                for (int i = 1; i < sizeY; ++i) {
                    Node<T> *aux2 = new Node<T>{-1, -i, i, nullptr, nullptr};
                    (*auxCol) = aux2;
                    //cout<<(*auxCol)->data;
                    auxCol = &(aux2->next);
                }
        }

        void set(int x, int y, T data) {
            if(x<rows && y<columns) {
                if(data!=0) {
                    if((*this)(x,y)==0) {
                        Node<T> *nodeaux = new Node<T>{x, y, data, nullptr, nullptr};

                        //--------------------------ROW-----------------------------------------------
                        Node<T> *auxCR = hRows;
                        for (int i = 0; i < x; ++i) { auxCR = auxCR->down; }
                        //while (auxCol->data < nodecout<<auxCR->x;aux->x){auxCol=auxCol->down;}

                        while ((auxCR->next != nullptr) && (nodeaux->y > auxCR->next->y)) {
                            auxCR = auxCR->next;
                        }
                        if (auxCR->next) {
                            nodeaux->next = auxCR->next;
                        }
                        auxCR->next = nodeaux;


                        //-------------------------------COL------------------------------------------
                        auxCR = hColumns;
                        for (int i = 0; i < y; ++i) { auxCR = auxCR->next; }
                        //while ( auxRow->data < nodeaux->y) {auxRow=auxRow->next;}

                        //RECORRER COL DE ROW
                        while ((auxCR->down != nullptr) && (nodeaux->x > auxCR->down->x)) {
                            auxCR = auxCR->down;
                        }

                        if (auxCR->down) {
                            nodeaux->down = auxCR->down;
                        }
                        auxCR->down = nodeaux;
                    }
                    else{
                        find(x,y)->data=data;
                    }
                }
                else{
                    if((*this)(x,y)!=0){
                        Eliminar( find(x,y) );
                    }
                }
            }
            else{
                cout<<endl<<"valores fuera del rango"<<endl;
            }
        }

        void Eliminar(Node<T>* nodo){
            int x=nodo->x;
            int y=nodo->y;
            if((*this)(x,y) != 0) {
                Node<T> * aux2;
                //--------------------------ROW-----------------------------------------------
                Node<T> *auxCR = hRows;
                for (int i = 0; i < x; ++i) { auxCR = auxCR->down; }
                //while (auxCol->data < nodecout<<auxCR->x;aux->x){auxCol=auxCol->down;}

                while ((auxCR->next != nullptr) && (y > auxCR->next->y)) {
                    auxCR = auxCR->next;
                }
                aux2=auxCR->next;
                if(auxCR->next->next!= nullptr){
                    auxCR->next=auxCR->next->next;
                }
                else{
                    auxCR->next= nullptr;
                }

                //-------------------------------COL------------------------------------------
                auxCR = hColumns;
                for (int i = 0; i < y; ++i) { auxCR = auxCR->next; }
                //while ( auxRow->data < nodeaux->y) {auxRow=auxRow->next;}

                while ((auxCR->down != nullptr) && (x > auxCR->down->x)) {
                    auxCR = auxCR->down;
                }

                if(auxCR->down->down!= nullptr){
                    auxCR->down=auxCR->down->down;
                } else{auxCR->down= nullptr;}

                aux2->next= nullptr;
                aux2->down= nullptr;

                delete (aux2);
            }
        }

        void PrintByRow(){
            Node<T>* aux=hRows;
            for(int i=0;i<rows;++i){
                Node<T>* aux2=aux;
                cout<<i<<": ";
                while(aux2->next!= nullptr){
                    aux2=aux2->next;
                    cout<<aux2->data<<" ";
                }

                cout<<endl;
                aux=aux->down;
            }
        }

        void PrintByCol(){
            Node<T>* aux=hColumns;
            for(int i=0;i<columns;++i){
                Node<T>* aux2=aux;
                cout<<i<<": ";
                while(aux2->down!= nullptr){
                    aux2=aux2->down;
                    cout<<aux2->data<<" ";
                }
                cout<<endl;
                aux=aux->next;
            }
        }

        T operator()(int x, int y) {
            if(x<rows && y<columns) {
                Node<T>* auxCR = hRows;
                for(int i=0;i<x;++i){
                    auxCR=auxCR->down;
                }

                bool thereis=false;

                while((auxCR->next!= nullptr)&&(auxCR->y<y)){
                    auxCR=auxCR->next;
                    if(auxCR->y ==y){thereis=true;
                        break;
                    }
                }
                if(thereis){
                    return auxCR->data;
                }
                else{
                    return 0;
                }

            } else{ throw "sale del rango";}

        }

        Node<T>* find(int x, int y){
            Node<T>* auxCR = hRows;
            for(int i=0;i<x;++i){
                auxCR=auxCR->down;
            }
            bool thereis=false;

            while((auxCR->next!= nullptr)&&(auxCR->y<y)){
                auxCR=auxCR->next;
                if(auxCR->y ==y){thereis=true;
                    break;
                }
            }
            if(thereis){ return (auxCR);}
            else{
                return nullptr;
            }
        }

        Matrix<T> operator*(Matrix<T> other){
            if(this->columns==other.rows){
                Matrix nuevo(rows,other.columns);

                for(int i=0;i<rows;++i){
                    for(int j=0;j<other.columns;++j){
                        T total=0;
                        for(int k=0; k<columns;++k){
                            if( (*this)(i,k)!=0 || other(k,j)!= 0 ) {
                                total = total + ((*this)(i, k))*(other(k, j));
                            }
                        }
                        if(total!=0){
                            nuevo.set(i,j,total);
                        }
                    }

                }
                return nuevo;
            }
            else{throw "No tiene las dimensiones adecuadas";}
        }

        Matrix<T> operator*(T scalar){
            Matrix nuevo(rows,columns);
            Node<T>* aux=hRows;
            for(int i=0;i<rows;++i){
                Node<T>* aux2=aux;
                while(aux2->next!= nullptr){
                    aux2=aux2->next;
                    nuevo.set(i,aux2->y,(aux2->data)*scalar);
                }
                aux=aux->down;
            }
            return nuevo;
        }

        Matrix<T> operator+(Matrix<T> other){
            if((rows==other.rows)&&(columns==other.columns)){
                Matrix<T> nuevo=(*this)*1;

                Node<T>* aux11=nuevo.hRows;
                Node<T>* aux12=other.hRows;

                for(int i=0;i<rows;++i){
                    Node<T>* aux1=aux11;//nuevo
                    Node<T>* aux2=aux12;//other

                    while(aux2->next!= nullptr){
                        aux2=aux2->next;
                        if(nuevo(i,aux2->y)!=0){
                            nuevo.set(i,aux2->y, nuevo(i,aux2->y) + other(i,aux2->y));
                            //*(nuevo.find(i,aux2->y))=(*(nuevo.find(i,aux2->y)) + other(i,aux2->y));
                        }
                        else{
                            nuevo.set(i, aux2->y, aux2->data);
                        }
                    }

                    aux11=aux11->down;
                    aux12=aux12->down;
                }

                return nuevo;

            }
            else{throw "no se puede porque son de distintos tamaños";}
        }

        Matrix<T> operator-(Matrix<T> other){
            if((rows==other.rows)&&(columns==other.columns)){
                Matrix<T> nuevo=(*this)*1;

                Node<T>* aux11=nuevo.hRows;
                Node<T>* aux12=other.hRows;

                for(int i=0;i<rows;++i){
                    Node<T>* aux1=aux11;//nuevo
                    Node<T>* aux2=aux12;//other

                    while(aux2->next!= nullptr){
                        aux2=aux2->next;
                        if(nuevo(i,aux2->y)!=0){
                            nuevo.set(i,aux2->y, nuevo(i,aux2->y) - other(i,aux2->y));
                            //*(nuevo.find(i,aux2->y))=(*(nuevo.find(i,aux2->y)) - other(i,aux2->y));
                        }
                        else{
                            nuevo.set(i, aux2->y,-(aux2->data));
                        }
                    }

                    aux11=aux11->down;
                    aux12=aux12->down;
                }

                return nuevo;

            }
            else{throw "no se puede";}
        }

        Matrix<T> transposed(){
            Matrix<T> nuevo(columns,rows);

            Node<T>* aux=hRows;
            for(int i=0;i<rows;++i){
                Node<T>* aux2=aux;
                while(aux2->next!= nullptr){
                    aux2=aux2->next;
                    nuevo.set(aux2->y,aux2->x,aux2->data);
                }
                aux=aux->down;
            }
            return nuevo;
        }

        Matrix<T> operator=(Matrix<T> other){
            //Matrix nuevo=(*this)*1;

            Matrix <T> nuevo(rows, columns);
            Node<T>* aux=hColumns;
            for(int i=0;i<columns;++i){
                Node<T>* aux2=aux;
                while(aux2->next!= nullptr){
                    aux2=aux2->next;
                    nuevo.set(i,aux2->y,(aux2->data));
                }
                aux=aux->down;
            }

            return nuevo;
        }


        ~Matrix(){

        }


};

#endif