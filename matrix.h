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
        Matrix();
        Matrix(int sizeX, int sizeY){
            columns=sizeY;
            rows=sizeX;

            hRows= new Node<T>{-1,0,0, nullptr,nullptr};
            Node<T>** auxrows=&(hRows->down);
            for(int i=1;i<sizeX;++i){
                Node<T>* aux2= new Node<T>{-1,-i,i, nullptr,nullptr};
                (*auxrows)=aux2;
                //cout<<(*auxrows)->data;
                auxrows=&(aux2->down);
            }


            hColumns= new Node<T>{0,-1,0, nullptr,nullptr};
            Node<T>** auxCol=&(hColumns->next);
            for(int i=1;i<sizeY;++i){
                Node<T>* aux2= new Node<T>{-i,-1,i, nullptr,nullptr};
                (*auxCol)=aux2;
                //cout<<(*auxCol)->data;
                auxCol=&(aux2->next);
            }


        }

        void set(int x, int y, T data) {
            if(x<rows && y<columns) {

                Node<T> *nodeaux = new Node<T>{x, y, data, nullptr, nullptr};

                //--------------------------COL-----------------------------------------------
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


                //-------------------------------ROW------------------------------------------
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
                cout<<endl<<"valores fuera del rango"<<endl;
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
                T *aux = this->find(x, y);
                if (aux != nullptr) {
                    return *aux;
                } else {
                    throw "no existe";
                }
            } else{ throw "sale del rango";}

        }

        T* find(int x, int y){
            Node<T>* auxCR = hRows;
            while (auxCR->data < x){
                auxCR=auxCR->down;
            }
            bool thereis=false;
            while((auxCR->next!= nullptr)&&(auxCR->y<y)){
                auxCR=auxCR->next;
                if(auxCR->y ==y){thereis=true;}
            }
            if(thereis){ return &(auxCR->data);}
            else{
                return nullptr;
            }
        }

        Matrix<T> operator*(Matrix<T> other){

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
                        if(nuevo.find(i,aux2->y)){
                            *(nuevo.find(i,aux2->y))=(*(nuevo.find(i,aux2->y)) + other(i,aux2->y));
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
            else{throw "no se puede";}
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
                        if(nuevo.find(i,aux2->y)){
                            *(nuevo.find(i,aux2->y))=(*(nuevo.find(i,aux2->y)) - other(i,aux2->y));
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
            Matrix<T> nuevo(rows,columns);
            /*
            Node<T>* aux=hColumns;
            for(int i=0;i<columns;++i){
                Node<T>* aux2=aux;
                while(aux2->next!= nullptr){
                    aux2=aux2->next;
                    int aux3=aux2->y;
                    aux2->y=aux2->x;
                }
                aux=aux->down;
            }
            Node<T>* aux4=hColumns;
            hColumns=hRows;
            hRows=aux4;
            */
            Node<T>* aux=hRows;
            for(int i=0;i<rows;++i){
                Node<T>* aux2=aux;
                while(aux2->next!= nullptr){
                    aux2=aux2->next;
                    nuevo.set(aux2->y,i,aux2->data);
                }
                aux=aux->down;
            }

            return nuevo;

        }

        Matrix<T> operator=(Matrix<T> other){
            Matrix nuevo=(*this)*1;
            /*
            Node<T>* aux=hColumns;
            for(int i=0;i<columns;++i){
                Node<T>* aux2=aux;
                while(aux2->next!= nullptr){
                    aux2=aux2->next;
                    nuevo.set(i,aux2->y,(aux2->data));
                }
                aux=aux->down;
            }
*/
            return nuevo;
        }

        //~Matrix();

};

#endif