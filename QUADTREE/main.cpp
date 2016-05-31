#include <iostream>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define DIVISIONES 4
template<typename T>
struct Node{
    Node *hijos[DIVISIONES];
    int x;
    int y;
    T dato;
    Node(T dato, int x, int y){
        this->x = x;
        this->y = y;
        this->dato = dato;
    }

};
template<typename T>
class QTree{
public:
    //Qtree(){}
    Node<T> *raiz;
    void Obtener_Hijo(int pos_x, int pos_y){
        //*if(pos_x<)
    }
    void Insertar(pair<>){

    }
};
void Datos(int num_datos){
    vector<pair<int,int>>Data;
    for(int i=0;i<num_datos;i++){
        int pos_x = rand()%num_datos;
        int pos_y = rand()%num_datos;
        pair<int,int>my_pair;
        my_pair = make_pair(pos_x,pos_y);
        Data.push_back(my_pair);
    }
}
int main(int argc, char *argv[])
{
    //QTree();
    return 0;
}
