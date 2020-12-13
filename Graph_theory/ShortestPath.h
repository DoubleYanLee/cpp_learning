//
// Created by Yannie Lee on 12/10/20.
//

// 更多无权图的算法
// flood fill (PS中的魔棒这个功能 容忍度 https://blog.csdn.net/xiaowei_cqu/article/details/8987387 )
//


#ifndef GRAPH_THEORY_SHORTESTPATH_H
#define GRAPH_THEORY_SHORTESTPATH_H

#include<iostream>
#include<assert.h>
#include <queue>
#include <stack>


using namespace std;

template <typename Graph>
class ShortestPath{

private:
    Graph &G;
    int s;
    bool *visited;
    int *from;
    int *ord; //记录从s到每一个点的最短距离是多少

public:
    ShortestPath( Graph &graph, int s ) : G(graph){

        assert( s >= 0 && s < graph.V() );

        visited = new bool[graph.V()];
        from = new int[graph.V()];
        ord = new int[graph.V()];
        for( int i = 0 ; i < graph.V(); i ++ ){
            visited[i] = false;
            from[i] = -1;
            ord[i] = -1;
        }

        this->s = s;
        queue<int> q;

        //无向图最短路径算法
        q.push( s );
        visited[s] = true;
        ord[s] = 0;
        while( !q.empty() ){
            int v = q.front();
            q.pop();

            typename Graph::adjIterator adj(G, v);
            for( int i = adj.begin(); !adj.end(); i = adj.next() ){
                if( !visited[i] ){
                    q.push(i);
                    visited[i] = true;
                    from[i] = v;
                    ord[i] = ord[v] + 1;
                }
            }

        }


    }

    ~ShortestPath(){
        delete []visited;
        delete []from;
        delete [] ord;

    }

    bool hasPath(int w){

        assert( w >= 0 && w < G.V() );
        return visited[w];

    }

    void path( int w, vector<int> &vec ){

        stack<int> s;

        int p = w;
        while( p != -1 ){
            s.push(p);
            p = from[p];
        }

        vec.clear();
        while( !s.empty() ){
            vec.push_back( s.top() );
            s.pop();
        }

    }

    void showPath(int w){

        vector<int> vec;
        path( w, vec );
        for( int i = 0 ; i < vec.size(); i ++ ){
            cout << vec[i];
            if( i == vec.size() - 1 )
                cout << endl;
            else
                cout << " -> ";
        }

    }

    int length(int w){

        assert( w >= 0 && w < G.V() );
        return ord[w];

    }




};



#endif //GRAPH_THEORY_SHORTESTPATH_H
