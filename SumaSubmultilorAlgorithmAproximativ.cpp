#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, T;
    cin >> n >> T;
    int s[n + 5];
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    int sum = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] + sum > T) sum = max(sum, s[i]);
        else sum += s[i];
    }
    cout << sum;
    return 0;
}