#include <bits/stdc++.h>

using namespace std;

struct Turple {
    int a, b, c;
    void in () {
        scanf("%d %d %d", & a, & b, & c);
        a--;
        b--;
        c--;
    }
}
ban[4100];

const int N = 16;
int dp[1 << N], previous_mask[1 << N], ans[N];
bool frees[1 << N];

bool ok(int msk, int x) {
    return (1 << x) & msk;
}

int main() {
    freopen("districts.in", "r", stdin);
    freopen("districts.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        ban[i].in();
    }
    int bit = 1 << n;
    for (int msk = 0; msk < bit; msk++) {
        frees[msk] = true;
        if (msk) {
            dp[msk] = 1e6;
        }
        for (int i = 0; i < m; i++) {
            if (ok(msk, ban[i].a) && ok(msk, ban[i].b) && ok(msk, ban[i].c)) {
                frees[msk] = false;
            }
        }
    }
    for (int msk = 1; msk < bit; msk++) {
        for (int s = msk; s; s = (s - 1) & msk) {
            if (frees[s] && dp[msk] > dp[msk ^ s] + 1) {
                dp[msk] = dp[msk ^ s] + 1;
                previous_mask[msk] = s;
            }
        }
    }
    cout << dp[bit - 1] << endl;
    int current_state = bit - 1, location = 1;
    while (current_state) {
        for (int i = 0; i < n; i++) {
            if ((1 << i) & previous_mask[current_state]) {
                ans[i] = location;
            }
        }
        current_state ^= previous_mask[current_state];
        location++;
    }
    for (int i = 0; i < n; i++) {
        printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
    }
    return 0;
}