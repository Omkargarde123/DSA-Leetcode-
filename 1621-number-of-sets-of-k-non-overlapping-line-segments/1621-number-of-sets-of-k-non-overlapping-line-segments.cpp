class Solution {
public:
    int numberOfSets(int n, int k) {
        long long MOD = 1e9 + 7;
        long long N = n + k - 1;
        long long R = 2 * k;

        if (R > N) return 0;
        if (R > N - R) R = N - R;

        long long num = 1, den = 1;

        for (int i = 1; i <= R; ++i) {
            num = (num * (N - i + 1)) % MOD;
            den = (den * i) % MOD;
        }

        return (num * power(den, MOD - 2, MOD)) % MOD;
    }

private:
    long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return res;
    }
};