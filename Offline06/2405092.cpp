#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<vector<int>> connectedIDs;
double totalCost = 0;

class City
{
public:
    int id;
    double x;
    double y;

    City(int ID, double X, double Y)
    {
        id = ID;
        x = X;
        y = Y;
    }
};

double distance(const City &a, const City &b)
{
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

bool isConnected(vector<vector<int>> &connectedIDs, int id1, int id2)
{
    for (int v : connectedIDs[id1])
    {
        if (v == id2)
        {
            return true;
        }
    }
    return false;
}

void connectCities(vector<City> &cities, int i, int j)
{
    double minDis;
    int minIdx;

    for (int l = i; l < j; l++)
    {
        minDis = distance(cities[l], cities[l + 1]);
        minIdx = l + 1;
        for (int r = i; r <= j; r++)
        {
            if (r == l)
                continue;

            double d = distance(cities[l], cities[r]);

            if (!isConnected(connectedIDs, cities[l].id, cities[r].id) && d < minDis)
            {
                minDis = d;
                minIdx = r;
            }
        }
        if (!isConnected(connectedIDs, cities[l].id, cities[minIdx].id))
        {
            totalCost += minDis;
            connectedIDs[cities[l].id].push_back(cities[minIdx].id);
            connectedIDs[cities[minIdx].id].push_back(cities[l].id);
        }
    }
}

void mergeCities(vector<City> &cities, int leftEnd, int rightStart, int M)
{
    double minD = 1e18;
    int minIdx1 = -1;
    int minIdx2 = -1;

    for (int i = leftEnd; i >= leftEnd - M + 1; i--)
    {
        for (int j = rightStart; j <= rightStart + M - 1; j++)
        {
            double d = distance(cities[i], cities[j]);
            if (d < minD)
            {
                minD = d;
                minIdx1 = i;
                minIdx2 = j;
            }
        }
    }

    if (minIdx1 != -1)
    {
        totalCost += minD;

        connectedIDs[cities[minIdx1].id].push_back(cities[minIdx2].id);
        connectedIDs[cities[minIdx2].id].push_back(cities[minIdx1].id);
    }
}

void citySplit(vector<City> &cities, int i, int j, int M)
{
    if (j - i + 1 <= M)
    {
        connectCities(cities, i, j);
        return;
    }

    int mid = i + (j - i) / 2;

    citySplit(cities, i, mid, M);
    citySplit(cities, mid + 1, j, M);

    mergeCities(cities, mid, mid + 1, M);
}

void printOut(vector<City> &cities, int N)
{
    vector<vector<bool>> isPrinted(N + 1, vector<bool>(N + 1, false));

    printf("Total Cost: %.2f\n", totalCost);
    cout << "Edges: " << endl;
    for (int u = 0; u < N; u++)
    {
        for (int v : connectedIDs[cities[u].id])
        {
            if (!isPrinted[cities[u].id][v])
            {
                cout << cities[u].id << " " << v << endl;
                isPrinted[cities[u].id][v] = true;
                isPrinted[v][cities[u].id] = true;
            }
        }
    }
}

int main()
{
    vector<City> cities;

    int N, M;

    cin >> N >> M;

    connectedIDs.resize(N + 1);

    for (int i = 0; i < N; i++)
    {
        int id;
        double x, y;
        cin >> id >> x >> y;
        cities.push_back(City(id, x, y));
    }

    sort(cities.begin(), cities.end(), [](const City &a, const City &b)
         { return a.x < b.x; });

    citySplit(cities, 0, cities.size() - 1, M);

    printOut(cities, N);
}