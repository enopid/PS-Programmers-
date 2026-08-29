#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> solution(vector<vector<int>> dice) {
    
    int iNumWin = -1;
    vector<int> answer;
    int n = dice.size();
    
    vector<int> vecChosen;
    
    auto Check = [&](){
        vector<int> vecCaseA, vecCaseB;
        vecCaseA.push_back(0);
        vecCaseB.push_back(0);
        
        for(int i=0; i<n; i++){
            bool bIsPossible = false;
            for(int s : vecChosen) if (s==i) bIsPossible = true;
            if (bIsPossible) continue;
            
            vector<int> ref = vecCaseA;
            vecCaseA.clear();
            for(auto v0 : dice[i]) for(auto v1 : ref){
                vecCaseA.push_back(v0+v1);
            }
        }
        
        for(int i=0; i<n; i++){
            bool bIsPossible = true;
            for(int s : vecChosen) if (s==i) bIsPossible = false;
            if (bIsPossible) continue;
            
            vector<int> ref = vecCaseB;
            vecCaseB.clear();
            for(auto v0 : dice[i]) for(auto v1 : ref){
                vecCaseB.push_back(v0+v1);
            }
        }
        
        sort(vecCaseA.begin(), vecCaseA.end());
        sort(vecCaseB.begin(), vecCaseB.end());
        
        int iTemp = 0;
        int iIdx = 0;
        for(auto s : vecCaseB){
            while(iIdx<vecCaseA.size() && s>vecCaseA[iIdx]){
                iIdx++;
            }
            iTemp+=iIdx;
        }
        
        if (iNumWin<iTemp){
            iNumWin = iTemp;
            answer  = vecChosen;
        }
    };
    
    auto BT = [&](auto&& self)->void{
        if (vecChosen.size()==n/2){
            Check();
            return;
        }
        
        int iSrt = 0;
        if (vecChosen.size()) iSrt = vecChosen.back()+1;
        for(int i=iSrt; i<n; i++){
            vecChosen.push_back(i);
            self(self);
            vecChosen.pop_back();
        }
    };
    BT(BT);
    
    for(auto& s: answer) s++;
    return answer;
}