#include <vector>
#include <iostream>


using namespace std;

template<class T>
struct Punto
{
    T x, y;
    Punto(T x = 0, T y = 0):x(x), y(y){}
};
template<class T>
struct Node{
    Punto<T> dato;
    Node<T> *SE;
    Node<T> *NE;
    Node<T> *NW;
    Node<T> *SW;
    Node(Punto<T> p){
        SE = nullptr;
        NE = nullptr;
        NW = nullptr;
        SW = nullptr;
        dato = p;
    }
};
template<class T>
class PointQuadTree{
    Node<T>*raiz;
    Node<T> **q;
    //Node<T> **r;
public:
    Node<T> **r;
    vector<Punto<T>> result_consulta;
    PointQuadTree(){
        raiz = nullptr;
    }
    bool contiene(Punto<T>punto_ini,Punto<T>punto_fin,Punto<T> a)
    {
        if( ( ((punto_ini.x <= a.x && a.x <= punto_fin.x)  ||  (punto_ini.x >= a.x && a.x >= punto_fin.x) ) &&
                ((punto_ini.y <= a.y && a.y <= punto_fin.y)  ||  (punto_ini.y >= a.y && a.y >= punto_fin.y) ) ))
        {
            return true;
        }
        return false;
    }
    void PuntoCardinal(Punto<T>a,Punto<T>b, Node<T>**&q ){ //b es el q qiero insertar
        if(b.x < a.x && b.y> a.y)
        {
            q = &(*q)->NW;
        }
        else if(b.x < a.x && b.y< a.y)
        {
            q = &(*q)->SW;
        }
        else if(b.x > a.x && b.y> a.y)
        {
            //cout<<"entro ne"<<endl;
            q = &(*q)->NE;
        }
        else//(b.x > a.x && b.y < a.y)
        {
            q = &(*q)->SE;
        }
    }

    bool insert(Punto<T> p){
        //Node<T> **q;
        if(!raiz){
            q    = &raiz;
            r    = &raiz;
            raiz = new Node<T>(p);
            return true;
        }
        if(!(*q)){
            (*q) = new Node<T>(p);
            //q se inserta al final
             q = &raiz;
            return true;
        }
        //si aun todos son nullptr
        if(!(*q)->NE ){
            PuntoCardinal( (*q)->dato,p ,q);
            insert(p);
        }
        else{
            PuntoCardinal( (*q)->dato,p ,q);
            insert(p);
        }
    }
    bool PointQuery(Punto<T>p){
        if( (*r) ){
            if( (*r)->dato.x == p.x && (*r)->dato.y == p.y ){
                cout<<"Se encontro el punto: "<<(*r)->dato.x<<","<<(*r)->dato.y<<endl;
                return true;
            }
            else{
                PuntoCardinal( (*r)->dato ,p,r);
                PointQuery(p);
            }
        }
    }
    void range_recur(Node<T>* &p,Punto<T> a , Punto<T> b ){
       if(!(p)) return;
       else{
            if( contiene(a,b,(p)->dato) )
            result_consulta.push_back( (p)->dato);
       }
       range_recur( (p)->SE, a , b );
       range_recur( (p)->NE, a , b );
       range_recur( (p)->SW, a , b );
       range_recur( (p)->NW, a , b );

    }
    void RangeQuery(Punto<T> a , Punto<T> b)
    {
            Node<T> **p = &raiz;
            range_recur( *p,a,b );
    }

    void PrintRange(){
        cout<<"RESULTADO DEL RANGE QUERY"<<endl;
        for(int i=0;i<result_consulta.size();i++){
            cout<<result_consulta[i].x<<","<<result_consulta[i].y<<endl;
        }
    }
};

int main(){
    PointQuadTree<double> A;
    //A.insert( Punto<double>(1,1) );
    A.insert( Punto<double>(2,3) );
    A.insert( Punto<double>(3,45) );
    A.insert( Punto<double>(4,5) );
    A.insert( Punto<double>(-1,-1) );
    A.insert( Punto<double>(-4,50) );
    A.insert( Punto<double>(4,-7) );
    A.insert( Punto<double>(-2,-5) );
    //A.insert( Punto<double>(-3,9) );
    //A.insert( Punto<double>(-300,999) );
    //A.print();
    A.PointQuery( Punto<double> (-1000,1000) );
    A.RangeQuery( Punto<double>(-11,11),Punto<double>(11,-11) );
    A.PrintRange();
    return 0;
}
