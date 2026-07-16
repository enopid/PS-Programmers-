#include <string>
#include <vector>
#include <bitset>
#include <iostream>

// 기본적으로 1개 변형시는 
// 내부비트에서 0인 가장 적은 비트변환
// 이때는 항상 원본보다 큼이보장


// 기본적으로 2개 변형시는 
// 내부 비트중 2개 바꿔야 하는데
// 커야하므로 0 변경이 먼저 그다음 1변경
// 이때 0은 가장처음 나오는 0이며 1은 그다음

// 0 2개 변경은 무의미
// - 어차피하나만하는게 더 최소
// 1 2개 변경은 무의미
// - 오히려 작아짐

using namespace std;

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    
    for(auto num : numbers){
        int idx0 = 0;
        bitset<64> bitNum(num);
        while(idx0<=64){
            if (bitNum[idx0]==0){
                break;
            }
            idx0++;
        }
        bitNum[idx0] = 1;
        
        int idx1 = -1;
        for(int i=0; i<64  && idx0>i; i++){
            if (bitNum[i]==1){
                idx1 = i;
            }
            
        }
        if (idx1!=-1 && idx0>idx1){
            bitNum[idx1] = 0;
        }
        answer.push_back(bitNum.to_ullong());
        
        //cout <<bitNum<<endl;
        //cout <<idx0<<" "<<idx1<<endl;
    }
    
    
    return answer;
}