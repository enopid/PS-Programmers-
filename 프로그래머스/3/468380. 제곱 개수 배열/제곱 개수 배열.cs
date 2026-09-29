using System;
using System.Collections.Generic;

public class Solution {
    public long[] solution(int[] arr, long l, long r) {
        var DP = new (long, long)[arr.Length+1];
        DP[0] = (0,0);

        long iMaxBrr = 0;
        for(long i=0; i<arr.Length; i++){
            iMaxBrr += (long)arr[i];
            DP[i+1] = (DP[i].Item1+arr[i],DP[i].Item2 + (long)arr[i]*(long)arr[i]);
        }

        Func<long,long> GetSum = value => {
            if (value==0) return 0;
            if (value==iMaxBrr) return DP[arr.Length].Item2;

            long lv = 0;
            long rv = arr.Length;

            while(lv+1<rv){
                long mid = (lv+rv)/2;

                if (DP[mid].Item1 <= value){
                    lv = mid;
                }
                else{
                    rv = mid;
                }
            }

            return DP[lv].Item2 + (long)arr[lv] * (value - DP[lv].Item1);
        };

        Func<long,long> GetIndex = value => {
            long lv = 0;
            long rv = arr.Length;

            while(lv+1<rv){
                long mid = (lv+rv)/2;

                if (DP[mid].Item1 <= value){
                    lv = mid;
                }
                else{
                    rv = mid;
                }
            }

            return lv;
        };

        long K = GetSum(r)-GetSum(l-1);
        long C = 0;

        long iLength = r-l+1;
        long iMaxStart = iMaxBrr-iLength;

        var Events = new List<long>();
        Events.Add(0);
        Events.Add(iMaxStart);

        for(long i=1; i<arr.Length; i++){
            long iEvent = DP[i].Item1;

            if (0<iEvent && iEvent<iMaxStart)
                Events.Add(iEvent);

            iEvent = DP[i].Item1-iLength;

            if (0<iEvent && iEvent<iMaxStart)
                Events.Add(iEvent);
        }

        Events.Sort();

        // 중복 제거
        long iPrev = -1;
        var UniqueEvents = new List<long>();

        foreach(long iEvent in Events){
            if (iPrev==iEvent)
                continue;

            UniqueEvents.Add(iEvent);
            iPrev = iEvent;
        }

        long iSum = GetSum(iLength);

        for(int i=0; i<UniqueEvents.Count-1; i++){
            long iStart = UniqueEvents[i];
            long iEnd = UniqueEvents[i+1];
            long iCount = iEnd-iStart;

            long iLeftIndex = GetIndex(iStart);
            long iRightIndex = GetIndex(iStart+iLength);

            long iDiff = (long)arr[iRightIndex] - arr[iLeftIndex];

            // 현재 구간에서는
            // Sum(x) = iSum + iDiff*x
            if (iDiff==0){
                if (iSum==K)
                    C += iCount;
            }
            else{
                long iRemain = K-iSum;

                if (iRemain%iDiff==0){
                    long iOffset = iRemain/iDiff;

                    if (0<=iOffset && iOffset<iCount)
                        C++;
                }
            }

            iSum += iDiff*iCount;
        }

        if (GetSum(iMaxBrr)-GetSum(iMaxStart)==K)
            C++;

        long[] answer = new long[] {K,C};

        return answer;
    }
}