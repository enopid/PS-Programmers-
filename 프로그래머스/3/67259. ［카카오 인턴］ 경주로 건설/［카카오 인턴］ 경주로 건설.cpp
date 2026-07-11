#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<vector<int>> board) {
    int answer = 0;
    int n = board.size();
    int m = board[0].size();
    
    vector<vector<vector<int>>> vecMinPath(n, vector<vector<int>>(m, vector<int>(2, -1)));
    
    //(cost, node*2 + 1), 0 : vertical 1: horizontal
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; 
    
    pq.push({0, 0});
    pq.push({0, 1});
    while(pq.size()){
        auto [iCost, _info] = pq.top();
        pq.pop();
        int  iNode          = _info/2;
        int  ix             = iNode/m;
        int  iy             = iNode%m;
        int  bIsVertical    = _info%2;
        
        if (ix==n-1 && iy==m-1){
            answer = iCost;
            break;   
        }
        if (vecMinPath[ix][iy][bIsVertical]!=-1)
            continue;
        vecMinPath[ix][iy][bIsVertical] = iCost;
        
        
        pair<int,int> _tmp;
        for(auto[_dx, _dy] : {
            pair<int, int>(-1,+0),
            pair<int, int>(+1,+0),
            pair<int, int>(+0,-1),
            pair<int, int>(+0,+1),
        }){
            int _nx(ix+_dx),  _ny(iy+_dy);
            if (_nx<0 || _nx>=n) continue;
            if (_ny<0 || _ny>=m) continue;
            if (board[_nx][_ny]) continue;
            
            if (abs(_dx)==bIsVertical)//동일방향
                _tmp.first = iCost+100;
            else
                _tmp.first = iCost+100+500;
            
            _tmp.second = _nx*m+_ny;
            _tmp.second *=2;
            if (_dy==0) _tmp.second+=1;
            
            pq.push(_tmp);
        }
    }
    
    return answer;
}