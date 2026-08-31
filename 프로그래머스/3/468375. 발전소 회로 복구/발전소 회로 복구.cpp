#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

//1. 판넬 간 거리 계산
//2. 마스킹

using namespace std;

int solution(int h, vector<string> grid, vector<vector<int>> panels, vector<vector<int>> seqs) {
    int answer = 0;
    int n = panels.size();
    
    auto GetDist = [&](int r0, int c0, int r1, int c1){
        int iX = grid.size();
        int iY = grid[0].size();
        vector<vector<int>> vecCost(iX, vector<int>(iY, iX*iY));
        queue<pair<int,int>> q;
        q.push({r0,c0});
        vecCost[r0][c0]=0;
        while(q.size()){
            auto [iCurX, iCurY] = q.front();
            q.pop();
            if (iCurX==r1 && iCurY==c1){
                return vecCost[iCurX][iCurY];
            }
            for(auto [dx, dy] : {pair<int,int>(-1,0), pair<int,int>(+1,0), pair<int,int>(0,+1), pair<int,int>(0,-1)}){
                int nx(iCurX+dx), ny(iCurY+dy);
                if(nx<0 || nx >= iX)        continue;
                if(ny<0 || ny >= iY)        continue;
                if(grid[nx][ny]=='#')       continue;
                if(vecCost[nx][ny]!=iX*iY)  continue;
                
                q.push({nx,ny});
                vecCost[nx][ny] = vecCost[iCurX][iCurY]+1;
            }
        }
        
        return -1000;
    };
    
    pair<int,int> pEV;
    for(int i=0; i<grid.size(); i++) for(int j=0; j<grid[0].size(); j++){
        if (grid[i][j]=='@'){
            pEV.first   =i;
            pEV.second  =j;
            break;
        }
    }
    
    vector<int> vecMask(n,0);
    for(auto _seq : seqs) vecMask[_seq[1]-1] |= 1<<(_seq[0]-1);
    
    vector<vector<int>> vecDist(n, vector<int>(n, 0));
    for(int i=0; i<n; i++) for(int j=i; j<n; j++){
        int iCost = 0;
        
        auto panelA = panels[i];
        auto panelB = panels[j];
        
        if(panelA[0]==panelB[0]){
            iCost += GetDist(panelA[1]-1, panelA[2]-1, panelB[1]-1, panelB[2]-1);
        }
        else{
            iCost += abs(panelA[0]-panelB[0]);
            iCost += GetDist(pEV.first, pEV.second, panelA[1]-1, panelA[2]-1);
            iCost += GetDist(pEV.first, pEV.second, panelB[1]-1, panelB[2]-1);
        }
        
        vecDist[i][j] = vecDist[j][i] = iCost;
    }
    
    //for(int i=0; i<n; i++, cout<<endl) for(int j=0; j<n; j++) cout << vecDist[i][j] << '\t';
    
    const int MAXV = 40*40*10*15*4;
    vector<vector<int>> vecDP((1<<n), vector<int>(n, MAXV));
    for(int i=0; i<n; i++){
        if (vecMask[i]==0)
            vecDP[1<<i][i] = vecDist[0][i];
    }
    for(int iMask=0; iMask<(1<<n); iMask++) for(int i=0; i<n; i++){
        if (vecDP[iMask][i]==MAXV) continue;
        for(int j=0; j<n; j++){
            if ((vecMask[j] & iMask)!=vecMask[j]) continue;
            int iNxtMask = iMask | (1<<j);
            vecDP[iNxtMask][j] = min(vecDP[iNxtMask][j], vecDP[iMask][i]+vecDist[i][j]);
        }
    }
    
    
    answer = *min_element(vecDP.back().begin(), vecDP.back().end());
    
    return answer;
}