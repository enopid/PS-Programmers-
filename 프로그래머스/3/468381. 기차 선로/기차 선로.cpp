#include <string>
#include <vector>
#include <iostream>

// 8*8
// 백트래킹
// 특정 진입점을 산정시 가능경로는 4개 
// 내가생각하는 방식은 일단은 쭉 진행

using namespace std;

using pos = pair<int,int>;

int solution(vector<vector<int>> grid) {
    int answer = 0;
    int n = grid.size();
    int m = grid[0].size();
    int iCnt =0;
    auto PrintBoard = [&](){
        if (iCnt++>=10) return;
        for(int i=0; i<n; i++, cout << endl) for(int j=0; j<m; j++) cout << grid[i][j] << '\t';
        cout << endl;
    };
    
    auto IsValid = [&](pos _curPos, pos _prevPos)->pos{
        pos _nxtPos = pos(-1,-1);
        auto _dy = _curPos.first  - _prevPos.first;
        auto _dx = _curPos.second - _prevPos.second;
        auto iTileType = grid[_curPos.first][_curPos.second];
        if (iTileType==1){
            if (_dx!=0){
                _nxtPos = _curPos;
                _nxtPos.second+=_dx;
            }
        }
        else if (iTileType==2){
            if (_dy!=0){
                _nxtPos = _curPos;
                _nxtPos.first+=_dy;
            }
        }
        else if (iTileType==3){
            _nxtPos = _curPos;
            _nxtPos.second +=_dx;
            _nxtPos.first+=_dy;
        }
        else if (iTileType==4){
            if (_dx==1){
                _nxtPos = _curPos;
                _nxtPos.first-=1;
            }
            else if (_dy==1){
                _nxtPos = _curPos;
                _nxtPos.second-=1;
            }
        }
        else if (iTileType==5){
            if (_dx==-1){
                _nxtPos = _curPos;
                _nxtPos.first-=1;
            }
            else if (_dy==1){
                _nxtPos = _curPos;
                _nxtPos.second+=1;
            }
        }
        else if (iTileType==6){
            if (_dx==-1){
                _nxtPos = _curPos;
                _nxtPos.first+=1;
            }
            else if (_dy==-1){
                _nxtPos = _curPos;
                _nxtPos.second+=1;
            }
        }
        else if (iTileType==7){
            if (_dx==1){
                _nxtPos = _curPos;
                _nxtPos.first+=1;
            }
            else if (_dy==-1){
                _nxtPos = _curPos;
                _nxtPos.second-=1;
            }
        }
        
        return _nxtPos;
    };
    auto CheckBoard = [&]()->bool{
        vector<vector<int>> vecVisited = vector<vector<int>>(n, vector<int>(m, 0));
        
        auto _curPos  = pos(0,1);
        auto _prevPos = pos(0,0);
        vecVisited[0][0] = 1;
        while(true){
            vecVisited[_curPos.first][_curPos.second] += 1;
            if (_curPos.first==n-1 && _curPos.second==m-1){ break; }
            auto _nxtPos = IsValid(_curPos, _prevPos);
            _prevPos    = _curPos;
            _curPos     = _nxtPos;
        }
        
        for(int i=0; i<n; i++) for(int j=0; j<m; j++){
            if (grid[i][j]>0) {
                if (grid[i][j]==3){
                    if(vecVisited[i][j]<2) return false;  
                }
                else{
                    if(vecVisited[i][j]<1) return false;  
                }
            }
        }
        return true;
    };
    
    auto GetTileType = [&](pos _nxtPos, pos _curPos, pos _prevPos){
        auto _dy = _nxtPos.first  - _prevPos.first;
        auto _dx = _nxtPos.second - _prevPos.second;
        if  (abs(_dx)==2) return 1;
        if  (abs(_dy)==2) return 2;
        
        if  (_dx==_dy) {
            if (_curPos.first==max(_nxtPos.first, _prevPos.first))   return 5;
            else                                                        return 7;
        }
        else {
            if (_curPos.first==max(_nxtPos.first, _prevPos.first))   return 4;
            else                                                        return 6;
        }
    };
    
    auto BackTracking = [&](auto&& self, pos _curPos, pos _prevPos)->void{
        if (_curPos.first <0 || _curPos.first >=n  ) return;
        if (_curPos.second<0 || _curPos.second>=m  ) return;
        
        if (grid[_curPos.first][_curPos.second]==0){ //현재 선로가 빈상태
            for(auto [_dx,_dy] : {pos(+1,+0), pos(-1,+0), pos(+0,+1), pos(+0,-1)}) {
                auto _nxtPos = pos(_curPos.first + _dx, _curPos.second + _dy);
                if (_nxtPos==_prevPos)                       continue;
                if (_nxtPos.first <0 || _nxtPos.first >=n  ) continue;
                if (_nxtPos.second<0 || _nxtPos.second>=m  ) continue;
                
                grid[_curPos.first][_curPos.second]=GetTileType(_nxtPos, _curPos, _prevPos);
                self(self, _nxtPos, _curPos);
                grid[_curPos.first][_curPos.second]=0;
            }
        }
        else{ //현재 선로에 무언가 있는 상태
            //장애물이 있는 상황
            if (grid[_curPos.first][_curPos.second]==-1) {
                return;   
            }
            
            auto _nxtPos = IsValid(_curPos, _prevPos);
            if (_nxtPos!=pos(-1,-1)){//기존 노선
                if (_curPos.first==n-1 && _curPos.second==m-1){
                    if (CheckBoard()) answer++;
                    return;
                }
                else{
                    self(self, _nxtPos, _curPos);
                }
            }
            else {
                if (grid[_curPos.first][_curPos.second]==1) {//십자가 가능
                    grid[_curPos.first][_curPos.second] = 3;
                    self(self, pos(_curPos.first*2 - _prevPos.first, _curPos.second), _curPos);
                    grid[_curPos.first][_curPos.second] = 1;
                }
                else if(grid[_curPos.first][_curPos.second]==2){
                    grid[_curPos.first][_curPos.second] = 3;
                    self(self, pos(_curPos.first, _curPos.second*2 - _prevPos.second), _curPos);
                    grid[_curPos.first][_curPos.second] = 2;
                }
                else{//불가
                    return;   
                }
            }
        }
    };
    
    BackTracking(BackTracking, pos(0,1), pos(0,0));
    
    return answer;
}