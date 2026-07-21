#include <string>
#include <vector>
#include <map>
#include <iostream>



using namespace std;

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    
    map<long long, bool> mapFlags;
    for(auto num : room_number){
        long long iNum = -1;
        auto it0 = mapFlags.lower_bound(num);
        
        if (it0 == mapFlags.end()){
            iNum = num;
        }
        else if((*mapFlags.begin()).first>num){
            iNum = num;
        }
        else {
            if ((*it0).second){
                if((*it0).first==num)
                    iNum = (*next(it0)).first;
                else
                    iNum = num;
            }
            else{
                iNum = (*it0).first;
            }
        }
        
        auto it1 = mapFlags.find(iNum);
        auto it2 = mapFlags.find(iNum+1);
        
        if      (it1==mapFlags.end() && it2==mapFlags.end()){
            mapFlags[iNum]      = true;
            mapFlags[iNum+1]    = false;
        }
        else if (it1!=mapFlags.end() && it2==mapFlags.end()){
            mapFlags.erase(it1);
            mapFlags[iNum+1]    = false;
        }
        else if (it1==mapFlags.end() && it2!=mapFlags.end()){
            mapFlags.erase(it2);
            mapFlags[iNum]    = true;
        }
        else{
            mapFlags.erase(it1);
            mapFlags.erase(it2);
        }
        
        //cout << iNum << " : ";
        //for(auto [_num, _flag] : mapFlags) cout << "( "<< _num << " " << _flag << " ) ";
        //cout << endl;
        
        answer.push_back(iNum);
    }
    
    return answer;
}