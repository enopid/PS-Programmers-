#include <string>
#include <vector>

//dlru 순 (하, 왼, 우, 상)
//완전 아래로 왼쪽으로 최대한가고 그다음에 길찾기
//아니 애초에 하하하하 왼왼왼 + 우우우 상상상
//1. 가능한한 왼쪽아래로
//2. 딱 최단거리일시 우우우 상상상 이런식으로 이동
//3. 거리가 남을시 우우우 상상상 이전에 (이미 왼쪽아래끝 도달) 
//우왼우왼 (오른쪽가능시)
//상하상하 (오른쪽불가능시)
//왼왼왼 우우우로 이동

using namespace std;

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    int ix = x;
    int iy = y;
    
    int iUp     = 0;
    int iRight  = 0;
    
    int dy = abs(c-y); //+
    int dx = abs(x-r); //-
    int dRemain = k-(dx+dy);
    if (dRemain<0 || dRemain%2){
        answer = "impossible";
    }
    else{
        dRemain = dRemain/2;
        //일단 최대한 아래로
        if(x<r){
            for(int i =0; i< r-x; i++) 
                answer += "d"; 
            ix+=(r-x);
        }
        while(ix<n && dRemain>0){
            ix++;
            dRemain--;
            answer += "d"; 
        }
        
        if(y>c){
            for(int i =0; i< y-c; i++) 
                answer += "l"; 
            iy-=(y-c);
        }
        while(iy>1 && dRemain>0){
            iy--;
            dRemain--;
            answer += "l"; 
        }
        
        for(int i=0; i<dRemain; i++){
            answer += "rl"; 
        }
        
        //right 보상
        while(iy<c){
            iy++;
            answer += "r"; 
        }
        //up보상
        while(ix>r){
            ix--;
            answer += "u"; 
        }
    }
    return answer;
}