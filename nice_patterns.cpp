#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define si second
using namespace std;
const ll maxn = (1<<16);
const ll inf = 1e18;
ll n, m;
char a[31][31];
vector<vector<ll> >  dp[maxn];
int main() {
      ios::sync_with_stdio(0); cin.tie(0);
      cin >> n >> m;
      if (n > m) {
            swap(n, m);
      }

      ll e = (1<<(n + 1));
      for (ll z = 0; z < e; ++z) {
            dp[z].resize(m + 2);
            for (ll j = 0; j <= m + 1; ++j) {
                  dp[z][j].resize(n + 2);
            }
      }

      sos[0] = 0;
      dp[0][0][0] = 1;
      ll sum = 0;
      for (ll i = 0; i < m; ++i) {
            for (ll j = 0; j < n; ++j) {
                  for (ll z = 0; z < e; ++z) {
                        for (ll b = 0; b <= 1; ++b) {
                              if (j == 0 || ((z>>(j-1))&7) != b * 7 || i == 0) {
                                    ll q = ((z & ~(1 << j)) | (b<<j));
                                    dp[q][i][j + 1] += dp[z][i][j];
                              }
                        }
                  }
            }
      sum = 0;
            for (ll z = 0; z < e; ++z) {
                  ll q = ((z & (~(1<<(n))))<< 1);
                  dp[q][i + 1][0] += dp[z][i][n];
                  sum += dp[z][i][n];
            }
      }
      cout << sum <<endl;
}

