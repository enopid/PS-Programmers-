#include <string>
#include <vector>
#include <array>
#include <iostream>

#include <unordered_map>
#include <list>
#include <stack>

using namespace std;

template<typename _keyType>
class Topological_Sort{
    struct FNode {
        FNode(_keyType _iKey) : iKey(_iKey) {}
        bool IsEnable(){
            if (iMinIndegree==-1)
                return iIndegree==iOriginalIndegree;
            else
                return iIndegree>=iMinIndegree;
        }
        const _keyType iKey;
        int     iOriginalIndegree   = 0;
        int     iIndegree           = 0;
        int     iMinIndegree        = -1;   
        bool    bActive             = false;
        list<_keyType> lstSuccesors;
    };
public:
    Topological_Sort(){

    }
    ~Topological_Sort(){
        for(auto& [_, _pNode] : setNodes){
            delete _pNode;
        }
        setNodes.clear();
    }
    bool AddNode(_keyType _iKey, int _iMinIndegree = -1){
        if (setNodes.find(_iKey)!=setNodes.end()) 
            return false;
        setNodes[_iKey] = new FNode(_iKey);
        setNodes[_iKey]->iMinIndegree = _iMinIndegree;
        return true;
    }
    bool AddRelation(_keyType _iKey0, _keyType _iKey1){
        auto it0 = setNodes.find(_iKey0);
        auto it1 = setNodes.find(_iKey1);
        if (it0==setNodes.end() || it1==setNodes.end())
            return false; 
        //Check 중복 추가
        it0->second->lstSuccesors.push_back(it1->first);
        it1->second->iOriginalIndegree+=1;
        return true; 
    }
    void Reset(){
        for(auto& [_, _pNode] : setNodes){
            _pNode->iIndegree   = 0;
            _pNode->bActive     = false;
        }
    }
    bool ActiveNode(_keyType _iKey, list<_keyType>& lstEnableKeys){
        auto it = setNodes.find(_iKey);
        if (it==setNodes.end()) return false;
        auto pNode = it->second;
        if (pNode->bActive) return false;
        
        if (pNode->IsEnable()){
            pNode->bActive = true;
            for(auto& _iSuccesorKey : pNode->lstSuccesors){
                auto it = setNodes.find(_iSuccesorKey);
                if (it==setNodes.end()) continue;
                auto pChildNode = it->second;
                pChildNode->iIndegree++;
                if (pChildNode->IsEnable())
                    lstEnableKeys.push_back(_iSuccesorKey);
            }
            
            return true;   
        }
        else{
            return false;
        }
    
    }
    bool CheckEnable(_keyType _iKey){
        auto it = setNodes.find(_iKey);
        if (it==setNodes.end()) return false;
        return it->second->IsEnable();
    }
    void GetEnables(list<int>& lstEnableKeys){
        for(auto& [_key, _pNode] : setNodes){
            if (_pNode->IsEnable())
                lstEnableKeys.push_back(_key);
        }
    }
private:
    unordered_map<_keyType, FNode*> setNodes;
};

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    bool answer = true;
    Topological_Sort<int> TS;
    for(int i=0; i<n; i++) TS.AddNode(i);
    for(auto _order : order) TS.AddRelation(_order[0], _order[1]);
    
    vector<vector<int>> vecNeighbours(n,vector<int>());
    vector<int>         vecVisited(n, false);
    for(auto _path : path) {
        vecNeighbours[_path[0]].push_back(_path[1]);
        vecNeighbours[_path[1]].push_back(_path[0]);
    }
    stack<int> st;
    st.push(0);
    vecVisited[0] = true;
    while(st.size()){
        auto curNode = st.top();
        st.pop();
        for(auto neighbour : vecNeighbours[curNode]){
            if (vecVisited[neighbour]) continue;
            TS.AddRelation(curNode, neighbour);
            st.push(neighbour);
            vecVisited[neighbour] = true;
        }
    }
    list<int> lstEnableKeys;
    
    TS.GetEnables(lstEnableKeys);
    while(lstEnableKeys.size()){
        auto iNode = lstEnableKeys.back();
        lstEnableKeys.pop_back();
        if (TS.ActiveNode(iNode, lstEnableKeys)) n--;
    }
    cout << n;
    answer = n==0;
    
    return answer;
}