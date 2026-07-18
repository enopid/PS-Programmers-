#include <string>
#include <vector>
#include <list>
#include <bitset>
#include <iostream>

using namespace std;

struct FBoard{
    FBoard(){}
    FBoard(const vector<vector<int>>& key, int iRot = 0){
        for(int i=0; i<40; i++)
            bitMask.push_back(bitset<40>(0));
        
        N = key.size();
        auto it = bitMask.begin();
        for(int i=0; i<N; i++) for(int j=0; j<N; j++){
            if (key[i][j]){
                if      (iRot == 0)
                    (*next(it,i))[j]       = 1;
                else if (iRot == 1)
                    (*next(it,N-1 - j))[i] = 1;
                else if (iRot == 2)
                    (*next(it,N-1 - i))[N-1 - j] = 1;
                else if (iRot == 3)
                    (*next(it,j))[N-1-i]   = 1;
            }
        }
    }
    
    void Shift(int i, int j){
        if (i>0)
            for(auto& _bitset : bitMask) _bitset>>=i;
        else
            for(auto& _bitset : bitMask) _bitset<<=abs(i);
        
        if (j>0)
            while(j--) bitMask.splice(bitMask.end(), bitMask, bitMask.begin());
        else
            while(j++) bitMask.splice(bitMask.begin(), bitMask, prev(bitMask.end()));
    }
    
    bool Check(const FBoard& key){
        bool bIsPossible =true;
        auto it0 = key.bitMask.begin();
        auto it1 = bitMask.begin();
        for(int _=0; _<N; _++,it0++,it1++) for(int i=0; i<N; i++){
            if ((*it0)[i]==(*it1)[i]) bIsPossible = false;
        }
        return bIsPossible;
    }
    
    list<bitset<40>> bitMask;
    int N = 0;
};

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = false;
    FBoard Keys[4];
    for(auto i =0; i<4; i++) Keys[i] = FBoard(key, i);
    FBoard lockBoard = FBoard(lock);
    
    int N = lock.size();
    for(auto i = -N; i<=N; i++) for(auto j = -N; j<=N; j++) for(auto k =0; k<4; k++){
        auto _tmp = Keys[k];
        _tmp.Shift(i,j);
        if (lockBoard.Check(_tmp)) answer = true;
    }
    
    return answer;
}