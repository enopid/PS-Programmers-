#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// pq : 2nlogm = 100'000log(10000)
// log(10,000 * 50,000) * 10,000

//
//   6
// 5 6 3
// 4 2 3
// 1 2 3

int solution(int n, vector<int> cores) {
    int answer = 0;
    long long m = cores.size();
    
    long long lv(0), rv(*min_element(cores.begin(), cores.end()) * (long long)n +1LL);
    
    while(lv<rv){
        long long mid = (lv+rv)/2LL;
        
        long long iCnt(0);
        for(long long _value : cores) {
            if ((mid%_value)==0) iCnt+=mid/_value;   
            else                 iCnt+=mid/_value + 1LL;
        }
        //cout << mid << " " << iCnt << endl;
        
        if (iCnt>=n)    rv = mid;
        else            lv = mid+1;
    }
    lv =(lv+rv)/2;
    vector<long long> vecCandidates;
    long long iCnt(0);
    for(long long i=0; i<m; i++) {
        if (((lv-1)%cores[i])==0) {
            vecCandidates.push_back(i);
            iCnt+=(lv-1)/cores[i];   
        }
        else{
            iCnt+=(lv-1)/cores[i] +1;   
        }
    }
    long long idx = n-iCnt-1;
    answer = vecCandidates[idx]+1;
    
    cout << iCnt << " " << idx << " " << lv << endl;
    for(auto _vl : vecCandidates) cout << _vl << " ";
    
        
    return answer;
}
