#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define pb push_back
using namespace std;
using namespace __gnu_pbds;

const long long maxn = 5 * 1e5;
long long n, kol, l, zap, zap1, c1, c2; string s;

unordered_map<string, long long> mp;
unordered_map<long long, string> mp1;

tree<long long, nulong long_type, less<long long>, rb_tree_tag, tree_order_statistics_node_update> mn;
stack<long long> st;
vector<long long> ans;
bool f =true;

unordered_multiset<long long> a[maxn], b[maxn];
string sos, s1, s2;

int main() {

      #ifdef DEBUG
        freopen("input.txt", "r", stdin);
      #endif // DEBUG
      cin >> n;
      for (long long i = 1; i <= n; ++i) {
            cin >> s;
            s1 = ""; s2 = "";
            s1 += s[0];
            s1 += s[1];
            if (mp[s1] == 0) {
                  ++l;
                  mp[s1] = l;
                  mp1[l] = s1;
            }
            s2 += s[1];
            s2 += s[2];
            if (mp[s2] == 0) {
                  ++l;
                  mp[s2] = l;
                  mp1[l] = s2;
            }
            a[mp[s1]].insert(mp[s2]);
            b[mp[s2]].insert(mp[s1]);
      }
      f = true;
      for (long long i = 1; i <= l; ++i) {
            if ((long long)a[i].size() + 1 < (long long)b[i].size()) {
                  cout << "NO" << endl;
                  return 0;
            }
            if ((long long)a[i].size() > (long long)b[i].size() + 1) {
                  cout << "NO" << endl;
                  return 0;
            }
            if ((long long)a[i].size() + 1 == (long long)b[i].size()) {
                  c1++;
            }
            if ((long long)a[i].size() == (long long)b[i].size() + 1) {
                  zap = i;
                  c2++;
            }

      }

      if ((c1 > 1) || (c2 > 1)) {
            cout << "NO" <<endl;
            return 0;
      }
      if (c1 != c2) {
            cout << "NO" <<endl;
            return 0;
      }
      if (zap == 0) {
            for (long long i = 1; i <= l; ++i)
                  if (a[i].size() > 0) {
                        zap = i;
                        break;
                  }
      }
      st.push(zap);
      while (!st.empty()) {
            long long u = st.top();
            bool f1 = true;
            if (a[u].size() == 0) {
                  ans.pb(u);
                  st.pop();
                  continue;
            }
            for (auto p : a[u]) {
                //  cout << p << endl;
                  st.push(p);
                  a[u].erase(a[u].find(p));
                  f1 = false;
                  break;
            }

      }
      if (ans.size() != n + 1) {
            cout << "NO" <<endl;
            return 0;
      }
      cout << "YES" <<endl;
      reverse(ans.begin(), ans.end());
      cout << mp1[ans[0]][0]<< mp1[ans[0]][1];
      for (long long i = 1; i < ans.size(); ++i) {
            cout << mp1[ans[i]][1];
      }

}
