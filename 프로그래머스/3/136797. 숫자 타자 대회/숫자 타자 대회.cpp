#include <string>
#include <vector>

using namespace std;

int solution(string numbers) {
    int answer = 0;
    int n =  numbers.size();
    auto GetVal = [](char word)->int{
        int _value = 0;
        if      (word=='*') _value = 9;
        else if (word=='0') _value = 10;
        else if (word=='#') _value = 11;
        else                _value = word-'1';
        return _value;
    };
    int arrCost[12][12] ={};
    for(int i=0; i<12; i++) for(int j=0; j<12; j++){
        int x0 = i/3;
        int y0 = i%3;
        int x1 = j/3;
        int y1 = j%3;
        
        int dx = abs(x0-x1);
        int dy = abs(y0-y1);
        
        int iDiagonal = min(dy,dx);
        int iStraight = max(dy,dx) - iDiagonal;
        
        arrCost[i][j] = max(iStraight*2 + iDiagonal*3, 1);
    };
    const int MAXVALUE = 100'001*30;
    answer = MAXVALUE;
    int vecDP[100'001][12][12];
    for(int k=0; k<100'001; k++) for(int i=0; i<12; i++) for(int j=0; j<12; j++) vecDP[k][i][j]=MAXVALUE;
    vecDP[0][3][5] = 0;
    vecDP[0][5][3] = 0;
    for(int k=0; k<n; k++) {
        auto _value = GetVal(numbers[k]);
        for(int i=0; i<12; i++) for(int j=0; j<12; j++){
            if (vecDP[k][i][j]==MAXVALUE) continue;

            if (_value!=j)
                vecDP[k+1][_value][j] = min(vecDP[k+1][_value][j], vecDP[k][i][j]+arrCost[_value][i]);
            
            if (_value!=i)
                vecDP[k+1][i][_value] = min(vecDP[k+1][i][_value], vecDP[k][i][j]+arrCost[j][_value]);
        }
    }
    
    for(int i=0; i<12; i++) for(int j=0; j<12; j++) 
        answer = min(answer, vecDP[n][i][j]);
    return answer;
}