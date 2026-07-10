#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;


int solution(int n, int start, int end, vector<vector<int>> roads, vector<int> traps) {
    int answer = 0;
    
    int iNumEdge    = roads.size();
    int tableEdges[1001][1001];
    vector<vector<int>> vecEdges(n+1, vector<int>());
    for(int i=0; i<1001; i++)for(int j=0; j<1001; j++){
        tableEdges[i][j]=3001;
    }
    for(auto edge : roads){
        tableEdges[edge[0]][edge[1]]=min(edge[2], tableEdges[edge[0]][edge[1]]);
        vecEdges[edge[0]].push_back(edge[1]);
        vecEdges[edge[1]].push_back(edge[0]);
    }
    auto CheckTrap = [&](int i)->int{
        for(int iTrapIdx = 0; iTrapIdx<traps.size(); iTrapIdx++){
            if (traps[iTrapIdx]==i){
                return iTrapIdx;
            }
        }
        return -1;
    };
    auto CheckFlip = [&](int iMask, int i, int j)->int{
        bool bFlip = false;
        int iTrapIdx0 = CheckTrap(i);
        int iTrapIdx1 = CheckTrap(j);
        if (iTrapIdx0!=-1){
            if (iMask & (1<<iTrapIdx0)) bFlip^=true;
        }
        if (iTrapIdx1!=-1){
            if (iMask & (1<<iTrapIdx1)) bFlip^=true;
        }
        return bFlip;
    };
    
    vector<vector<long long>> vecMinCost(1<<11, vector<long long>(n+1, -1));
    
    priority_queue<
        pair<long long, pair<int, int>>,
        vector<pair<long long, pair<int, int>>>,
        greater<pair<long long, pair<int, int>>>
    > pq; // (cost, (mask, node))
    
    pq.push(pair<long long, pair<int, int>>(0, {0, start}));
    while(pq.size()){
        auto [_cost, _info] = pq.top();
        auto [_mask, _node] = _info;
        pq.pop();
        
        if (_node==end){
            answer = _cost;
            break;
        }
        
        int iTrapIdx = CheckTrap(_node);
        if (iTrapIdx!=-1)
            _mask^=(1<<iTrapIdx);
        if (vecMinCost[_mask][_node]!=-1)
            continue;
        
        //cout << _node << " " << _cost << " " << _mask << endl;
        
        vecMinCost[_mask][_node] = _cost;
        pair<long long, pair<int, int>> _tmp;
        _tmp.second = {_mask, -1};
        for(auto neighbour : vecEdges[_node]){
            bool bFlip = CheckFlip(_mask, _node, neighbour);
            _tmp.second.second = neighbour;
            long long iCost;
            if (bFlip){
                iCost = tableEdges[neighbour][_node];
            }
            else{
                iCost = tableEdges[_node][neighbour];
            }
            if (iCost>=3001LL){
                continue;
            }
            _tmp.first = _cost+iCost;
            pq.push(_tmp);
        }
    }
    
    return answer;
}