#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

//2^15 = 32,000
//8 * 32,000 * (15*2)

using namespace std;

int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = -1;
    int iNumWP      = weak.size();
    int iNumDists   = dist.size();
    sort(dist.begin(), dist.end());
    reverse(dist.begin(), dist.end());
    
    auto CheckCWDist = [&](int i, int j)->int{
        int iDist = weak[j]-weak[i]; 
        if (iDist<0) iDist+=n;
        return iDist;
    };
    auto CheckCCWDist = [&](int i, int j)->int{
        int iDist = weak[i]-weak[j]; 
        if (iDist<0) iDist+=n;
        return iDist;
    };
    
    auto GetCWMask = [&](int iDist, int iWPIdx)->int{
        int iMask = 0;
        int iCurIdx = iWPIdx;
        while(CheckCWDist(iWPIdx, iCurIdx) <=iDist && iMask<((1<<iNumWP) -1)){
            iMask |= (1<<iCurIdx);
            iCurIdx+=1;
            iCurIdx%=iNumWP;
        }
        return iMask;
    };
    
    auto GetCCWMask = [&](int iDist, int iWPIdx)->int{
        int iMask = 0;
        int iCurIdx = iWPIdx;
        while(CheckCCWDist(iWPIdx, iCurIdx) <=iDist && iMask<((1<<iNumWP) -1)){
            iMask |= (1<<iCurIdx);
            iCurIdx+=iNumWP-1;
            iCurIdx%=iNumWP;
        }
        return iMask;
    };
    
    vector<vector<bool>> vecDP(iNumDists+1, vector<bool>(1<<iNumWP, false));
    vecDP[0][0] = true;
    for(int i=0; i<iNumDists; i++){
        int iDist = dist[i];
        for(int j=0; j<(1<<iNumWP); j++){
            if (!vecDP[i][j]) continue;
            for(int k=0; k<iNumWP; k++){
                for(int iMask : {GetCWMask(iDist, k), GetCCWMask(iDist, k)}){
                    vecDP[i+1][j|iMask] = true;
                    if((j|iMask) == (1<<iNumWP)-1){
                        answer = i+1;
                        return answer;
                    }
                }
            }
        }
    }
    
    
    return answer;
}