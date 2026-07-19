class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int n = landStartTime.size();
        int m = waterStartTime.size();

        int minLandFinish = 2e9 + 7;
        for (int i = 0; i < n; ++i) {
            minLandFinish = min(minLandFinish, landStartTime[i] + landDuration[i]);
        }

        int minWaterFinish = 2e9 + 7;
        for (int j = 0; j < m; ++j) {
            minWaterFinish = min(minWaterFinish, waterStartTime[j] + waterDuration[j]);
        }

        int case1 = 2e9 + 7;
        for (int j = 0; j < m; ++j) {
            case1 = min(case1, max(minLandFinish, waterStartTime[j]) + waterDuration[j]);
        }

        int case2 = 2e9 + 7;
        for (int i = 0; i < n; ++i) {
            case2 = min(case2, max(minWaterFinish, landStartTime[i]) + landDuration[i]);
        }

        return min(case1, case2);
    }
};