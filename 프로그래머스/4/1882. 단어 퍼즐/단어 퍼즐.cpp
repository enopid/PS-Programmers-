#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

int solution(vector<string> strs, string t)
{
    int answer = 0;
    int n = t.size();
    
    set<string> setStrs = set<string>(strs.begin(), strs.end());
    vector<int> vecDP(n+1, n+1);
    vecDP[0] = 0;
    
    for(int i=0; i<n; i++){
        for(int j=1; j<=5 && i+j<n+1; j++){
            if (setStrs.find(t.substr(i,j)) == setStrs.end()) continue;
            vecDP[i+j] = min(vecDP[i]+1, vecDP[i+j]);
        }
    }
    
    answer = vecDP.back();
    if (answer==n+1) answer = -1;
    return answer;
}