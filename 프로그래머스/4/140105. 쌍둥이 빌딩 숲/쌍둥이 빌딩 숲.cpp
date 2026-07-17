#include <string>
#include <vector>

//1
//3
//5
//7

using namespace std;

int solution(int n, int count) {
    int answer = 0;
    vector<vector<long long>> vecDP(n, vector<long long>(n+1, 0));
    vecDP[0][1]=1;
    for(int i=1; i<n; i++) for(int j=1; j<=n; j++) {
        vecDP[i][j]   += vecDP[i-1][j] * (2*i);
        vecDP[i][j]   += vecDP[i-1][j-1];
        vecDP[i][j]   %=1000000007;
    }
    answer= vecDP[n-1][count];
    return answer;
}