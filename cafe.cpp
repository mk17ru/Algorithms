#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const long long maxn = 200;
const long long inf = 1e17;
long long n;
long long dp[maxn][maxn];
pair<long long, long long> pred[maxn][maxn];
long long x, y;
vector<long long> ans;
long long a[200];
int main() {
      cin >> n;
      for (long long i = 0; i <= n + 10; ++i)
            for (long long j = 0; j <= n + 10; ++j)
                  dp[i][j] = inf;
      dp[0][0] = 0;
      for (long long i = 1; i <= n; ++i) {
            cin >> a[i];
            long long x = a[i];
            for (long long j = 0; j <= n; ++j) {
                  if (x > 100) {
                        if (j > 0)
                        if (dp[i][j] > dp[i - 1][j - 1] + x) {
                              dp[i][j] = dp[i - 1][j - 1] + x;
                              pred[i][j] = {i - 1, j - 1};
                        }
                  }
                  else {
                        if (dp[i][j] > dp[i - 1][j] + x) {
                              dp[i][j] = dp[i - 1][j] + x;
                              pred[i][j] = {i - 1, j};
                        }
                       // dp[i][j] = min(dp[i - 1][j] + x, dp[i][j]);
                  }
                        if (dp[i][j] > dp[i - 1][j + 1]) {
                              dp[i][j] = dp[i - 1][j + 1];
                              pred[i][j] = {i - 1, j + 1};
                        }
                        //dp[i][j - 1] = min(dp[i][j - 1], dp[i - 1][j]);
            }
      }
      long long min1 = 1e18, j = 0;
      for (long long i = 0; i <= n; ++i) {
            if (dp[n][i] <= min1) {
                  min1 = dp[n][i];
                  j = i;
            }
      }
      cout << min1 <<endl;
      cout << j<<" ";
      pair<long long, long long> h = {n, j};
      while (h.first != 0) {
            long long i = h.first, j = h.second;
            if (a[i] > 100) {
                 if (j > 0) {
                  if (dp[i][j] == dp[i - 1][j - 1] + a[i]) {
                        h = {i - 1,j - 1};
                  }
                 }
            }
            else {
                  if (dp[i][j] == dp[i - 1][j] + a[i]) {
                        h = {i - 1,j};
                  }
            }
                  if (dp[i][j] == dp[i - 1][j + 1]) {
                        h = {i - 1,j + 1};
                        ans.pb(i);
                  }
      }
      cout << (long long)ans.size()<<endl;
      reverse(ans.begin(), ans.end());
      for (auto p : ans) {
            cout << p <<endl;
      }
}
