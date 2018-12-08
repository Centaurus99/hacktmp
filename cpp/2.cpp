# include <stdio.h>
# include <string.h>
# include <algorithm>
// # include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
const int M = 5e5 + 10;

# define RG register
# define ST static

int n, m, p, c, a[M], phi[M], pn;
int pws[27][M][2]; 
bool pwk[27][M][2];
inline int pwr(int a, int b, int p, bool &ok) {
    ok = 0;
    int ret = 1;
    while(b) {
        if(b&1) ok |= (1ll * ret * a >= p), ret = 1ll * ret * a % p;
        ok |= (1ll * a * a >= p && b != 1); a = 1ll * a * a % p; 
        b >>= 1;
    }
    return ret;
}

inline int getphi(int n) {
    int ret = n;
    for (int i=2; i*i<=n; ++i) {
        if(n%i!=0) continue;
        ret = ret/i*(i-1);
        while(n%i==0) n/=i;
    }
    if(n!=1) ret=ret/n*(n-1);
    return ret;
}

inline int pwrb(int b, int p, bool &ok){
    p = min(p, pn); ok = 0;
    ok |= pwk[p][b & 16383][0];
    ok |= pwk[p][b >> 14][1];
    ok |= (1ll * pws[p][b & 16383][0] * pws[p][b >> 14][1] >= phi[p]);
    return 1ll * pws[p][b & 16383][0] * pws[p][b >> 14][1] % phi[p];
}
inline int calc(int x, int p) {
    int ret = x; bool ok;
    if(ret >= phi[p]) ret = ret % phi[p] + phi[p];
    while(p--) {
        x = ret;
        ret = pwrb(x, p, ok); 
        if(ok) ret += phi[p]; 
    }
    return ret % phi[0];
}

namespace SMT {
    # define ls (x<<1)
    # define rs (x<<1|1) 
    int v[M], tms[M];
    inline void build(int x, int l, int r) {
        if(l==r) {
            v[x] = a[l] % phi[0];
            tms[x] = 0; 
            return ;
        }
        int mid = l+r>>1;
        build(ls, l, mid);
        build(rs, mid+1, r);
        v[x] = (v[ls]+v[rs])%phi[0];
        tms[x] = min(tms[ls], tms[rs]);
    }
    inline void change(int x, int l, int r, int L, int R) {
        if(tms[x] >= pn) return;
        if(l == r) {
            tms[x] ++;
            v[x] = calc(a[l], tms[x]);
            return ;
        }
        int mid = l+r>>1;
        if(L <= mid) change(ls, l, mid, L, R);
        if(R > mid) change(rs, mid+1, r, L, R);
        v[x] = (v[ls]+v[rs])%phi[0];
        tms[x] = min(tms[ls], tms[rs]);
    }
    inline int query(int x, int l, int r, int L, int R) {
        if(L <= l && r <= R) return v[x];
        int mid = l+r>>1, re=0;
        if(L <= mid) re += query(ls, l, mid, L, R);
        if(R > mid) re += query(rs, mid+1, r, L, R);
        return re%phi[0];
    }
    # undef ls
    # undef rs
}

int main() {
    scanf("%d%d%d%d", &n, &m, &p, &c);
    for (int i=1; i<=n; ++i) scanf("%d", a+i); 
    phi[0] = p; 
    while(p != 1) {
        int t = getphi(p);
        phi[++pn] = t;
        p = t;
    }
    phi[++pn] = 1;
    for(int i=0; i<=pn; ++i) {
        bool ok;
        int j = pwr(c, 16384, phi[i], ok);
        pws[i][0][0] = pws[i][0][1] = 1;
        pwk[i][0][0] = 0, pwk[i][0][1] = 0;
        for(int k=1; k<16384; k++) 
            pwk[i][k][0] = pwk[i][k-1][0] | (1ll * pws[i][k-1][0] * c >= phi[i]),
            pws[i][k][0] = 1ll * pws[i][k-1][0] * c % phi[i],
            pwk[i][k][1] = pwk[i][k-1][1] | (ok || (1ll * pws[i][k-1][1] * j >= phi[i])),
            pws[i][k][1] = 1ll * pws[i][k-1][1] * j % phi[i]; 
    }
    
    SMT::build(1, 1, n); 
    int opt, l, r;
    while(m--) {
        scanf("%d%d%d", &opt, &l, &r);
        if(opt==0) SMT::change(1, 1, n, l, r); 
        else printf("%d\n", SMT::query(1, 1, n, l, r));
    }
    return 0;
}
