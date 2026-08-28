#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// a  - z  : 01~26
// aa - az : 27~51

using namespace std;

string solution(long long n, vector<string> bans) {
    string answer = "";
    auto Spell2Num = [](const string& s)->long long{
        long long iResult   = 0LL;
        long long iBase     = 1LL;
        for(int i=s.size()-1; i>=0; i--){
            iResult += iBase*(s[i] - 'a' + 1);
            iBase   *= 26;
        }
        return iResult;
    };
    auto Num2Spell = [](long long i)->string{
        string sResult;
        do{
            sResult=char((i-1)%26+'a') + sResult;
            i=(i-1)/26LL;
        }
        while(i>0);
        
        return sResult;
    };
    
    vector<long long> vecBanNums;
    for(const auto& s : bans){
        vecBanNums.push_back(Spell2Num(s));
    }
    sort(vecBanNums.begin(), vecBanNums.end());
    
    for(auto iNum : vecBanNums){
        if (iNum<=n)
            n++;
        else 
            break;
    }
    
    answer = Num2Spell(n);
    
    
    return answer;
}