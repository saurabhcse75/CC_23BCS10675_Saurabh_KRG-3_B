#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int &x : a) cin >> x;

        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + a[i];
        }

        vector<bool> possible(n + 1, false);

        // Generate all subarray sums of length >= 2
        for (int l = 0; l < n; l++) {
            for (int r = l + 2; r <= n; r++) {
                int sum = prefix[r] - prefix[l];
                if (sum > n) break; // pruning
                possible[sum] = true;
            }
        }

        int count = 0;
        for (int x : a) {
            if (possible[x]) count++;
        }

        cout << count << "\n";
    }

    return 0;
}