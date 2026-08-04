#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer = {n+1,10'000'001};
    
    vector<int>     vecMask(n+1, 0);
    vector<bool>    vecVisited(n+1, false);
    vector<vector<pair<int,int>>> vecNeighbours(n+1, vector<pair<int,int>>());
    
    for(const auto& path : paths){
        vecNeighbours[path[0]].push_back({path[1], path[2]});
        vecNeighbours[path[1]].push_back({path[0], path[2]});
    }
    for(const auto& gate   : gates  ) vecMask[gate]     = 1;
    for(const auto& summit : summits) vecMask[summit]   = 2;
    
    auto DFS = [&](int i, int iMaxCost)->int{
        int ans = n+1;
        stack<int> st;
        st.push(i);
        while(st.size()){
            auto curNode = st.top();
            st.pop();
            if (vecVisited[curNode]) continue;
            vecVisited[curNode] = true;
            if (vecMask[curNode]==2) {
                ans = min(ans, curNode);
                continue;
            }
            
            for(auto [_iNeighbourNode, _iCost] : vecNeighbours[curNode]){
                if (vecVisited[_iNeighbourNode]) continue;
                if (_iCost>iMaxCost)             continue;
                st.push(_iNeighbourNode);
            }
        }
        
        return ans;
    };
    
    auto CheckPossible = [&](int iMaxCost)->int{
        for(int i=1; i<=n; i++) vecVisited[i] = false;
        int ans = n+1;
        for(auto gate   : gates  ){
            if (vecVisited[gate]) continue;
            ans = min(ans, DFS(gate, iMaxCost));
        }
        return ans;
    };
    
    int lv = 0;
    int rv = 10'000'001;
    
    while(lv < rv){
        int mid = (lv+rv)/2;
        auto _value = CheckPossible(mid);
        if (_value == n+1){//imp
            lv = mid+1;
        }
        else {
            rv = mid; 
        }
    }
    answer[1] = (lv+rv)/2;
    answer[0] = CheckPossible(answer[1]);
    
    return answer;
}