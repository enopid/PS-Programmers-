#include <string>
#include <vector>

// 0 : 0   = 1
// 0 : 0 :                               = 1  
// 1 : 1 : 1*1                           = 1  0
// 2 : 2 : 1*2 + 1*1                     = 3  1  (+1)
// 3 : 5 : 1*5 + 1*2 + 3*1               = 10 5  (+4)
// 4 : 0 : 1*0 + 1*5 + 3*2 + 10*1        = 21 21 (+16)
// 5 : 1 : 1*1 + 1*0 + 3*5 + 10*2 + 21*1 = 57 56 (+35)

// DP[n] += DP[n-k] + 6;
// DP[n] += DP[n-k] + 2;
// DP[n] += DP[n-1] + 1;
// DP[n] += DP[n-3] + 2; 
// 2. 
// DP[n] = 
// DP[n-1]*1 +
// DP[n-3]*1 +
// for() DP[n-(3*i+4)]*2 +
// for() DP[n-(3*i+3)]*4 +
// for() DP[n-(3*i+2)]*2 +

using namespace std;

int solution(int n) {
    int answer = 0;
    const long long IDIVISOR =  1'000'000'007;
    vector<long long> vecDP (max(n+1, 4), 0);
    vector<long long> vecAcc(max(n+1, 4), 0);
    vecDP [0] = 1;
    vecDP [1] = 1;
    vecDP [2] = 3;
    vecDP [3] = 10;
    vecAcc[0] = 1;
    vecAcc[1] = 1;
    vecAcc[2] = 3;
    vecAcc[3] = 11;
    for(int i=4; i<n+1; i++){
        vecDP[i]+=vecDP[i-1];
        vecDP[i]+=vecDP[i-3];
        
        vecDP[i]+=vecAcc[i-4]*2LL;
        vecDP[i]+=vecAcc[i-3]*4LL;
        vecDP[i]+=vecAcc[i-2]*2LL;
        
        vecDP[i]%=IDIVISOR;
        
        vecAcc[i] = vecAcc[i-3] + vecDP[i];
        vecAcc[i] %= IDIVISOR;
    }
    
    
    return vecDP[n];
}