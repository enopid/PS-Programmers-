#include <string>
#include <vector>
#include <queue>
#include <iostream>


// 1 x x 8 8
// 5 5 3 3 3
// x 6 6 4 4
// 2 2 x x x

// 1 1 3 3 3
// 5 5 3 3 3
// 2 2 6 4 4
// 2 2 x x x


//특정 격자안에 포함된 최소숫자
using namespace std;

vector<int> solution(int m, int n, int h, int w, vector<vector<int>> drops) {
    vector<int> answer;
    answer.push_back(0);
    answer.push_back(0);
    
    const int MAXVALUE = m*n+1;
    vector<vector<int>> vecMinValues(m, vector<int>(n, MAXVALUE));
    vector<vector<int>> vecDropNum  (m, vector<int>(n, MAXVALUE));
    
    int idx = 1;
    for(auto& _drop : drops){
        vecDropNum[_drop[0]][_drop[1]] = idx++;
    }
    
    for(int i=0; i<m; i++) {
        priority_queue<pair<int, int>,vector<pair<int, int>>, greater<pair<int, int>>> _pqWindow;
        for(int j=0; j<w; j++){
            if (vecDropNum[i][j]!=MAXVALUE) _pqWindow.push({vecDropNum[i][j], j});
        }
        for(int j=w; j<=n; j++){
            if (_pqWindow.size()) {
                vecMinValues[i][j-w] = _pqWindow.top().first;   
            }
            while(_pqWindow.size() && _pqWindow.top().second <= j-w) { 
                _pqWindow.pop(); 
            }
            if (j!=n && vecDropNum[i][j]!=MAXVALUE) _pqWindow.push({vecDropNum[i][j], j});
        }   
    }
    
    //for(int i=0; i<m; i++, cout << endl) for(int j=0; j<n; j++) cout << vecMinValues[i][j] << '\t';
    
    for(int j=0; j<n; j++) {
        priority_queue<pair<int, int>,vector<pair<int, int>>, greater<pair<int, int>>> _pqWindow;
        for(int i=0; i<h; i++){
            if (vecMinValues[i][j]!=MAXVALUE) _pqWindow.push({vecMinValues[i][j], i});
        }
        for(int i=h; i<=m; i++){
            if (_pqWindow.size()) {
                vecMinValues[i-h][j] = _pqWindow.top().first;   
            }
            while(_pqWindow.size() && _pqWindow.top().second <= i-h) { 
                _pqWindow.pop(); 
            }
            if (i!=m && vecMinValues[i][j]!=MAXVALUE) _pqWindow.push({vecMinValues[i][j], i});
        }   
    }
    //cout << endl;
    //for(int i=0; i<m; i++, cout << endl) for(int j=0; j<n; j++) cout << vecMinValues[i][j] << '\t';
    
    int iMaxValue =-1;
    for(int i=0; i<=m-h; i++) for(int j=0; j<=n-w; j++) {
        if (iMaxValue<vecMinValues[i][j]){
            iMaxValue = vecMinValues[i][j];
            answer[0]=i;
            answer[1]=j;
        }
    }
    
    return answer;
}