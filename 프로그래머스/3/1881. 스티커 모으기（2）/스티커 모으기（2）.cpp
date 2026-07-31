#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> sticker)
{
    int answer =0;
    int n = sticker.size();
    
    vector<int> vecDP_NonIncludeFirst (n, 0);
    vector<int> vecDP_IncludeFirst(n, 0);
    vecDP_NonIncludeFirst [0] = 0;
    vecDP_NonIncludeFirst [1] = sticker[1];
    
    vecDP_IncludeFirst[0] = sticker[0];
    vecDP_IncludeFirst[1] = sticker[0];
    
    for(int i=2; i<n; i++){
        vecDP_NonIncludeFirst[i] = max(
            vecDP_NonIncludeFirst[i-1],
            vecDP_NonIncludeFirst[i-2] + sticker[i]
        );
    }
    
    for(int i=2; i<n-1; i++){
        vecDP_IncludeFirst[i] = max(
            vecDP_IncludeFirst[i-1],
            vecDP_IncludeFirst[i-2] + sticker[i]
        );
    }
    
    answer = max(
    *max_element(vecDP_NonIncludeFirst.begin(), vecDP_NonIncludeFirst.end()),
    *max_element(vecDP_IncludeFirst.begin(),    vecDP_IncludeFirst.end())
    );
    
    return answer;
}