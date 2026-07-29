#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

// 이진트리가 보장
// 고정개수의 그룹분할
// 가장큰 그룹의 수의 최소화
// 강하게나는 이분탐색 향기
// 만약 최대 그룹 인원의 개수를 고정하고 그게 가능한 분할 방법으로 생각하면
// 강하게나는 그리디의 향기
//
// 단일노드에대한고려
// 1. 둘 다 커버가능
// 2. 왼쪽까지는 커버가능
// 3. 오른쪽까지는 커버가능
// 4. 나혼자만됨 ㅠㅠ
// 
// 다음 우선순위
// 1. 둘 다 포함
// 2. 한쪽만 커버되는 경우 더 작은 쪽을 커버
// 3. 누구도 안되는경우 둘다 쳐내기

using namespace std;

int solution(int k, vector<int> num, vector<vector<int>> links) {
    int answer = 0;
    int n =  num.size();
    
    vector<int> vecVisited(n, -1);
    int iDivCnt = 0;
    
    int iMinV = *max_element(num.begin(), num.end());
    int iMaxV = accumulate(num.begin(), num.end(), 0);
    int iMidV;
    int iRootIdx = -1;
    vector<bool> vecIsRoot(num.size(), true);
    
    for(auto children : links){
        if (children[0]!=-1) vecIsRoot[children[0]] = false;
        if (children[1]!=-1) vecIsRoot[children[1]] = false;
    }  
    for(int i=0; i<num.size(); i++) {
        if (vecIsRoot[i]){
            iRootIdx = i;
            break;
        }
    }
    
    auto dfs = [&](auto&& self, int i)->int{
        if (vecVisited[i]==-1){
            int iNodeV = num[i];
            int iChildV_L = 0;
            int iChildV_R = 0;
            
            if (links[i][0]!=-1) iChildV_L = self(self, links[i][0]);
            if (links[i][1]!=-1) iChildV_R = self(self, links[i][1]);
            
            
            if      (iNodeV + iChildV_L + iChildV_R <=iMidV){
                vecVisited[i] = iNodeV + iChildV_L + iChildV_R;
            }
            else if (iNodeV + min(iChildV_L, iChildV_R) <=iMidV){
                vecVisited[i] = iNodeV + min(iChildV_L, iChildV_R);
                iDivCnt+=1;
            }
            else    {
                vecVisited[i] = iNodeV;
                iDivCnt+=2;
            }
        }
        return vecVisited[i];
    };
    
    while(iMinV < iMaxV){
        iMidV = (iMinV + iMaxV) / 2;
        
        vecVisited =  vector<int>(n, -1);
        iDivCnt = 0;
        
        dfs(dfs, iRootIdx);
        if (iDivCnt<=k-1) //can divide
            iMaxV = iMidV;
        else
            iMinV = iMidV+1;
    }
    answer = (iMinV + iMaxV) / 2;
    return answer;
}