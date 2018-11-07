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
            Node<T>** auxrows=&(hRows->next);
            for(int i=1;i<sizeX;++i){
                Node<T>* aux2= new Node<T>{-1,-i,i, nullptr,nullptr};
                (*auxrows)=aux2;
                //cout<<(*auxrows)->data;
                auxrows=&(aux2->next);
            }


            hColumns= new Node<T>{0,-1,0, nullptr,nullptr};
            Node<T>** auxCol=&(hColumns->down);
            for(int i=1;i<sizeY;++i){
                Node<T>* aux2= new Node<T>{-i,-1,i, nullptr,nullptr};
                (*auxCol)=aux2;
                //cout<<(*auxCol)->data;
                auxCol=&(aux2->down);
            }


        }

        void set(int x, int y, T data) {
            Node<T> *nodeaux = new Node<T>{x, y, data, nullptr, nullptr};

            //--------------------------COL-----------------------------------------------
            Node<T>* auxCR = hColumns;
            for(int i=0;i<x;++i){ auxCR=auxCR->down; }
            //while (auxCol->data < nodecout<<auxCR->x;aux->x){auxCol=auxCol->down;}

            while ((auxCR->next!= nullptr)&&(nodeaux->y > auxCR->next->y)){
                auxCR=auxCR->next;
            }
            if(auxCR->next){
                nodeaux->next=auxCR->next;
            }
            auxCR->next=nodeaux;


            //-------------------------------ROW------------------------------------------
            auxCR = hRows;
            for(int i=0;i<y;++i){ auxCR=auxCR->next; }
            //while ( auxRow->data < nodeaux->y) {auxRow=auxRow->next;}

            //RECORRER COL DE ROW
            while ((auxCR->down!= nullptr)&&(nodeaux->x > auxCR->down->x)){
                auxCR=auxCR->down;
            }

            if(auxCR->down){
                nodeaux->down=auxCR->down;
            }
            auxCR->down=nodeaux;

        }

        void PrintByCol(){
            Node<T>* aux=hColumns;
            for(int i=0;i<columns;++i){
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
        void PrintByRow(){
            Node<T>* aux=hRows;
            for(int i=0;i<rows;++i){
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
            Node<T>* auxCR = hColumns;
            while (auxCR->data < x){
                auxCR=auxCR->down;
            }
            cout<<"here"<<auxCR->data<<endl;

            bool thereis=false;
            while((auxCR->next!= nullptr)&&(auxCR->y<y)){
                auxCR=auxCR->next;
                cout<<auxCR->data<<" ";
                if(auxCR->y ==y){thereis=true;cout<<"yai ";}
            }
            cout<<auxCR->data;
            if(thereis){ return auxCR->data;}
            else{
                throw "no existe";
            }

        }

        Matrix<T> operator*(Matrix<T> other){

        }

        Matrix<T> operator*(T scalar){

            Matrix nuevo(columns,rows);
            Node<T>* aux=hColumns;
            for(int i=0;i<columns;++i){
                Node<T>* aux2=aux;
                while(aux2->next!= nullptr){
                    aux2=aux2->next;
                    nuevo.set(i,aux2->y,(aux2->data)*scalar);
                }
                aux=aux->down;
            }

            return nuevo;
        }
        Matrix<T> operator+(Matrix<T> other);
        Matrix<T> operator-(Matrix<T> other);
        Matrix<T> transposed();
        Matrix<T> operator=(Matrix<T> other);

        //~Matrix();

};

#endif