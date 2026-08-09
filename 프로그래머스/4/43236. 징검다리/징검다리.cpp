#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// a b / c  d  e
// a / b  c  d  e
// 0 2 11 14 17 21 25
//  2 9  3  3  4  4


using namespace std;

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    sort(rocks.begin(), rocks.end());
    int iPrevV = 0;
    vector<int> vecDists;
    for(int i=0; i<rocks.size(); i++){
        vecDists.push_back(rocks[i] - iPrevV);
        iPrevV = rocks[i];
    }
    vecDists.push_back(distance - iPrevV);
    
    int lv = *min_element(vecDists.begin(), vecDists.end()) -1;
    int rv = distance+1;
    while(lv<rv){
        int mid = (lv+rv)/2;
        
        int iCnt = 0;
        int iSum = 0;
        for(auto _value : vecDists){
            if (iSum+_value >= mid){
                iSum = 0;
            }
            else{
                iSum+=_value;
                iCnt++;
            }
        }
        
        if (iCnt>n) rv = mid;
        else        lv = mid+1;
    }
    
    answer = lv-1;
    
    return answer;
}