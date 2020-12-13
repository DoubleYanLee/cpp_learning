//
// Created by Yannie Lee on 12/12/20.
//

#ifndef RIGHTGRAPH_EDGE_H
#define RIGHTGRAPH_EDGE_H


#include<iostream>
#include<cassert>

using namespace std;


template<typename Weight>
class Edge{

private:
    int a, b;
    Weight weight;

public:
    Edge(int a, int b, Weight weight){
        this->a = a;
        this->b = b;
        this->weight = weight;
    }

    Edge( ){ }
    ~Edge( ){ }

    int v( ){ return a; }
    int w( ){ return b; }

    Weight wt( ){ return weight; }

    int other( int x ){
        //返回另外一个顶点
        assert( x == a || x == b );
        return x == a ? b : a;
    }

    friend ostream &operator<<(ostream &os, const Edge &e){
        os << e.a << "-" << e.b << ": " << e.weight;
        return os;
    }

    bool operator<(Edge<Weight>& e){
        return weight < e.wt();
    }

    bool operator<=(Edge<Weight>& e){
        return weight <= e.wt();
    }

    bool operator>(Edge<Weight>& e){
        return weight > e.wt();
    }

    bool operator>=(Edge<Weight>& e){
        return weight >= e.wt();
    }

    bool operator==(Edge<Weight>& e){
        return weight == e.wt();
    }


};

#endif //RIGHTGRAPH_EDGE_H
