#include <iostream>
#include <iomanip>
#include "DenseGraph.h"
#include "SparseGraph.h"
#include "ReadGraph.h"
#include "LazyPrimMST.h"
#include "PrimMST.h"
#include "KruskalMST.h"

//带权图的第一个问题 最小生成树问题 Minimum Span Tree  使用最小堆来完成
//krukal中判断是否有环 可以用并查集的方法 在放入时看看这两个点是否有共同的顶点 有共同的顶点证明其已经连接在一起了，再放进去就会形成环
//最小生成树算法还有一个实现 Vyssotsky's Algorithm 将边逐渐地添加到生成树中，一旦形成环，删除环中权值最大地边


using namespace std;

int main(){

    string filename = "/Users/yannie/Desktop/Graph_theory/RightGraph/testG1.txt";
    int V = 8;

    SparseGraph<double> g = SparseGraph<double>(V, false);
    ReadGraph< SparseGraph<double>, double > readGraph(g,  filename );

    cout << "Test Lazy Prim MST: " << endl;
    LazyPrimMST< SparseGraph<double>, double > lazyPrimMst(g);
    vector< Edge<double> > mst = lazyPrimMst.mstEdges();
    for( int i = 0 ; i < mst.size(); i ++ )
        cout << mst[i] << endl;

    cout << "The MST weight is: " << lazyPrimMst.result() << endl;

    cout << endl;

    // Test Prim MST
    cout<<"Test Prim MST:"<<endl;
    PrimMST<SparseGraph<double>, double> primMST(g);
    mst = primMST.mstEdges();
    for( int i = 0 ; i < mst.size() ; i ++ )
        cout<<mst[i]<<endl;
    cout<<"The MST weight is: "<<primMST.result()<<endl;

    cout<<endl;

    // Test Kruskal MST
    cout<<"Test Kruskal MST:"<<endl;
    KruskalMST<SparseGraph<double>, double> kruskalMST(g);
    mst = kruskalMST.mstEdges();
    for( int i = 0 ; i < mst.size() ; i ++ )
        cout<<mst[i]<<endl;
    cout<<"The MST weight is: "<<kruskalMST.result()<<endl;



    return 0;
}




//int main(){
//
//    string filename = "/Users/yannie/Desktop/Graph_theory/RightGraph/testG1.txt";
//    int V = 8;
//    cout << fixed << setprecision(2);
//
//    DenseGraph<double> g1 = DenseGraph<double>(V, false);
//    ReadGraph< DenseGraph<double>, double > readGraph1(g1, filename);
//    g1.show();
//    cout << endl;
//
//    SparseGraph<double> g2 = SparseGraph<double>(V, false);
//    ReadGraph<SparseGraph<double>,double> readGraph2(g2, filename);
//    g2.show();
//    cout<<endl;
//
//
//
//    return 0;
//
//
//}