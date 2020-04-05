#include<iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
const int MAXN = 100009;
const ll INF = 1e18;
int n;
pair<ll, ll> a[MAXN];
pair<ll, ll> temp[MAXN];
ll ans = INF;
// sort for y
bool cmp (const pair<ll, ll> & x, const pair<ll, ll> & y) {
    return x.second < y.second;
}
// distance between a, b
ll dist(pair<ll, ll> a, pair<ll, ll> b) {
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}
// PRE: temp [l..  m] and temp[m + 1.. r] sorted for y
// POST: temp[l .. r] sorted for y and a[l..r] = temp[l..r]
void uni(int l, int m, int r) {
    int it1 = l, it2 = m + 1;
    int cur_ind = 0;
    while (it1 <= m || it2 <= r) {
        if (it2 != r + 1 && (it1 == m + 1 || a[it1].second > a[it2].second)) {
            temp[cur_ind] = a[it2];
            ++it2;
        } else {
            temp[cur_ind] = a[it1];
            ++it1;
        }
        cur_ind++;
    }
    for (ll i = l; i <= r; ++i) {
        a[i] = temp[i - l];
    }
}

// MEET IN THE MIDDLE
void comp(ll & ans, int l, int r) {
    // Calc for few points
    if (r <= l + 4) {
        for (int i = l; i <= r; ++i) {
            for (int j = i + 1; j <= r; ++j) {
                ans = min(ans, dist(a[i], a[j]));
            }
        }
        stable_sort(a + l, a + r + 1, cmp);
    } else {
        int m = (r - l) / 2 + l;
        int middle = a[m].first;
        int cur_index = 0;
        comp(ans, l, m); // left half
        comp(ans, m + 1, r); // right half
        uni(l, m, r); // sort a[l..r] for y
        for (int i = l; i <= r; ++i) {
            if (ans > abs(middle - a[i].first)) {
                for (int j = cur_index - 1; j >= 0; --j) {
                    if (a[i].second - temp[j].second > ans) {
                        break; // cur_point higher than temp[j] more than ans
                    } else {
                        ans = min(ans, dist(a[i], temp[j])); // update
                    }
                }
                temp[cur_index] = a[i]; // stack elements which (ans > abs(middle - cur_point.x))
                ++cur_index;
            }
        }
    }
}

ll check() { // DEBUG
    ll res = INF;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (res > dist(a[i], a[j])) {
                res = dist(a[i], a[j]);
            }
        }
    }
    return res;
}

int main() {
   // int seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    //std::mt19937 g1 (seed1);
    ans = INF;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        cin >> a[i].second;
    }
    stable_sort(a, a + n); // sort for x and if x1 == x2 sort for y
    comp(ans, 0, n - 1);
    cout << ans  << endl;
}
/*
7
99 12
49 51
21 77
61 49
99 76
43 22
47 74
 */
