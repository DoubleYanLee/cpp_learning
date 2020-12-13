//
// Created by Yannie Lee on 12/10/20.
//

#ifndef GRAPH_THEORY_SPARSEGRAPH_H
#define GRAPH_THEORY_SPARSEGRAPH_H


#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"

using namespace std;

//稠密图 —— 邻接矩阵
template<typename Weight>
class SparseGraph{

private:
    int n, m;
    bool directed;
    vector< vector< Edge<Weight>* > > g;

public:
    SparseGraph( int n, bool directed ){
        this->n = n;
        this->m = 0;
        this->directed = directed;
        for( int i = 0; i < n ; i ++ )
            g.push_back( vector< Edge<Weight>* >() );
    }

    ~SparseGraph(){

        for( int i = 0; i < n ; i ++)
            for( int j = 0 ; j < g[i].size(); j ++ )
                delete g[i][j];


    }

    int V() { return n; }
    int E() { return m; }

    void addEdge( int v, int w, Weight weight){ //这里v和w只能是1 2这种数字了吧

        assert( v >= 0 && v < n );
        assert( w >= 0 && w < n );

        //对于稀疏表 不处理平行边

        g[v].push_back( new Edge<Weight>( v, w, weight ) );
        if( v != w && !directed ) //去掉自环边的情况
            g[w].push_back(new Edge<Weight>( v, w, weight ));

        m ++;

    }

    bool hasEdge( int v , int w ){

        assert( v >= 0 && v < n );
        assert( w >= 0 && w < n );

        for( int i = 0; i < g[v].size(); i ++ )
            if( g[v][i]->other(v) == w )
                return true;
        return false;
    }

    void show(){
        for( int i = 0; i < n; i ++ ){
            cout << " vertex " << i << ":\t";
            for( int j = 0; j < g[i].size(); j ++ )
                cout << "( to: " << g[i][j]->w() << ",wt:" << g[i][j]->wt() << ")\t";
            cout << endl;
        }

    }


    class adjIterator{
    private:
        SparseGraph &G;
        int v;
        int index; //指示当前迭代到哪里了
    public:
        adjIterator( SparseGraph &graph, int v ) : G(graph){

            this->v = v;
            this->index = 0;
        }

        Edge<Weight>* begin(){
            index = 0;
            if( G.g[v].size() )
                return G.g[v][index];
            return nullptr;
        }

        Edge<Weight>* next(){
            index ++;
            if( index < G.g[v].size() )
                return G.g[v][index];
            return nullptr;
        }

        bool end(){
            return index >= G.g[v].size();
        }

    };

};




#endif //GRAPH_THEORY_SPARSEGRAPH_H
