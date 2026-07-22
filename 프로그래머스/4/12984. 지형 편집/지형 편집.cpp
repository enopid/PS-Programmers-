#include<vector>
#include<iostream>
using namespace std;

long long solution(vector<vector<int> > land, int P, int Q) {
    long long answer = -1;
    int n = land.size();
    auto GetIncline = [&](long long iHeight){
        long long iIncline = 0;
        for(int i=0; i<n; i++) for(int j=0; j<n; j++){
            long long iDist = land[i][j]-iHeight;
            if (iDist > 0)
                iIncline -= Q;
            if (iDist < 0)
                iIncline += P;
        }
        return iIncline;
    };
    
    long long l=1'000'000'000LL;
    long long r=0LL;
    for(int i=0; i<n; i++) for(int j=0; j<n; j++){
        l = min((long long)land[i][j], l);
        r = max((long long)land[i][j], r);
    }
    //cout << l << " " << r << endl;
    while(l<r){
        auto mid = (l+r)/2LL;
        if (mid==l) break;
        auto iIncline = GetIncline(mid);
        if      (iIncline<=0){
            l = mid;
        }
        else if (iIncline>0){
            r = mid;
        }
    }
    //cout << l << " " << r << endl;
    
    
    auto GetCost = [&](long long iHeight)->long long{
        long long iCost = 0;
        for(int i=0; i<n; i++) for(int j=0; j<n; j++){
            long long iDist = land[i][j]-iHeight;
            if (iDist > 0)
                iCost += iDist*Q;
            if (iDist < 0)
                iCost -= iDist*P;
        }
        return iCost;
    };
    
    answer = min(GetCost(l), GetCost(r));
    
    return answer;
}