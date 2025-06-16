#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bitset<200005> dp, aux;
int a[200005];
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    for(int i = 0; i <= 2 * n; i++) {
        aux[i] = 1;
    }

    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        dp |= (dp & aux) << a[i];
        aux[i - 1] = 0;
    }

    ll sum = 0, sol = 0;
    for(int i = 1; i <= 2 * n; i++) {
        sum += a[i];
        if(dp[i - 1] == 1) {
            sol = max(sol, sum - i + 1);
        }
    }
    cout << sol;
    return 0;
}