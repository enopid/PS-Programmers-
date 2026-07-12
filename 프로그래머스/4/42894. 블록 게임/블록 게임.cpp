#include <string>
#include <vector>
#include <iostream>

//XXOO
//XOOX
//OXXX
//누운거 3개 / 서있는거 2개

using namespace std;

int solution(vector<vector<int>> board) {
    int answer = 0;
    int n = board.size();
    int m = board[0].size();
    vector<vector<int>> vecMarker(n, vector<int>(m, -1));
    
    vector<vector<bool>> vecMasks[5];
    vecMasks[0] = vector<vector<bool>>{vector<bool>{true, false, false}, vector<bool>{true, true, true}};
    vecMasks[1] = vector<vector<bool>>{vector<bool>{false, false, true}, vector<bool>{true, true, true}};
    vecMasks[2] = vector<vector<bool>>{vector<bool>{false, true, false}, vector<bool>{true, true, true}};
    vecMasks[3] = vector<vector<bool>>{vector<bool>{true, false}, vector<bool>{true, false}, vector<bool>{true, true}};
    vecMasks[4] = vector<vector<bool>>{vector<bool>{false, true}, vector<bool>{false, true}, vector<bool>{true, true}};
    
    auto CheckAndRemove = [&](int i, int j, int k) {
        int iFilterSize0 = vecMasks[k].size();
        int iFilterSize1 = vecMasks[k][0].size();
        
        if (i+iFilterSize0>n) return false;
        if (j+iFilterSize1>m) return false;
        
        bool bIsPossible    = true;
        int  iSegment       = -1;
        for(int x=0; x<iFilterSize0; x++) for(int y=0; y<iFilterSize1; y++){
            if (vecMasks[k][x][y]){
                if (board[i+x][j+y]<=0) bIsPossible = false;
                
                if (iSegment==-1)
                    iSegment = board[i+x][j+y];
                else{
                    if (board[i+x][j+y]!=iSegment) 
                        bIsPossible = false;
                }
            }
            else{
                if (board[i+x][j+y]!=-1) bIsPossible = false;
            }
        }
        
        if(bIsPossible){
            for(int x=0; x<iFilterSize0; x++) for(int y=0; y<iFilterSize1; y++){
                if (board[i+x][j+y]>0)
                    board[i+x][j+y] = 0;
            }
            
            return true;
        }
        return false;
    };
    
    for(int i=0; i<n; i++) for(int j=0; j<m; j++) for(int k=0; k<5; k++){
        int iFilterSize0 = vecMasks[k].size();
        int iFilterSize1 = vecMasks[k][0].size();
        
        if (i+iFilterSize0>n) continue;
        if (j+iFilterSize1>m) continue;
            
        bool bIsPossible    = true;
        int  iSegment       = -1;
        for(int x=0; x<iFilterSize0; x++) for(int y=0; y<iFilterSize1; y++){
            if (vecMasks[k][x][y]){
                if (board[i+x][j+y]==0) bIsPossible = false;
                
                if (iSegment==-1)
                    iSegment = board[i+x][j+y];
                else{
                    if (board[i+x][j+y]!=iSegment) 
                        bIsPossible = false;
                }
            }
        }
        
        if (bIsPossible){
            vecMarker[i][j] = k;
        }
    }
    
    //for(int i=0; i<n; i++, cout << endl) for(int j=0; j<m; j++) cout << board[i][j] << "\t";
    //cout << endl;
    //for(int i=0; i<n; i++, cout << endl) for(int j=0; j<m; j++) cout << vecMarker[i][j] << "\t";
    
    vector<int> vecZeros(m, 0);
    bool bChange = true;
    while(bChange){
        for(int i=0; i<m; i++){
            while(vecZeros[i]<n && board[vecZeros[i]][i]==0){
                board[vecZeros[i]][i]=-1;
                vecZeros[i]+=1;
            }
        }
        bChange = false;
        for(int i=0; i<n; i++) for(int j=0; j<m; j++){
            int iMaker = vecMarker[i][j];
            if (iMaker==-1)continue;
            if (CheckAndRemove(i, j, iMaker)){
                answer++;
                bChange = true;
            }
        }
    }
    
    return answer;
}