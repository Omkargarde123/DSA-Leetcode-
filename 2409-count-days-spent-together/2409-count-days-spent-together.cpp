class Solution {
private:
    int getDayNumber(string date) {
        int m = stoi(date.substr(0, 2)), d = stoi(date.substr(3, 2));
        int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        for (int i = 1; i < m; ++i) d += days[i];
        return d;
    }

public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        int start = max(getDayNumber(arriveAlice), getDayNumber(arriveBob));
        int end = min(getDayNumber(leaveAlice), getDayNumber(leaveBob));
        return max(0, end - start + 1);
    }
};