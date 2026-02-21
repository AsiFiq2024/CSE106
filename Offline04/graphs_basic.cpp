#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class Graph
{
    int V;
    list<int> *l;

public:
    Graph(int v)
    {
        V = v;
        l = new list<int>[V];
    }
    
    void addEdge(int u, int v)
    {
        l[u].push_back(v);
        l[v].push_back(u);
    }
    
    void bfs()
    { // O(V+E)
        queue<int> q;
        vector<bool> vis(V, false);

        q.push(0);
        vis[0] = true;

        while (q.size() > 0)
        {
            int u = q.front();
            q.pop();

            cout << u << " ";

            for (int v : l[u])
            {
                if (!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    
    void dfsHelper(int u, vector<bool> &vis)
    {
        cout << u << " ";
        vis[u] = true;

        for (int v : l[u])
        {
            if (!vis[v])
            {
                dfsHelper(v, vis);
            }
        }
    }
    
    void dfs()
    {
        vector<bool> vis(V, false);

        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                dfsHelper(i, vis);
            }
        }
    }

    bool cycle_dfs(int src, vector<bool> &vis, int par)
    {
        vis[src] = true;

        for (int v : l[src])
        {
            if (!vis[v])
            {
                if (cycle_dfs(v, vis, src))
                    return true;
            }
            else if (v != par)
            {
                return true;
            }
        }
        return false;
    }
    
    bool cycle_bfs(int src, vector<bool> &vis)
    {
        queue<pair<int, int>> q;

        q.push({src, -1});
        vis[0] = true;

        while (q.size() > 0)
        {
            int u = q.front().first;
            int u_par = q.front().second;
            q.pop();

            for (int v : l[u])
            {
                if (!vis[v])
                {
                    q.push({v, u});
                    vis[v] = true;
                }
                else if (v != u_par)
                {
                    return true;
                }
            }
        }
        return false;
    }

    void isCycle()
    {
        vector<bool> vis(V, false);

        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                if (cycle_bfs(i, vis)) // cycle_dfs(i, vis, -1))
                {
                    cout << "Yes" << endl;
                    return;
                }
            }
        }
        cout << "No" << endl;
    }
};

int main()
{
    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 4);
    g.addEdge(3, 2);
    g.addEdge(3, 4);
    g.addEdge(3, 5);

    cout << "BFS: ";
    g.bfs();
    cout << endl;

    cout << "DFS: ";
    g.dfs();
    cout << endl;

    cout << "Cycle exist: ";
    g.isCycle();

    return 0;
}