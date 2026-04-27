class Solution {
public:
    vector<int> search(string pat, string txt) {
        int n = txt.size(), m = pat.size();
        vector<int> ans;

        if(m == 0) return ans;

    
        vector<int> lps(m, 0);
        int len = 0;

        for(int i = 1; i < m; ) {
            if(pat[i] == pat[len]) {
                lps[i++] = ++len;
            } else {
                if(len != 0) len = lps[len - 1];
                else lps[i++] = 0;
            }
        }

    
        int i = 0, j = 0;

        while(i < n) {
            if(txt[i] == pat[j]) {
                i++;
                j++;
            }

            if(j == m) {
                ans.push_back(i - j);
                j = lps[j - 1];
            }
            else if(i < n && txt[i] != pat[j]) {
                if(j != 0) j = lps[j - 1];
                else i++;
            }
        }

        return ans;
    }
};