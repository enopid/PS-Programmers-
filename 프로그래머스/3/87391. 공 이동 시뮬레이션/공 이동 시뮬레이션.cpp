#include <string>
#include <vector>
#include <iostream>

// 행과 열은 독립적으로 처리가능
// 아마 특정 연속적인 구간에서 가능
// 아 깨달음
// 이동이 먹히는 가용 범위가 존재하고 밖에서는 클림핑 되는 느낌

using namespace std;

long long solution(int n, int m, int x, int y, vector<vector<int>> queries) {
    long long answer = 0;
    
    
    long long d[4] = {0,0,0,0};
    long long dx = 0; //행
    long long dy = 0; //열
    for(auto _query : queries){
        int _dv = _query[1];
        
        if      (_query[0]==0){
            dy-=_dv;
            d[0] = min(dy, d[0]);
        }
        else if (_query[0]==1){
            dy+=_dv;
            d[1] = max(dy, d[1]);
        }
        else if (_query[0]==2){
            dx-=_dv;
            d[2] = min(dx, d[2]);
        }
        else if (_query[0]==3){
            dx+=_dv;
            d[3] = max(dx, d[3]);
        }
    }
    cout << dy << " " << dx << '\n';
    for(int i=0; i<4; i++) cout << d[i] << " ";
    cout << '\n';
    
    //열 행
    auto GetPos = [&](int _srtX, int _srtY)->pair<int,int>{
        pair<int,int> pos = {_srtX, _srtY};
        //cout << "Srt\n";
        //cout << m << 'x' << n << ':' << pos.first << " " << pos.second << '\n';
        for(const auto& _query : queries){
            int _dv = _query[1];

            if      (_query[0]==0){
                pos.first-=_dv;
                pos.first = max(pos.first, 0);
            }
            else if (_query[0]==1){
                pos.first+=_dv;
                pos.first = min(pos.first, m-1);
            }
            else if (_query[0]==2){
                pos.second-=_dv;
                pos.second = max(pos.second, 0);
            }
            else if (_query[0]==3){
                pos.second+=_dv;
                pos.second = min(pos.second, n-1);
            }
            //cout << m << 'x' << n << ':' << pos.first << " " << pos.second << '\n';
        }
        //cout << "End\n";
        return pos;
    };
    
    long long _sx = 0;
    long long _sy = 0;
    // 두개의 기존점 존재, 양 기존점기준으로확장
    if (d[1]-d[0]+1 >= m){// 항상 동일한 지점
        if (GetPos(0,0).first==y) _sx = m;
    }
    else{
        long long idx0 = -d[0];
        long long idx1 = m-1-d[1];
        long long lv = GetPos(idx0,0).first;
        long long rv = GetPos(idx1,0).first;
        cout << GetPos(idx1,0).first << " " << GetPos(idx1,0).second << '\n';
        if (lv == y){
            _sx += idx0+1;
        }
        if (rv == y){
            _sx += m - idx1;
        }
        if (lv < y && y < rv){
            _sx = 1;
        }
        cout << idx0 << " " << idx1 << " " << lv << " " << rv << '\n';
    }
    
    if (d[3]-d[2]+1 >= n){// 항상 동일
        if (GetPos(0,0).second==x) _sy = n;
    }
    else{
        long long idx0 = -d[2];
        long long idx1 = n-1-d[3];
        long long lv = GetPos(0,idx0).second;
        long long rv = GetPos(0,idx1).second;
        if (lv == x){
            _sy += idx0+1;
        }
        if (rv == x){
            _sy += n - idx1;
        }
        if (lv < x && x < rv){
            _sy = 1;
        }
        cout << idx0 << " " << idx1 << " " << lv << " " << rv << '\n';
    }
    cout << _sx << " " << _sy << '\n';
    answer = _sx*_sy;
    
    return answer;
}