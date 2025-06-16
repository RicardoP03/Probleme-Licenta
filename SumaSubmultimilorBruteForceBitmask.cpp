#include <bits/stdc++.h>
using namespace std;


int main() {
    int n, T;
    cin >> n >> T;
    int s[n + 5];
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    bool can = false;
    for(int bitmask = 0; bitmask < (1 << n); bitmask++) {
        int sum = 0;
        for(int i = 0; i < n; i++) {
            if(bitmask & (1 << i)) sum += s[i + 1];
        }

        if(sum == T) {
            can = true;
            break;
        }
    }
    if(can) cout << "Suma tinta poate fi formata folosind elementele multimii S\n";
    else cout << "Suma tinta nu poate fi formata\n";
    return 0;
}