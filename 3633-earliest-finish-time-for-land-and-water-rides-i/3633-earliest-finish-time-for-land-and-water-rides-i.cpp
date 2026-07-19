
class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, 
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        int minFinishTime = INT_MAX;
        int n = landStartTime.size();
        int m = waterStartTime.size();
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int finishLand1 = landStartTime[i] + landDuration[i];
                int startWater1 = max(finishLand1, waterStartTime[j]);
                int totalTime1 = startWater1 + waterDuration[j];
                
                int finishWater2 = waterStartTime[j] + waterDuration[j];
                int startLand2 = max(finishWater2, landStartTime[i]);
                int totalTime2 = startLand2 + landDuration[i];
                
                minFinishTime = min({minFinishTime, totalTime1, totalTime2});
            }
        }
        
        return minFinishTime;
    }
};