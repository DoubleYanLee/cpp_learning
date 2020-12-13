#include <iostream>
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Path.h"
#include "ShortestPath.h"

//邻接表适合稀疏图  邻接矩阵适合稠密图
//图的深度优先遍历可以求连通分量
//广度优先遍历 是加入到队列中就要用visited 而不是访问的时候才标记为visited
//广度优先遍历求出了无权图的最短路径
//扫雷游戏  走迷宫  迷宫生成(有的迷宫的本质是一棵树)
//欧拉路径  哈密尔顿路径  BluePath游戏  二分图  地图填色问题


int main(){
    string filename = "/Users/yannie/Desktop/Graph_theory/testG2.txt";
    SparseGraph g = SparseGraph(7, false);
    ReadGraph<SparseGraph> readGraph(g, filename);
    g.show();

    cout << endl;

    ShortestPath<SparseGraph> bfs(g,0);
    cout << "BFS: ";
    bfs.showPath(6);



    return 0;
}

//int main(){
//    string filename = "/Users/yannie/Desktop/Graph_theory/testG2.txt";
//    SparseGraph g = SparseGraph(7, false);
//    ReadGraph<SparseGraph> readGraph( g, filename );
//    g.show();
//    cout << endl;
//
//    Path<SparseGraph> dfs(g, 0);
//    cout << "DFS : ";
//    dfs.showPath(6);
//
//    return 0;
//}


//int main(){
//    string filename = "/Users/yannie/Desktop/Graph_theory/testG1.txt"; //真的绝对路径就可以了。。。 相对就不行？
//
//    SparseGraph g1 (13, false);
//    ReadGraph<SparseGraph> readGraph1(g1, filename);
//    g1.show();
//
//    cout << endl;
//
//    DenseGraph g2( 13, false );
//    ReadGraph<DenseGraph> readGraph2(g2, filename);
//    g2.show();
//
//    return 0;
//}


//int main() {
//
//    int N = 20;  int M = 100;
//
//    srand( time(NULL) );
//
//    //Sparse Graph
//    SparseGraph g1(N, false);
//
//    for( int i = 0; i < M; i ++ ){
//        int a = rand()%N;
//        int b = rand()%N;
//        g1.addEdge( a, b );
//    }
//
//    // 时间复杂度 O(E)
//    for( int v = 0; v < N; v ++ ){
//        cout << v << " : ";
//        SparseGraph::adjIterator adj( g1, v );
//        for( int w = adj.begin(); !adj.end(); w = adj.next() )
//            cout << w << " ";
//        cout << endl;
//    }
//
//    cout << endl;
//
//
//    //Dense Graph
//    DenseGraph g2(N, false);
//    for( int i = 0; i < M; i ++ ){
//        int a = rand()%N;
//        int b = rand()%N;
//        g2.addEdge( a, b );
//    }
//
//    //O(V^2)
//    for( int v = 0; v < N; v ++ ){
//        cout << v << " : ";
//        DenseGraph::adjIterator adj( g2, v );
//        for( int w = adj.begin(); !adj.end(); w = adj.next() )
//            cout << w << " ";
//        cout << endl;
//    }
//
//    cout << endl;
//
//    return 0;
//
//}