#include <string>
#include <vector>

using namespace std;

int solution(vector<string> storage, vector<string> requests) {
    int answer = 0;
    int N = storage.size();
    int M = storage[0].size();
    vector<vector<bool>> vecEmpty (N, vector<bool>(M, false));
    vector<vector<bool>> vecVisted(N, vector<bool>(M, false));
    char iType;
    bool bIsCrane;
    
    auto DFS = [&](int i, int j, auto&& self)->void{
        if (vecVisted[i][j])        return;
        vecVisted[i][j] = true;
        if (!vecEmpty[i][j]){
            if (storage[i][j]!=iType) return;
            vecEmpty[i][j] = true;   
            return;
        }
        
        if (i>0){
            self(i-1,j,self);
        }
        if (i<N-1){
            self(i+1,j,self);
        }
        if (j>0){
            self(i,j-1,self);
        }
        if (j<M-1){
            self(i,j+1,self);
        }
        
    };
    
    for(const auto& _sCommand : requests){
        iType = _sCommand[0];
        bIsCrane = _sCommand.size()>1;
        vecVisted = vector<vector<bool>>(N, vector<bool>(M, false));
        for(int i=0; i< N; i++) for(int j=0; j< M; j++){
            if (bIsCrane 
                || (i==0 || j==0 || i==N-1 || j==M-1)
           ) DFS(i,j, DFS);
        }
    }
    
    for(int i=0; i< N; i++) for(int j=0; j< M; j++)
        if (!vecEmpty[i][j]) answer++;
    return answer;
}