#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

//대소문자 구분 없이 등장 횟수
//알파벳을 제외한 문자로 구분


using namespace std;

int solution(string word, vector<string> pages) {
    int answer = 0;
    map<string, int> mapURL2IDX;
    vector<vector<string>> mapURL2REFURLS;
    vector<int> vecBaseScores;
    vector<float> vecLinkScores(pages.size(), 0.f);
    transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {return tolower(c);});
    auto GetBaseScore = [&pages, &word](int iPageIdx)
    {
        int iScore   = 0;
        int iSrtIdx  = pages[iPageIdx].find("<body>") + 5;
        int iEndIdx  = pages[iPageIdx].find("</body>");
        int bFlag       = false;
        for(int i=iSrtIdx; i<iEndIdx+1; i++){
            if (pages[iPageIdx][i]=='<'){
                if (pages[iPageIdx][i+1]=='/'){
                    bFlag = false;
                }
                else{
                    bFlag = true;
                }
            } 
            if (bFlag) continue;
            
            if (!isalpha(pages[iPageIdx][i])){
                auto sWord = pages[iPageIdx].substr(iSrtIdx, i-iSrtIdx);
                transform(sWord.begin(), sWord.end(), sWord.begin(), [](unsigned char c) {return tolower(c);});
                if (i-iSrtIdx>0){
                    if (sWord==word){
                        iScore++;
                    }
                }
                iSrtIdx=i+1;
            }
        }
        return iScore;
    };
    
    auto GetTag = [&pages](int iPageIdx)->string{
        int srtIdx = 0;
        srtIdx = pages[iPageIdx].find("head", srtIdx);
        srtIdx = pages[iPageIdx].find("meta property=", srtIdx);
        srtIdx = pages[iPageIdx].find("content=", srtIdx);
        
        int urlSrtIdx = pages[iPageIdx].find("\"", srtIdx)+1;
        int urlEndIdx = pages[iPageIdx].find("\"", urlSrtIdx);
        
        auto sWord = pages[iPageIdx].substr(urlSrtIdx, urlEndIdx-urlSrtIdx);
        return sWord;
    };
    
    auto GetRefTags = [&pages](int iPageIdx)->vector<string>{
        vector<string> vecRefTags;
        int srtIdx = 0;
        while(true){
            srtIdx = pages[iPageIdx].find("a href=", srtIdx+1);
            if (srtIdx==string::npos) break;

            int urlSrtIdx = pages[iPageIdx].find("\"", srtIdx)+1;
            int urlEndIdx = pages[iPageIdx].find("\"", urlSrtIdx);

            auto sWord = pages[iPageIdx].substr(urlSrtIdx, urlEndIdx-urlSrtIdx);
            vecRefTags.push_back(sWord);
        }
        return vecRefTags;
    };
    
    
    
    for(int i=0; i<pages.size(); i++) {
        mapURL2IDX[GetTag(i)] = i;
        mapURL2REFURLS.push_back(GetRefTags(i));
    }
    for(int i=0; i<pages.size(); i++) {
        vecBaseScores.push_back(GetBaseScore(i));
    }
    for(auto& [_sTag, _iIdx] : mapURL2IDX){
        for(const auto& sRefTag : mapURL2REFURLS[_iIdx]){
            if (mapURL2IDX.find(sRefTag) == mapURL2IDX.end()) continue;
            vecLinkScores[mapURL2IDX[sRefTag]] +=
            (float)vecBaseScores[_iIdx] / mapURL2REFURLS[_iIdx].size();
        }
    }
    
    //for(int i=0; i<pages.size(); i++) cout << vecBaseScores[i] << "+" << vecLinkScores[i] << "=" << vecBaseScores[i]+vecLinkScores[i] << " ";
    
    float fMaxV = -1.f;
    for(int i=0; i<pages.size(); i++) {
        fMaxV = max(
            vecBaseScores[i]+vecLinkScores[i],
            fMaxV
        );
    }
    
    for(int i=0; i<pages.size(); i++) {
        if (fMaxV == vecBaseScores[i]+vecLinkScores[i]){
            return i;
        }
    }
    
    return answer;
}