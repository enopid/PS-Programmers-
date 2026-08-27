#include <string>
#include <vector>

using namespace std;

int solution(int coin, vector<int> cards) {
    int answer = 1;
    int n = cards.size();
    int m = n/2+1;
    vector<int> vecCost (m, 0);
    vector<int> vecCount(m, 0);
    int arrCounts[3] ={0,0,0};
    auto GetNum = [=](int i)->int{
        if (i>=m)   return n+1-i;
        else        return i;
    };
    for(int i=0; i<n/3; i++){
        int idx = GetNum(cards[i]);
        vecCount[idx]++;
        if (vecCount[idx] == 2)
            arrCounts[vecCost[idx]]++;
    }
    for(int i=n/3; i<n; i+=2){
        int idx;
        idx = GetNum(cards[i]);
        vecCount[idx]++;
        vecCost[idx]++;
        if (vecCount[idx] == 2)
            arrCounts[vecCost[idx]]++;
        
        idx = GetNum(cards[i+1]);
        vecCount[idx]++;
        vecCost[idx]++;
        if (vecCount[idx] == 2)
            arrCounts[vecCost[idx]]++;
        
        ///////////////////////////
        
        bool bIsPossible = false;
        for(int j=0; j<3 && !bIsPossible; j++){
            if (arrCounts[j]>0 && coin>=j){
                arrCounts[j]--;
                coin-=j;
                bIsPossible = true;
            }
        }
        if (!bIsPossible) break;
        answer++;
    }
    
    
    return answer;
}