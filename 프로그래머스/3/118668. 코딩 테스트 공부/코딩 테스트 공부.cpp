#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

using state = pair<int,int>;

int solution(int alp, int cop, vector<vector<int>> problems) {
    int answer = 0;
    bool arrVisited[151][151] = {};
    problems.push_back({0,0,1,0,1});
    problems.push_back({0,0,0,1,1});
    priority_queue<pair<int, state>, vector<pair<int, state>>, greater<pair<int, state>>> pq;
    pq.push({0, state(alp,cop)});
    int iMaxAlg = 0;
    int iMaxCod = 0;
    for(auto _problem : problems){
        iMaxAlg = max(iMaxAlg, _problem[0]);
        iMaxCod = max(iMaxCod, _problem[1]);
    }
    
    while(pq.size()){
        auto [_cost, _state] = pq.top();
        pq.pop();
        if (arrVisited[_state.first][_state.second]) continue;
        arrVisited[_state.first][_state.second]  =true;
        
        if (_state.first >=iMaxAlg && _state.second >= iMaxCod) {
            answer = _cost;
            break;
        }
        
        auto _nxtState  = _state;
        auto _nxtCost   = _cost;
        for(const auto& _problem : problems){
            if (_state.first < _problem[0] || _state.second < _problem[1]) continue;
            _nxtState           = _state;
            _nxtCost            = _cost + _problem[4];
            _nxtState.first     +=_problem[2];
            _nxtState.second    +=_problem[3];
            _nxtState.first     = min(_nxtState.first,  150);
            _nxtState.second    = min(_nxtState.second, 150);
            if (arrVisited[_nxtState.first][_nxtState.second]) continue;
            pq.push({_nxtCost, _nxtState});
        }
    }
    return answer;
}