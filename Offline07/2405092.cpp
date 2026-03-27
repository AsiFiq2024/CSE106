#include <iostream>
#include <vector>

using namespace std;

void transformCost(int I, int D, int R, string S, string T) {
    int M[S.size()+1][T.size()+1];
    
    for (int i = 0; i <= S.size(); i++) {
        M[i][0] = i * D;
    }
    for (int j = 0; j <= T.size(); j++) {
        M[0][j] = j * I;
    }
    
    int costI,costD,costR;

    for(int i = 1; i <= S.size(); i++){
        for(int j = 1; j <= T.size(); j++){
            bool isMatch = false;
            
            if(S[i-1] == T[j-1]){
                costR = M[i - 1][j - 1];
                isMatch = true;
            }
            else{
                costR = R + M[i - 1][j - 1];
            }
            
            costI = I + M[i][j - 1];
            costD = D + M[i - 1][j];

            if(costR <= costI && costR <= costD){
                M[i][j] = costR;
            }
            else if(costI <= costR && costI <= costD){
                M[i][j] = costI;
            }
            else{
                M[i][j] = costD;
            }
        }
    }

    cout << "Minimum Cost: " << M[S.size()][T.size()] << endl;

    vector<string> operations;

    int i = S.size(),j = T.size();

    while(i > 0 || j > 0){
        if(i > 0 && j > 0 && S[i - 1] == T[j - 1] && M[i][j] == M[i - 1][j - 1]){
            operations.push_back("Match " + string(1, S[i - 1]));
            i--; 
            j--;
        }
        else if(i > 0 && j > 0 && M[i][j] == M[i - 1][j - 1] + R){
            operations.push_back("Replace " + string(1, S[i - 1]) + " with " + string(1, T[j - 1]));
            i--; 
            j--;
        }
        else if(j > 0 && M[i][j] == M[i][j - 1] + I){
            operations.push_back("Insert " + string(1, T[j - 1]));
            j--;
        }
        else if(i > 0 && M[i][j] == M[i - 1][j] + D){
            operations.push_back("Delete " + string(1, S[i - 1]));
            i--;
        }
    }

    cout << "Operations:" << endl;
    while(operations.size() != 0){
        cout << operations.back() << endl;
        operations.pop_back();
    }
}

int main() {
    string S,T;
    int I,D,R;

    cin >> I >> D >> R;
    cin.ignore();

    getline(cin,S);
    getline(cin,T);

    transformCost(I,D,R,S,T);
}