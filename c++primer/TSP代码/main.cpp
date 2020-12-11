#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <float.h>


using namespace std;

#define m 5				//蚂蚁的个数
#define n 4				//城市的数量

const int NC_max = 100;		//最大迭代次数
const double Alpha = 1;		//表征信息素重要程度的参数
const double Beta = 5;		//表征启发式因子重要程度的参数
const double Rho = 0.1;		//信息素蒸发系数
const double Q = 100;		//信息素增加强度系数
const double C[n][2] =		//各个城市的坐标数据
        {	{ 0,0 },   //城市0
            { 1,0 },  //城市1
            { 1,1 }, //城市2
            { 2,1 } //城市3
        };

double D[n][n];			//表示完全图的邻接矩阵
double Eta[n][n];		//表示启发式因子，为D中距离的倒数
double DeltaTau[n][n];	//表示启发式因子的变化量
double Tau[n][n];		//路径上面信息素的浓度
int Tabu[m][n];			//禁忌表，存储走过的路径

double L_best[NC_max];		//存储每次迭代的路径的最短长度
double L_ave[NC_max];		//存储每次迭代的路径的平均长度
int R_best[NC_max][n];		//存储每次迭代的最佳路线


void ValueInit(void)		//变量初始化函数
{
    for (int i = 0; i < n; i++)			//初始化 D[n][n]
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
                D[i][j] = pow(pow((C[i][0] - C[j][0]), 2) + pow((C[i][1] - C[j][1]), 2), 0.5);
            else
                D[i][j] = DBL_EPSILON;
        }
    }


    for (int i = 0; i < n; i++)			//初始化 Eta[n][n]
        for (int j = 0; j < n; j++)
            Eta[i][j] = 1.0 / D[i][j];

    for (int i = 0; i < n; i++)			//初始化 DeltaEta[n][n]
        for (int j = 0; j < n; j++)
            DeltaTau[i][j] = 0;

    for (int i = 0; i < n; i++)			//初始化 Tau[n][n]
        for (int j = 0; j < n; j++)
            Tau[i][j] = 1.0;

    for (int i = 0; i < m; i++)			//初始化 Tabu[m][n]
        for (int j = 0; j < n; j++)
            Tabu[i][j] = 0;
}

void ValueDisplayTabu(int (*p)[n])	//禁忌表，存储走过的路径, 显示函数
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << *(*(p + i) + j) << ' ';
        }
        cout << endl;
    }
}

void ValueDisplayTau(double(*p)[n])		//信息素的浓度,显示函数
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << *(*(p + i) + j) << ' ';
        }
        cout << endl;
    }
}

double rnd(double lower, double uper)	//生成lower和uper之间的一个double类型随机数
{
    return  (rand() / (double)RAND_MAX) * (uper - lower) + lower;
}

int main()
{
    //第一步：进行变量的初始化
    ValueInit();

    int NC = 0;
    while(NC < NC_max)
    {
        //第二步：将m只蚂蚁随机放到n个城市上
        vector<int> temp;
        for (int i = 0; i < ceil((double)m / (double)n); i++)
        {
            for (int j = 0; j < n; j++)
                temp.push_back(j);
        }


       // random_shuffle(temp.begin(), temp.end());	//打乱temp数组中元素的次序

        for (int i = 0; i < m; i++)
        {
            Tabu[i][0] = temp[i];
        }

        //第三步：m只蚂蚁按概率函数选择n中的下一座城市，完成各自的周游
        for (int j = 1; j < n; j++)
        {
            for (int i = 0; i < m; i++)
            {
                vector<int> visited;	//第i只蚂蚁已访问过的城市
                vector<int> J;			//第i只蚂蚁待访问的城市
                vector<double> P;		//第i只蚂蚁待访问的城市的概率

                double Psum = 0.0;		//概率值和
                double rate = 0.0;		//随机数
                double choose = 0.0;	//轮盘赌算法累加值
                int to_visit;			//下一个要去的城市

                for (int k = 0; k < j; k++)
                    visited.push_back(Tabu[i][k]);	//visited初始化

                for (int k = 0; k < n; k++)
                {
                    if (find(visited.begin(), visited.end(), k) == visited.end())	//在visited中没有找到t
                    {
                        J.push_back(k);				//J初始化
                        P.push_back(0.0);			//P初始化
                    }
                }

                for (int k = 0; k < P.size(); k++)	//计算去下一座城市的概率
                {
                    P[k] = pow(Tau[visited.back()][J[k]], Alpha) * pow(Eta[visited.back()][J[k]], Beta);
                    Psum += P[k];
                }

                rate = rnd(0.0, Psum);				//使用轮盘赌算法，挑选下一座要去的城市
                for (int k = 0; k < P.size(); k++)
                {
                    choose += P[k];
                    if (choose > rate)
                    {
                        to_visit = J[k];
                        break;
                    }
                }

                Tabu[i][j] = to_visit;				//更新禁忌表
            }
        }

        //第四步：记录本次迭代蚂蚁行走的路线数据
        double L[m];	//记录本代每只蚂蚁走的路程，并初始化
        for (int i = 0; i < m; i++)
        {
            L[i] = 0.0;
        }
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n - 1; j++)
            {
                L[i] += D[ Tabu[i][j] ][ Tabu[i][j + 1] ];
            }
            L[i] += D[ Tabu[i][0] ][ Tabu[i][n - 1] ]; //最后还要回来一下
        }

        double min_value = L[0];	//声明求本代所有蚂蚁行走距离最小值的临时变量
        double sum_value = L[0];	//声明求本代所有蚂蚁行走距离总值的临时变量
        int min_index = 0;			//记录本代所有蚂蚁行走距离最小值的下标
        for (int i = 1; i < m; i++)
        {
            sum_value += L[i];
            if (L[i] < min_value)
            {
                min_value = L[i];
                min_index = i;
            }
        }

        L_best[NC] = min_value;						//每代中路径的最短长度
        L_ave[NC] = sum_value / m;					//每代中路径的平均长度

        for (int i = 0; i < n; i++)
        {
            R_best[NC][i] = Tabu[min_index][i];		//记录每代最短的路径数据
        }

        cout << NC << ": L_best is " << L_best[NC] << ' ' << "L_ave is " << L_ave[NC] << endl;	//打印各代距离信息

        NC++;	//迭代继续

        //第五步：更新信息素
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n - 1; j++)
            {
                DeltaTau[ Tabu[i][j] ][ Tabu[i][j + 1] ] += Q / L[i];	//此次循环在整个路径上的信息素增量
            }
            DeltaTau[ Tabu[i][n - 1] ][ Tabu[i][0] ] += Q / L[i];
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                Tau[i][j] = (1 - Rho) * Tau[i][j] + DeltaTau[i][j];	//考虑信息素挥发，更新后的信息素
            }
        }

        //每一代之后将禁忌表🆑

        for (int i = 0; i < m; i++)			//禁忌表清零
            for (int j = 0; j < n; j++)
                Tabu[i][j] = 0;
    }

    //第六步：把结果画出来
    double min_L = L_best[0];			//所有迭代中最短距离
    int min_L_index = 0;				//所有迭代中最优路径的下标
    int Shortest_Route[n];				//所有迭代中的最优路径
    for (int i = 0; i < NC; i++)
    {
        if (L_best[i] < min_L)
        {
            min_L = L_best[i];
            min_L_index = i;
        }
    }

    cout << "The length of the shortest route is " << min_L << endl;
    cout << "The number of iteration is " << min_L_index << endl;
    cout << "The Shortest route is： " << endl << "start";

    for (int i = 0; i < n; i++)		//所有迭代中的最优路径
    {
        Shortest_Route[i] = R_best[min_L_index][i];
        cout << " -> " << Shortest_Route[i];
    }


    return 0;
}