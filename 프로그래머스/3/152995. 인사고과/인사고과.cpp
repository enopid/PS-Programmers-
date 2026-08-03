#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> scores) {
    int answer = 1;
    int n = scores.size();
    vector<int> vecIndices(n);
    iota(vecIndices.begin(), vecIndices.end(), 0);
    sort(vecIndices.begin(), vecIndices.end(), 
         [&](const int& i, const int& j){
             if (scores[i][0]==scores[j][0])
                 return scores[i][1]>scores[j][1];
             return scores[i][0]<scores[j][0];
         }
    );
    
    multiset<pair<int,int>> setNumbers;
    vector<int> vecNonIncentive(n, false);
    
    for(auto idx : vecIndices){
        setNumbers.insert({scores[idx][1], scores[idx][0]});
    }
    for(auto idx : vecIndices){
        auto _value = *setNumbers.rbegin();
        if (_value.first>scores[idx][1] && _value.second > scores[idx][0]) vecNonIncentive[idx] = true;
        
        auto it = setNumbers.find({scores[idx][1], scores[idx][0]});
        if (it!=setNumbers.end()) setNumbers.erase(it);
    }
    
    for(int i=0; i<n; i++) cout << vecNonIncentive[i];
    
    if (vecNonIncentive[0]){
        answer = -1;
    }
    else{
        for(int i=0; i<n; i++){
            if (vecNonIncentive[i]) continue;
            if (scores[0][0]+scores[0][1] < scores[i][0]+scores[i][1]) answer++;
        }
    }
        
    
    return answer;
}