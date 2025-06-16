#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bitset<2005> dp[2005];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t = 1;
    cin >> t;
    while(t--) {
        int n, d;
        cin >> n >> d;
        int a[n + 5];
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        
        sort(a + 1, a + n + 1);
        if(a[n] + a[n - 1] > d) {
            cout << "NO\n";
            continue;
        }

        dp[0][0] = 1;
        bool ok = false;
        for(int i = 1; i < n; i++) {
            for(int j = d; j >= a[i]; j--) {
                dp[j] |= dp[j - a[i]] << a[i];
                dp[j] |= dp[j - a[i]]; 
            }

            int val = a[n];
            for(int j = 0; j <= d; j++) {
                if(dp[d][j] == 1 && val <= min(j, d - j)) ok = true;
            }
        }

        for(int i = 0; i <= d; i++) {
            if(dp[d - a[n]][i] == 1) ok = true;
        }
        
        if(ok) cout << "YES\n";
        else cout << "NO\n";
        memset(dp, 0, sizeof(dp));
    }
    return 0;
}