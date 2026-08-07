#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    struct FactorCount {
        int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
    };

    FactorCount getFactors(long long n) {
        FactorCount fc;
        while (n % 2 == 0) { fc.c2++; n /= 2; }
        while (n % 3 == 0) { fc.c3++; n /= 3; }
        while (n % 5 == 0) { fc.c5++; n /= 5; }
        while (n % 7 == 0) { fc.c7++; n /= 7; }
        if (n > 1) return {-1, -1, -1, -1};
        return fc;
    }

    FactorCount digitFactors(char d) {
        int val = d - '0';
        if (val == 0) return {0, 0, 0, 0};
        FactorCount fc;
        while (val % 2 == 0) { fc.c2++; val /= 2; }
        while (val % 3 == 0) { fc.c3++; val /= 3; }
        while (val % 5 == 0) { fc.c5++; val /= 5; }
        while (val % 7 == 0) { fc.c7++; val /= 7; }
        return fc;
    }

    string getMinSuffix(FactorCount fc) {
        int c2 = max(0, fc.c2);
        int c3 = max(0, fc.c3);
        int c5 = max(0, fc.c5);
        int c7 = max(0, fc.c7);

        int count9 = c3 / 2; c3 %= 2;
        int count8 = c2 / 3; c2 %= 3;
        int count7 = c7;
        int count5 = c5;
        int count6 = 0, count4 = 0, count3 = 0, count2 = 0;

        if (c2 == 2 && c3 == 1) {
            count6 = 1;
            count2 = 1;
        } else if (c2 == 1 && c3 == 1) {
            count6 = 1;
        } else if (c2 == 2 && c3 == 0) {
            count4 = 1;
        } else if (c2 == 1 && c3 == 0) {
            count2 = 1;
        } else if (c2 == 0 && c3 == 1) {
            count3 = 1;
        }

        string suffix = "";
        suffix += string(count2, '2');
        suffix += string(count3, '3');
        suffix += string(count4, '4');
        suffix += string(count5, '5');
        suffix += string(count6, '6');
        suffix += string(count7, '7');
        suffix += string(count8, '8');
        suffix += string(count9, '9');
        return suffix;
    }

public:
    string smallestNumber(string num, long long t) {
        FactorCount req = getFactors(t);
        if (req.c2 == -1) return "-1";

        int n = num.length();
        int first_zero = num.find('0');
        int limit = (first_zero == string::npos) ? n : first_zero;

        vector<FactorCount> pref(n + 1);
        for (int i = 0; i < limit; ++i) {
            FactorCount df = digitFactors(num[i]);
            pref[i + 1] = {
                pref[i].c2 + df.c2,
                pref[i].c3 + df.c3,
                pref[i].c5 + df.c5,
                pref[i].c7 + df.c7
            };
        }

        if (first_zero == string::npos) {
            FactorCount rem = {
                req.c2 - pref[n].c2,
                req.c3 - pref[n].c3,
                req.c5 - pref[n].c5,
                req.c7 - pref[n].c7
            };
            if (rem.c2 <= 0 && rem.c3 <= 0 && rem.c5 <= 0 && rem.c7 <= 0) {
                return num;
            }
        }

        for (int i = limit; i >= 0; --i) {
            char start_d = (i == n) ? '1' : (num[i] + 1);

            for (char d = start_d; d <= '9'; ++d) {
                FactorCount df = digitFactors(d);
                FactorCount rem = {
                    req.c2 - (pref[i].c2 + df.c2),
                    req.c3 - (pref[i].c3 + df.c3),
                    req.c5 - (pref[i].c5 + df.c5),
                    req.c7 - (pref[i].c7 + df.c7)
                };

                string min_suf = getMinSuffix(rem);
                int available_len = n - 1 - i;

                if ((int)min_suf.length() <= available_len) {
                    string res = num.substr(0, i);
                    res += d;
                    res += string(available_len - min_suf.length(), '1');
                    res += min_suf;
                    return res;
                }
            }
        }

        for (int len = n + 1; ; ++len) {
            for (char d = '1'; d <= '9'; ++d) {
                FactorCount df = digitFactors(d);
                FactorCount rem = {
                    req.c2 - df.c2,
                    req.c3 - df.c3,
                    req.c5 - df.c5,
                    req.c7 - df.c7
                };

                string min_suf = getMinSuffix(rem);
                if ((int)min_suf.length() <= len - 1) {
                    string res = "";
                    res += d;
                    res += string((len - 1) - min_suf.length(), '1');
                    res += min_suf;
                    return res;
                }
            }
        }

        return "-1";
    }
};