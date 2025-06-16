#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

//Template NTT | Author: Bucă Mihnea-Vicențiu
//-------------------------------------------------------------------------

template <unsigned int MD> struct ModInt {
    using M = ModInt;
    const static M G;

    unsigned int v;
    ModInt(ll _v = 0) {set_v(_v % MD + MD);}

    M& set_v(unsigned int _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }

    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    M operator*(const M& r) const { return M().set_v(ull(v) * r.v % MD); }
    M operator/(const M& r) const { return *this * r.inv(); }
    M& operator+=(const M& r) { return *this = *this + r; }
    M& operator-=(const M& r) { return *this = *this - r; }
    M& operator*=(const M& r) { return *this = *this * r; }
    M& operator/=(const M& r) { return *this = *this / r; }
    bool operator==(const M& r) const { return v == r.v; }
    M pow(ll n) const {
        M x = *this, r = 1;
        while(n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    M inv() const { return pow(MD - 2); }
    friend istream& operator>>(istream& in, M& r) {int v; in >> v; r = v; return in;}
    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }
};

using Mint = ModInt <998'244'353>;
template <> const Mint Mint::G = Mint(3);

template <class Mint> void nft(bool type, vector <Mint>& a) {
    int n = a.size(), s = 0;
    while ((1 << s) < n) s++;

    static vector <Mint> ep, iep;
    while (ep.size() <= s) {
        ep.push_back(Mint::G.pow(Mint(-1).v / (1 << ep.size())));
        iep.push_back(ep.back().inv());
    }

    vector <Mint> b(n);
    for (int i = 1; i <= s; ++i) {
        int w = 1 << (s - i);
        Mint base = type ? iep[i] : ep[i], now = 1;
        for (int y = 0; y < n / 2; y += w) {
            for (int x = 0; x < w; x++) {
                auto l = a[y << 1 | x];
                auto r = now * a[y << 1 | x | w];
                b[y | x] = l + r;
                b[y | x | n >> 1] = l - r;
            }
            now *= base;
        }
        swap(a, b);
    }
}

template <class Mint> vector <Mint> multiply(const vector <Mint>& a, const vector <Mint>& b) {
    int n = a.size(), m = b.size(); 
    if (!n || !m) return {};
 
    int lg = 0;
    while ((1 << lg) < n + m - 1) lg++;
 
    int z = 1 << lg;
    vector <Mint> a2(z), b2(z);
    for (int i = 0; i < z; ++i) {
        a2[i] = i < n? Mint(a[i]) : 0;
        b2[i] = i < m? Mint(b[i]) : 0;
        
    }
 
    nft(false, a2), nft(false, b2);
    for (int i = 0; i < z; i++) a2[i] *= b2[i];
    nft(true, a2);
 
    a2.resize(n + m - 1);
    Mint iz = Mint(z).inv();
 
    for (int i = 0; i < n + m - 1; i++) a2[i] *= iz;
    return a2;
}
//------------------------------------------------------------------------------


int main() {
    int n, k;
    cin >> n >> k;
    vector<Mint> a(10);
    for(int i = 0; i < k; i++) {
        int x;
        cin >> x;
        a[x] = 1;
    }

    vector<Mint> sol;
    sol.push_back(1);
    n /= 2;
    while(true) {
        if((n & 1) != 0) sol = multiply<Mint>(sol, a);
        n /= 2;
        if(n == 0) break;
        a = multiply<Mint>(a, a);
    }

    Mint ans = 0;
    for(auto x: sol) {
        ans += x * x;
    }
    cout << ans << "\n";
}


