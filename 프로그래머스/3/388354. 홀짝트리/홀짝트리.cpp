#include <string>
#include <vector>
#include <map>
#include <stack>

//1. 엣지 처리
//2. 트리의 분리
//3. 홀짝 판단
//어떤 노드는 번호와 연결 수로
//번호는 짝수판단, 연결수도 짝수판단
// (짝,짝) (홀,홀) -> type0
// 루트시 홀짝   / 미루트시 역홀짝
// (홀,짝) (짝,홀) -> type1
// 루트시 역홀짝 / 미루트시 홀짝
// 
// 역홀짝 트리조건  
// type1 단일 and 나머지는 type0
// 홀짝 트리 조건
// type0 단일 and 나머지는 type1
//
//

using namespace std;

vector<int> solution(vector<int> nodes, vector<vector<int>> edges) {
    vector<int>             answer;
    answer.push_back(0);
    answer.push_back(0);
    
    int n       = nodes.size();
    vector<bool>        vecVisited  (n, false);
    vector<int>         vecNodeType(n, 0);
    map<int, int>       mapId2Idx;
    for(int i =0; i<n; i++) mapId2Idx[nodes[i]]=i;
    vector<vector<int>> vecNeighbourIndices(n, vector<int>());
    
    for(auto _edge : edges){
        auto idx0 = mapId2Idx[_edge[0]];
        auto idx1 = mapId2Idx[_edge[1]];
        vecNeighbourIndices[idx0].push_back(idx1);
        vecNeighbourIndices[idx1].push_back(idx0);
    }
    for(int i =0; i<n; i++){
        if ((nodes[i]%2) == (vecNeighbourIndices[i].size()%2))
            vecNodeType[i] = 0;
        else
            vecNodeType[i] = 1;
    }
    
    vector<vector<int>>   vecTreeInfo;
    
    for(int i =0; i<n; i++){
        if (vecVisited[i]) continue;
        
        vecTreeInfo.push_back(vector<int>(2,0));
        
        stack<int> st;
        st.push(i);
        vecVisited[i] = true;
        while(st.size()){
            int iCurIdx = st.top();
            st.pop();
            vecTreeInfo.back()[vecNodeType[iCurIdx]]++;
            for(int idx : vecNeighbourIndices[iCurIdx]){
                if (vecVisited[idx]) continue;
                vecVisited[idx] = true;
                st.push(idx);
            }
        }
    }
    
    for(auto _treeInfo : vecTreeInfo){
        if (_treeInfo[0] == 1) answer[0]++;
        if (_treeInfo[1] == 1) answer[1]++;
    }
    
    return answer;
}