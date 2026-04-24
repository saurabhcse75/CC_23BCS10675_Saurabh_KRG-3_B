#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll P1 = 31, MOD1 = 1e9 + 7;
const ll P2 = 37, MOD2 = 1e9 + 9;

const int MAXN = 600000 + 5;

ll p1[MAXN], p2[MAXN];

pair<ll,ll> get_hash(const string &s) {
    ll h1 = 0, h2 = 0;
    for (int i = 0; i < s.size(); i++) {
        ll val = (s[i] - 'a' + 1);
        h1 = (h1 + val * p1[i]) % MOD1;
        h2 = (h2 + val * p2[i]) % MOD2;
    }
    return {h1, h2};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute powers
    p1[0] = p2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        p1[i] = (p1[i-1] * P1) % MOD1;
        p2[i] = (p2[i-1] * P2) % MOD2;
    }

    int n, m;
    cin >> n >> m;

    unordered_map<int, set<pair<ll,ll>>> mp;

    string s;

    // Store strings
    for (int i = 0; i < n; i++) {
        cin >> s;
        mp[s.size()].insert(get_hash(s));
    }

    while (m--) {
        cin >> s;

        int len = s.size();

        if (!mp.count(len)) {
            cout << "NO\n";
            continue;
        }

        auto [h1, h2] = get_hash(s);

        bool found = false;

        for (int i = 0; i < len && !found; i++) {
            ll old_val = (s[i] - 'a' + 1);

            for (char c : {'a','b','c'}) {
                if (c == s[i]) continue;

                ll new_val = (c - 'a' + 1);

                ll nh1 = h1;
                ll nh2 = h2;

                // remove old
                nh1 = (nh1 - old_val * p1[i] % MOD1 + MOD1) % MOD1;
                nh2 = (nh2 - old_val * p2[i] % MOD2 + MOD2) % MOD2;

                // add new
                nh1 = (nh1 + new_val * p1[i]) % MOD1;
                nh2 = (nh2 + new_val * p2[i]) % MOD2;

                if (mp[len].count({nh1, nh2})) {
                    found = true;
                    break;
                }
            }
        }

        cout << (found ? "YES\n" : "NO\n");
    }

    return 0;
}