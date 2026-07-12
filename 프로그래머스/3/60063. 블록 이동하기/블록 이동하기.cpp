#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> board) {
    int answer = 0;
    int n = board.size();
    
    vector<vector<vector<int>>> vecMinPath(n, vector<vector<int>>(n, vector<int>{-1,-1}));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;//(cost, info) / info = 2*(x*n+y) + bVertical
    pq.push({0, 0});
    while(pq.size())
    {
        auto [iCost, iInfo]     = pq.top();
        auto iPos       = iInfo/2;
        auto ix         = iPos/n;
        auto iy         = iPos%n;
        auto bVertical  = iInfo%2;
        pq.pop();
        if (vecMinPath[ix][iy][bVertical]!=-1)
            continue;
        vecMinPath[ix][iy][bVertical]=iCost;
        
        if (bVertical){
            if (ix==n-2 && iy ==n-1){
                answer = iCost;
                break;
            }
        }
        else{
            if (ix==n-1 && iy ==n-2){
                answer = iCost;
                break;
            }
        }
        
        //Move
        pair<int, int> _tmp;
        for (auto [_dx, _dy] : {
            pair<int,int>(+1,+0),
            pair<int,int>(-1,-0),
            pair<int,int>(+0,+1),
            pair<int,int>(-0,-1),
        }){
            int nx(ix+_dx), ny(iy+_dy);
            //Check Valid
            if (nx<0 || nx>=n) continue;
            if (ny<0 || ny>=n) continue;
            if (bVertical){
                if (nx+1<0 || nx+1>=n) continue;
            }
            else{
                if (ny+1<0 || ny+1>=n) continue;
            }
            
            //Check Wall
            if (board[nx][ny]) continue;
            if (bVertical){
                if (board[nx+1][ny]) continue;
            }
            else{
                if (board[nx][ny+1]) continue;
            }
            
            //Add Node
            _tmp.first  = iCost +1;
            _tmp.second = 2*(nx*n+ny)+bVertical;
            
            //Add
            pq.push(_tmp);
        }
        
        //Rotate
        _tmp.first  = iCost +1;
        if (bVertical){
            if (iy+1<n && board[ix][iy+1]==0 && board[ix+1][iy+1]==0){
                _tmp.second = 2*((ix)*n+(iy+0))+(1-bVertical);
                pq.push(_tmp);
                _tmp.second = 2*((ix+1)*n+(iy+0))+(1-bVertical);
                pq.push(_tmp);
            }
            if (iy-1>=0 && board[ix][iy-1]==0 && board[ix+1][iy-1]==0){
                _tmp.second = 2*((ix)*n+(iy-1))+(1-bVertical);
                pq.push(_tmp);
                _tmp.second = 2*((ix+1)*n+(iy-1))+(1-bVertical);
                pq.push(_tmp);
            }
        }
        else{
            if (ix+1<n && board[ix+1][iy]==0 && board[ix+1][iy+1]==0){
                _tmp.second = 2*((ix)*n+(iy))+(1-bVertical);
                pq.push(_tmp);
                _tmp.second = 2*((ix)*n+(iy+1))+(1-bVertical);
                pq.push(_tmp);
                
            }
            if (ix-1>=0 && board[ix-1][iy]==0 && board[ix-1][iy+1]==0){
                _tmp.second = 2*((ix-1)*n+(iy))+(1-bVertical);
                pq.push(_tmp);
                _tmp.second = 2*((ix-1)*n+(iy+1))+(1-bVertical);
                pq.push(_tmp);
            }
        }
    }
    
    //for(int i=0; i<n; i++, cout << endl) for(int j=0; j<n; j++) cout << "(" << vecMinPath[i][j][0]<<"/"<< vecMinPath[i][j][1]<< ")\t";
        
    
    return answer;
}