#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    map<string, vector<string>> setEdges;
    map<pair<string,string>, int> setVisited;
    for(auto _edge : tickets){
        if (setEdges.find(_edge[0])==setEdges.end()) setEdges[_edge[0]] = vector<string>();
        if (setEdges.find(_edge[1])==setEdges.end()) setEdges[_edge[1]] = vector<string>();
        
        if (setVisited.find(pair<string,string>(_edge[0], _edge[1])) == setVisited.end())
            setVisited[pair<string,string>(_edge[0], _edge[1])] = 1;
        else
            setVisited[pair<string,string>(_edge[0], _edge[1])]++;
        
        setEdges[_edge[0]].push_back(_edge[1]);
    }
    for(auto& [_, _edgeList] : setEdges){
        sort(_edgeList.begin(), _edgeList.end());
    }
    int n = tickets.size();
    
    auto DFS = [&](auto&& self, const string& sSrtNode)->bool{
        answer.push_back(sSrtNode);
        if (answer.size()==n+1) return true;
        for(auto sDstNode : setEdges[sSrtNode]){
            if (setVisited[pair<string,string>(sSrtNode, sDstNode)]<=0) continue;
            setVisited[pair<string,string>(sSrtNode, sDstNode)]--;
            if (self(self, sDstNode)) return true;
            setVisited[pair<string,string>(sSrtNode, sDstNode)]++;
        }
        answer.pop_back();
        return false;
    };
    
    DFS(DFS, "ICN");
    
    
    return answer;
}