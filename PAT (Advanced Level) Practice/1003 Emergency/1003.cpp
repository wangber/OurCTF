#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

struct Vertex{
    int index;
    int dist;
    int team;
    int teamsum;
    int pathnum;
    bool visited;
    Vertex(int i, int d):index(i), dist(d), teamsum(0), pathnum(0), visited(false){}
};


void relax(int x, int y, vector<Vertex> &cities, vector<vector<int>> adj){
    if(cities[y].dist > cities[x].dist + adj[x][y]){
        cities[y].dist = cities[x].dist + adj[x][y];
        cities[y].pathnum = cities[x].pathnum;
        cities[y].teamsum = cities[x].teamsum + cities[y].team;
    }
    else if(cities[y].dist == cities[x].dist + adj[x][y]){
        cities[y].pathnum += cities[x].pathnum;
        if(cities[y].teamsum < cities[y].team + cities[x].teamsum)
            cities[y].teamsum = cities[y].team + cities[x].teamsum;
    }
}

int main(){
    int vn, en, src, dest;
    cin >> vn >> en >> src >> dest;
    //初始化城市列表
    vector<Vertex> cities;
    for(int i = 0; i < vn; ++i){
        Vertex temp(i, INT_MAX);
        cin >> temp.team;
        cities.push_back(temp);
    }


    //初始化邻接矩阵
    vector<int> init(vn, -1);
    vector<vector<int>> adjcent_matrix(vn, init);
    for(int i = 0; i < en; ++i){
        int temp1, temp2, templen;
        cin >> temp1 >> temp2;
        cin >> templen;
        adjcent_matrix[temp1][temp2] = adjcent_matrix[temp2][temp1] = templen;
    }


/*
    //为优先队列设置比较函数
    struct cmp{
        bool operator() (Vertex* a, Vertex* b){
            return a->dist > b->dist;
        }
    };

    //初始化dijkstra算法最小优先队列Q
    priority_queue<Vertex*, vector<Vertex*>, cmp> q;
    cities[src].dist = 0;
    cities[src].pathnum = 1;
    cities[src].teamsum = cities[src].team;
    for(int i = 0; i < vn; ++i){
        q.push(&cities[i]);
    }
*/

    cities[src].dist = 0;
    cities[src].pathnum = 1;
    cities[src].teamsum = cities[src].team;
    for(int j = 0; j < vn; j++){
        int u = -1, minn = INT_MAX;
        //Vertex* x = q.top();
        for(int i = 0; i < vn; ++i){
            if(cities[i].visited == false && cities[i].dist < minn){
                u = i;
                minn = cities[i].dist;
            }
        }
        if(u == -1) break;     //找不到最小距离城市
        Vertex* x = &cities[u];
        for(int i = 0; i < vn; ++i){
            if(adjcent_matrix[x->index][i]>0){                //存在连接
                relax(x->index, i, cities, adjcent_matrix);
            }
        }
        //q.pop();
        cities[u].visited = true;
    }


    cout << cities[dest].pathnum << " " << cities[dest].teamsum;

    return 0;
}
