#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

//정렬후
//가장 낮은 수의 친구만큼 남은 값들을 뺌
//해당수를 제거하고 다시반복
//이러다 총합이 k개가 된다면를 초과하면
//그때 순회를 하며 계산

using namespace std;

int solution(vector<int> food_times, long long k) {
    int answer = 0;
    long long n = food_times.size();
    vector<int> vecIndices(n);
    iota(vecIndices.begin(),vecIndices.end(), 0);
    sort(vecIndices.begin(), vecIndices.end(), [&](int i, int j)->bool {return food_times[i] < food_times[j];});
    
    //for(auto v : vecIndices) cout << v << " ";
    
    long long accV  = 0; // 현재까지 누적된 수치
    long long prevV = 0; // 이전 기준이된 수치
    for(long long i=0; i<n; i++){
        auto _value = food_times[vecIndices[i]];
        auto nxtAccV = accV + (_value - prevV) * (n-i);
        if (nxtAccV <= k){ //다음사이클 까지 필요
            accV    = nxtAccV;
            prevV   = _value;
        }
        else{// 여기서 처리가능
            auto iRemainV = (k-accV) % (n-i);
            
            vector<int> vecTmp = vector<int>(vecIndices.begin()+i, vecIndices.end());
            sort(vecTmp.begin(), vecTmp.end());
            return vecTmp[iRemainV]+1;
        }
    }
    answer = -1;
    
    return answer;
}