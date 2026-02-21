#include <iostream>
#include <list>
#include <vector>
#include <fstream>

using namespace std;

class Graph{
    int N;
    list<int> *L;
    int grp_count = 0;
public:
    Graph(int n){
        N = n;
        L = new list<int>[N];
    }
    void add(int u, int v){
        L[u].push_back(v);
        L[v].push_back(u);
    }

    void group(int a, vector<bool>& visit, vector<int> &teams){
        cout << a;
        teams.push_back(a);
        visit[a] = true;

        for(int v : L[a]){
            if(!visit[v]){
                cout << ", ";
                group(v,visit,teams);
            }
        }
    }
    void printGroups(){
        vector<bool> visited(N,false);
        int grp_serial = 0;

        for(int i = 0; i < N; i++){
            if(!visited[i]){
                grp_serial++;
                vector<int> grpTeams;
                cout << "Group " << grp_serial << ": {";
                group(i,visited,grpTeams);
                cout << "} | ";
                DNPdetect(grpTeams);
                cout << endl;
            }
        }
    }
    void group_visiter(int a, vector<bool> &visit){
        visit[a] = true;

        for(int v : L[a]){
            if(!visit[v]){
                group_visiter(v,visit);
            }
        }
    }
    int group_no(){
        vector<bool> visited(N, false);
        
        for(int i = 0; i < N; i++){
            if(!visited[i]){
                grp_count++;
                group_visiter(i,visited);
            }
        }
        return grp_count;
    }
    void DNPdetect(vector<int> &teams){
        int F = 0;
        for(int i = 0; i < teams.size() - 1; i++){
            int a = teams[i];
            for(int j = i + 1; j < teams.size(); j++){
                int b = teams[j]; 
                int f = 0;
                for(int v : L[b]){
                    if(a == v){
                        f = 1;
                        break;
                    }
                }
                if(!f){
                    cout << "[" << a << ", " << b << "] ";
                    F = 1;
                }
            }
        }
        if(!F){
            cout << "none";
        }
    }
};

int main(){
    int n,u,v;
    ifstream in("input.txt");

    in >> n;
    Graph g(n);
    
    while(in >> u >> v){
        g.add(u,v);
    }

    cout << g.group_no() << endl;
    g.printGroups();
}