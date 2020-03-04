#include<bits/stdc++.h>
#define ld long doble
#define pb push_back
using namespace std;
const long long maxn = 160000;
long long n, k;
long long st[maxn][32];
long long a[maxn];
void build() {
      for (long long i = 0; i < n; ++i) {
            st[i][0] = a[i];
      }
      for (long long j = 1; ((long long)1<<j) <= n; ++j) {
            for (long long i = 0; (i + (1 << j) - 1) < n; ++i) {
                  if (st[i][j - 1] < st[i + (1 << (j - 1))][j - 1]) {
                        st[i][j] = st[i][j - 1];
                  } else st[i][j] = st[i + (1 << (j - 1))][j - 1];
            }
      }
}
long long mint(long long L, long long R) {
      long long j = (long long)log2(R - L + 1);
      return min(st[L][j], st[R - (1 <<j) + 1][j]);
}
int main() {
      ios::sync_with_stdio(0); cin.tie(0);
      cin >> n >> k;
      for (long long i = 0; i < n; ++i)
            cin >> a[i];

      build();

      for (long long i = 0; i < n - k + 1; ++i) {
            cout << mint(i, i + k - 1) <<endl;
      }
      return 0;
}
