#define ll long long
#define MOD 1000000007

ll gcd(ll a,ll b) { if (b==0) return a; return gcd(b, a%b); }
ll mod(ll x) { return (((x%MOD) + MOD) % MOD); }
ll addMod(ll a, ll b) { return mod(mod(a) + mod(b)); } // (a + b)%MOD
ll subMod(ll a, ll b) { return mod(mod(a) - mod(b)); } // (a - b)%MOD
ll mulMod(ll a, ll b) { return mod(mod(a) * mod(b)); } // (a*b)%MOD
ll powMod(ll x, ll n) { if (n == 0) return 1%MOD; ll u = powMod(x,n/2); u = (u*u)%MOD; if (n%2 == 1) u = (u*x)%MOD; return u; } // (x^n)%MOD
ll inverseMod(ll a) { if (gcd(a, MOD) != 1) return -1; return powMod(a, MOD-2); }
ll divMod(ll a, ll b) { ll tmp = inverseMod(b); if (tmp == -1) return -1; return (((a%MOD)*inverseMod(b))%MOD); }