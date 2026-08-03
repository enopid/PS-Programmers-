#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(int e, vector<int> starts) {
    vector<int> answer;
    vector<long long> vecNum(e+1, 0);
    for(int i=1; i<=e; i++){
        for(int j=1; i*j<=e; j++){
            vecNum[i*j]++;
        }
    }
    vector<int> vecMinNum(e+1, -1);
    vecMinNum[e]=e;
    long long iCurMaxCnt = vecNum[e];
    for(int i=e-1; i>0; i--){
        if (iCurMaxCnt<=vecNum[i]){
            vecMinNum[i] = i;
            iCurMaxCnt = vecNum[i];
        }
        else{
            vecMinNum[i] = vecMinNum[i+1];
        }
    }
    
    for(int i=0; i<starts.size(); i++){
        answer.push_back(vecMinNum[starts[i]]);
    }
    
    
    return answer;
}