#include <bits/stdc++.h>
using namespace std;

bool canReachTargetSum(int T, int n, int* s, int idx = 1, int sum = 0) {
    if(sum == T) return true;
    if(sum > T) return false;
    if(idx > n) return false;

    return canReachTargetSum(T, n, s, idx + 1, sum + s[idx]) || canReachTargetSum(T, n, s, idx + 1, sum);
}

int main() {
    int n, T;
    cin >> n >> T;
    int s[n + 5];
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    if(canReachTargetSum(T, n, s)) cout << "Suma tinta poate fi formata folosind elementele multimii S\n";
    else cout << "Suma tinta nu poate fi formata\n";
    return 0;
}