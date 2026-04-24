#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> a(n), b(n);
    int total_water = 0;
    int max_spare = 0;
    
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        total_water += b[i];
        max_spare += (a[i] - b[i]);
    }
    
    const double NEG_INF = -1e18;
    // dp[j][s] = max water in chosen glasses, when j glasses chosen, total spare capacity = s
    vector<vector<double>> dp(n + 1, vector<double>(max_spare + 1, NEG_INF));
    dp[0][0] = 0.0;
    
    for (int i = 0; i < n; i++) {
        int spare = a[i] - b[i];
        int water = b[i];
        // 0/1 knapsack: iterate j and s in reverse
        for (int j = min(i, n - 1); j >= 0; j--) {
            for (int s = max_spare - spare; s >= 0; s--) {
                if (dp[j][s] < NEG_INF / 2) continue;
                double nval = dp[j][s] + water;
                if (nval > dp[j + 1][s + spare]) {
                    dp[j + 1][s + spare] = nval;
                }
            }
        }
    }
    
    cout << fixed << setprecision(10);
    
    for (int k = 1; k <= n; k++) {
        double best = 0.0;
        for (int s = 0; s <= max_spare; s++) {
            if (dp[k][s] < NEG_INF / 2) continue;
            double w_in = dp[k][s];
            double w_out = total_water - w_in;
            double val = w_in + min((double)s, w_out / 2.0);
            if (val > best) best = val;
        }
        cout << best;
        if (k < n) cout << ' ';
    }
    cout << '\n';
    
    return 0;
}