#include <iostream>
#include <vector>
using namespace std;

//2억으로 순회불가
//

int solution(int n, vector<int> stations, int w)
{
    int answer = 0;
    
    int iRangeSrt = 0;
    for(auto iStationIdx : stations){
        auto iStationSrt = iStationIdx-1-w-1;
        auto iStationEnd = iStationIdx-1+w+1;
        if (iRangeSrt<=iStationSrt){
            int iRange = iStationSrt-iRangeSrt+1;
            answer += 1;
            answer += (iRange-1) / (2*w+1);
            //cout << iRange << " " << answer << endl;
        }
        iRangeSrt = iStationEnd;
    }
    if (iRangeSrt<=n-1){
        int iRange = n-1-iRangeSrt+1;
        answer += 1;
        answer += (iRange-1) / (2*w+1);
        //cout << iRange << " " << answer << endl;
    }

    return answer;
}