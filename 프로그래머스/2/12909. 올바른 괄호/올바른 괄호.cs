using System;
using System.Collections.Generic;

public class Solution {
    public bool solution(string s) {
        bool answer = true;
        Stack<char> st = new Stack<char>();
        foreach (char sWord in s){
            if(sWord == ')'){
                if (st.Count!=0 && st.Peek()=='('){
                    st.Pop();
                    continue;
                }
            }
            st.Push(sWord);
        }
        
        answer = st.Count==0;
        return answer;
    }
}