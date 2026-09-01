#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

//각유형별로 독립적
//멘토 종류가 정해지면 시간은 결정적
//16C5=4368
//300
//n:20
//k:5
//s:300

using namespace std;

int solution(int k, int n, vector<vector<int>> reqs) {
    int answer = 300*300*100+1;
    vector<int> vecCount;
    
    auto check = [&](){
        int iResult=0;
        int arrEndTime[6] = {0,0,0,0,0,0};
        vector<vector<int>> vecMentos(k+1, vector<int>());
        for(int i=0; i<k; i++) vecMentos[i+1].resize(vecCount[i], 0);
        
        for(const auto& _req : reqs){
            int iSrtTime = max(vecMentos[_req[2]][0], _req[0]);
            iResult+=iSrtTime-_req[0];
            vecMentos[_req[2]][0] = iSrtTime + _req[1];
            sort(vecMentos[_req[2]].begin(), vecMentos[_req[2]].end());
        }
        answer = min(answer, iResult);
    };
    
    auto BT = [&](auto&& self){
        if (vecCount.size()==k){
            if (accumulate(vecCount.begin(), vecCount.end(),0)!=n) return;
            //check
            check();
            //check done
            return;
        }
        int iMaxCnt = n - accumulate(vecCount.begin(), vecCount.end(),0) - (k-vecCount.size()-1);
        for(int i=1; i<=iMaxCnt; i++){
            vecCount.push_back(i);
            self(self);
            vecCount.pop_back();
        }
    };
    BT(BT);
    return answer;
}