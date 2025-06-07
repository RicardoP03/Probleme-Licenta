#include <bits/stdc++.h>
using namespace std;

bitset<1000000> dp;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    int p[n + 5];
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    int cyclesize[n + 5] = {0}, viz[n + 5] = {0};
    for(int i = 1; i <= n; i++) {
        if(viz[i] == 0) {
            int ct = 0, aux = i;
            while(viz[aux] == 0) {
                ct++;
                viz[aux] = 1;
                aux = p[aux];
            }
            cyclesize[ct]++;
        }
    }

    int solMax = 0, auxK = k;
    for(int i = 1; i <= n; i++) {
        int num = (i / 2) * cyclesize[i];
        if(num >= auxK) {
            solMax += 2 * auxK;
            auxK = 0;
            break;
        }
        else solMax += 2 * num, auxK -= num;
    }
    solMax += auxK;

    dp[0] =  1;
    for(int i = 1; i <= n; i++) {
        if(cyclesize[i] > 2) {
            cyclesize[2 * i] += (cyclesize[i] - 1) / 2;
            cyclesize[i] -=  (cyclesize[i] - 1) / 2 * 2;
        }

        while(cyclesize[i]) {
            dp |= dp << i;
            cyclesize[i]--;
        }
    }

    cout << k + 1 - dp[k] << " " << min(solMax, n);
    return 0;
}