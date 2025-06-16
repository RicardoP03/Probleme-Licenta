#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, T;
    cin >> n >> T;
    int s[n + 5];
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    int dp[n + 5][T + 5];
    memset(dp, 0, sizeof(dp));

    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= T; j++) {
            dp[i][j] |= dp[i - 1][j];
            if(j >= s[i]) dp[i][j] |= dp[i - 1][j - s[i]];
        }
    }

    if(dp[n][T]) cout << "Suma tinta poate fi formata folosind elementele multimii S\n";
    else cout << "Suma tinta nu poate fi formata\n";
    return 0;
}