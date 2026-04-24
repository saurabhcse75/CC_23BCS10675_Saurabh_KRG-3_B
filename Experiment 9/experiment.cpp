#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool can(vector<ll>& h, ll H, ll D) {
    ll odd = (D + 1) / 2;   // +1 operations
    ll even = D / 2;        // +2 operations

    ll need1 = 0, need2 = 0;

    for (auto x : h) {
        ll d = H - x;
        need1 += d % 2;
        need2 += d / 2;
    }

    // If not enough +2 days, convert to +1
    if (even < need2) {
        ll shortage = need2 - even;
        need1 += 2 * shortage;
        need2 = even;
    }

    return need1 <= odd;
}

ll solve(vector<ll>& h, ll H) {
    ll l = 0, r = 1e18;

    while (l < r) {
        ll mid = (l + r) / 2;
        if (can(h, H, mid)) r = mid;
        else l = mid + 1;
    }

    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<ll> h(n);
        for (auto &x : h) cin >> x;

        ll mx = *max_element(h.begin(), h.end());

        ll ans = min(
            solve(h, mx),
            solve(h, mx + 1)
        );

        cout << ans << "\n";
    }

    return 0;
}