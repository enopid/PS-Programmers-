#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(int n, vector<vector<int>> data) {
    int answer = 0;
    sort(data.begin(), data.end(), [&](const vector<int>& i, const vector<int>& j){return i[0]<j[0];});
    int N, M;
    int iID;
    int iPrevValue;
    
    //좌표압축
    iID = 0;
    iPrevValue = data[0][0];
    for(auto& _data : data){
        if (iPrevValue!=_data[0]) iID++;
        iPrevValue = _data[0];
        _data[0]=iID;
    }
    N = iID+1;
    sort(data.begin(), data.end(), [&](const vector<int>& i, const vector<int>& j){return i[1]<j[1];});
    iID = 0;
    iPrevValue = data[0][1];
    for(auto& _data : data){
        if (iPrevValue!=_data[1]) iID++;
        iPrevValue = _data[1];
        _data[1]=iID;
    }
    M = iID+1;
    
    //누적합
    vector<vector<int>> vecTable(N, vector<int>(M,0));
    for(auto& _data : data)
        vecTable[_data[0]][_data[1]]=1;
    for(int i=0; i<N; i++) for(int j=1; j<M; j++)
        vecTable[i][j] += vecTable[i][j-1];
    for(int i=1; i<N; i++) for(int j=0; j<M; j++)
        vecTable[i][j] += vecTable[i-1][j];
    
    for(int i=0; i<n; i++) for(int j=i+1; j<n; j++){
        int iMaxX = max(data[i][0], data[j][0]);
        int iMinX = min(data[i][0], data[j][0]);
        int iMaxY = max(data[i][1], data[j][1]);
        int iMinY = min(data[i][1], data[j][1]);
        
        if (iMaxX==iMinX || iMaxY==iMinY) continue;
        
        int iValue = 0;
        iValue += vecTable[iMaxX-1][iMaxY-1];
        iValue -= vecTable[iMaxX-1][iMinY];
        iValue -= vecTable[iMinX][iMaxY-1];
        iValue += vecTable[iMinX][iMinY];
        if (iValue==0) answer++;
    }
    
    return answer;
}