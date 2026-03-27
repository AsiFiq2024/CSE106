#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class Graph
{
    int V;
    list<int> *l;
    queue<pair<int,int>> q;
    vector<int> T;

public:
    Graph(int v)
    {
        V = v;
        l = new list<int>[V];
        T.resize(V);
    }
    
    void addEdge(char u, char v)
    {
        l[u - 'A'].push_back(v - 'A');
        //l[v].push_back(u);
    }
    
    void bfs(int i)
    { // O(V+E)
        vector<bool> vis(V, false);

        q.push({i,1});
        vis[i] = true;

        while (q.size() > 0)
        {
            int u = q.front().first;
            int t = q.front().second; 
            T[u] = t;
            q.pop();

            for (int v : l[u])
            {
                if (!vis[v])
                {
                    vis[v] = true;
                    q.push({v,t+1});
                }
            }
        }
    }

    void getGen(){
        int gen = 0;
        for(int i = 0; i < V; i++){
            if(l[i].size() == 1){
                gen++;
            }
        }
        cout << gen << endl;
    }

    void getOnlyChild(){
        for(int i = 0; i < V; i++){
            if(l[i].size() == 1){
                cout << "[" ;
                cout << (char)(l[i].front() + 'A') << "," << T[l[i].front()] << "]" << endl;
            }
        }
    }
};

int main()
{
    int n;
    cin >> n;
    
    Graph g(n+1);

    for(int i = 0; i < n; i++){
        char u,v;
        cin >> u >> v;
        g.addEdge(u,v);
    }

    g.bfs(0);
    g.getGen();
    g.getOnlyChild();
}