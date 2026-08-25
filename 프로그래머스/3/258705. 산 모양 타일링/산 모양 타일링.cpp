#include <string>
#include <vector>
#include <array>

using namespace std;

const int REMAINDER = 10007;

int solution(int n, vector<int> tops) {
    int answer = 0;
    vector<array<int, 2>> vecDP(n+1, {0,0});
    vecDP[0][0] = vecDP[0][1] = 1;
    for(int i=1; i<n+1; i++){
        vecDP[i][0] = vecDP[i-1][0]*2 + vecDP[i-1][1]*1;
        vecDP[i][1] = vecDP[i-1][0]*1 + vecDP[i-1][1]*1;
        if (tops[i-1]){
            vecDP[i][0] += vecDP[i-1][0];
            vecDP[i][1] += vecDP[i-1][0];
        }
        
        vecDP[i][0]%=REMAINDER;
        vecDP[i][1]%=REMAINDER;
    }
    
    answer = vecDP.back()[0];
    
    return answer;
}