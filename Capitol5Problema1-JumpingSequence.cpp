#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<bool> subSetSum(const vector<int> &a, int T){
    int n = a.size(), D = 0;
    for(int x : a) {
        D = max(D, x);
    }
    int l = 0, sumL = 0;
    while(l < n && sumL + a[l] <= T) {
        sumL += a[l];
        l++;
    }

    if(l == n && sumL!=T) {
        return {};
    }
    vector<int> dp(D * 2, -1);
    vector<vector<int>> aux(n, vector<int>(D * 2, -1));
    dp[sumL - (T - D + 1)] = l;
    for(int i = l; i < n; i++) {
        vector<int> dp2 = dp;
        vector<int> &aux2 = aux[i]; 
        for(int j = D - 1; j >= 0; j--) {
            if(dp2[j + a[i]] < dp2[j]){
                aux2[j + a[i]] = -2;
                dp2[j + a[i]] = dp2[j];
            }
        }

        for(int j = D * 2 - 1; j >= D; j--) {
            for(int k = dp2[j] - 1; k >= max(dp[j], 0); k--) {
                if(dp2[j - a[k]] < k){
                    aux2[j - a[k]] = k;
                    dp2[j - a[k]] = k;
                }
            }
        }
        swap(dp, dp2);
    }
    if(dp[D - 1] == -1) {
        return {};
    }

    vector<bool> ans(n);
    int i = n - 1, j = D - 1;
    while(i >= l){
        int p = aux[i][j];
        if(p == -2) {
            ans[i] = !ans[i];
            j -= a[i];
            i--;
        }
        else if(p == -1) i--;
        else {
            ans[p] = !ans[p];
            j += a[p];
        }
    }
    while(i >= 0){
        ans[i] = !ans[i];
        i--;
    }
    return ans;
}

int main(){
    int n, a, b;
    cin >> n >> a >> b;
    int X = a + b, Y = a - b;
    int sum = 0;
    vector<int> d(n);
    for(int i = 0; i < n; i++){
        cin >> d[i];
        sum += d[i];
    }
    if(sum < abs(X) || sum < abs(Y) || (sum + X) % 2 != 0 || (sum + Y) % 2 != 0){
        cout << "No\n";
        return 0;
    }
    vector<bool> solA = subSetSum(d, (sum + X) / 2), solB = subSetSum(d, (sum + Y) / 2);
    if(solA.empty()||solB.empty()){
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    for(int i = 0; i < n; i++){
        if(solA[i] && solB[i]) cout << "R";
        else if(solA[i] && !solB[i]) cout << "U";
        else if(!solA[i] && solB[i]) cout << "D";
        else cout << "L";
    }
    cout << "\n";
    return 0;
}