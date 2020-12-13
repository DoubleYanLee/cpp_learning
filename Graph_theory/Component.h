//
// Created by Yannie Lee on 12/10/20.
//

#ifndef GRAPH_THEORY_COMPONENT_H
#define GRAPH_THEORY_COMPONENT_H

#include <iostream>
#include <cassert>

//深度优先算法的时间复杂度 邻接表 O(V+E) 邻接矩阵 O(V^2)
//使用深度优先遍历来查找有向图中是否有环

using namespace std;

template <typename Graph>
class Component{

private:
    Graph &G;
    bool *visited;
    int ccount;
    int *id; //用来查看哪两个节点是相连的

    void dfs( int v ){

        visited[v] = true;
        id[v] = ccount;
        typename Graph::adjIterator adj(G, v);
        for( int i = adj.begin(); !adj.end(); i = adj.next() ){
            if( !visited[i] )
                dfs(i);
        }
    }

public:
    Component(Graph &graph): G(graph){

        visited = new bool[G.V()];
        id = new int[G.V()];
        ccount = 0;
        for( int i = 0; i < G.V(); i ++ ){
            visited[i] = false;
            id[i] = -1;
        }

        for( int i = 0; i < G.V(); i ++ ){
            if( !visited[i] ){
                dfs(i);
                ccount ++;
            }
        }

    }

    ~Component(){
        delete [] visited;
        delete [] id;
    }

    int count(){
        return ccount;
    }

    bool isconnected( int v, int w ){
        assert( v >= 0 && v < G.V() );
        assert( w >= 0 && w < G.V() );

        return id[v] == id[w];
    }


};


#endif //GRAPH_THEORY_COMPONENT_H
