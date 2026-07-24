#include <string>
#include <vector>
#include <array>
#include <iostream>

#include <unordered_map>
#include <list>

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

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
string solution(int m, int n, vector<string> board) {
    string answer = "";
    
    Topological_Sort<int> TS;
    
    array<pair<int,int>, 26> arrPos0;
    array<pair<int,int>, 26> arrPos1;
    arrPos0.fill({-1,-1});
    arrPos1.fill({-1,-1});
    for(int i=0; i<m; i++) for(int j=0; j<n; j++){
        if (board[i][j]>='A' && board[i][j]<='Z'){
            if (arrPos0[board[i][j]-'A'].first == -1)
                arrPos0[board[i][j]-'A'] = {i,j};
            else
                arrPos1[board[i][j]-'A'] = {i,j};
        }
    }
    TS.AddNode(-1);
    int iTotal = 0;
    for(int i=0; i<26; i++){
        if (arrPos0[i].first != -1) {
            TS.AddNode(i, 1);   
            iTotal++;
        }
    }
    int idx = -2;
    for(int i=0; i<26; i++){
        if (arrPos0[i].first != -1) {
            auto idx0 = idx--;
            auto idx1 = idx--;
            
            auto pos0 = arrPos0[i];
            auto pos1 = arrPos1[i];
            auto pos2 = arrPos1[i];
            
            list<int> lstKeys;
            bool      bPossiblePath = true;
            //경로0
            lstKeys.clear();
            bPossiblePath = true;
            pos2 = pos0;
            while(true) {
                if      (pos2.first>pos1.first)
                    pos2.first--;
                else if (pos2.first<pos1.first)
                    pos2.first++;
                else{
                    if      (pos2.second>pos1.second)
                        pos2.second--;
                    else if (pos2.second<pos1.second)
                        pos2.second++;
                    else
                        break;
                }
                if (pos2==pos1) break;
                
                auto _x = pos2.first;
                auto _y = pos2.second;
                if      (board[_x][_y]=='.')    continue;
                else if (board[_x][_y]=='*')    bPossiblePath = false;
                else                            lstKeys.push_back(board[_x][_y]-'A');
            }
            
            TS.AddNode(idx0);
            if (bPossiblePath){
                for(auto _key : lstKeys)
                    TS.AddRelation(_key, idx0);
            }
            else{
                TS.AddRelation(-1, idx0);
            }
            
            //경로1
            lstKeys.clear();
            bPossiblePath = true;
            pos2 = pos0;
            while(true) {
                if      (pos2.second>pos1.second)
                    pos2.second--;
                else if (pos2.second<pos1.second)
                    pos2.second++;
                else{
                    if      (pos2.first>pos1.first)
                        pos2.first--;
                    else if (pos2.first<pos1.first)
                        pos2.first++;
                    else
                        break;
                }
                if (pos2==pos1) break;
                
                auto _x = pos2.first;
                auto _y = pos2.second;
                if      (board[_x][_y]=='.')    continue;
                else if (board[_x][_y]=='*')    bPossiblePath = false;
                else                            lstKeys.push_back(board[_x][_y]-'A');
            }
            
            TS.AddNode(idx1);    
            if (bPossiblePath){
                for(auto _key : lstKeys)
                    TS.AddRelation(_key, idx1);
            }
            else{
                TS.AddRelation(-1, idx1);
            }
            
            TS.AddRelation(idx0, i);
            TS.AddRelation(idx1, i);
        }
    }
    
    list<int> lstEnableKeys;
    TS.GetEnables(lstEnableKeys);
    while(lstEnableKeys.size()){
        int iCurKey = lstEnableKeys.front();
        lstEnableKeys.pop_front();
        if (iCurKey==-1) continue;
        
        if (TS.ActiveNode(iCurKey, lstEnableKeys)){
            lstEnableKeys.sort();
            if (iCurKey>=0 && iCurKey<26){
                answer.push_back(iCurKey+'A');
                iTotal--;
            }
        }
    }
    
    if (iTotal>0)
        answer="IMPOSSIBLE";
    
    //1. 연결 경로 가능 여부체크
    //2. 사이노드 체크
    
    return answer;
}