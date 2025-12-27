/*
* Author: Anonymous
* Description: dnc dp with cost func
*/
auto add = [&](int v) {
    cnt[a[v]]++;
    ans += cnt[a[v]] - 1;
};
auto rem = [&](int v) {
    cnt[a[v]]--;
    ans -= cnt[a[v]];
};

auto getcost = [&](int expl, int expr) {
    while (l > expl) add(--l);
    while (l < expl) rem(l++);
    while (r < expr) add(++r);
    while (r > expr) rem(r--);
    return ans;
};

function<void(int, int, int, int)> calc = [&] (int l, int r, int optl, int optr) {
    if (l > r) return;
    int mid = (l + r) / 2;
    array<int, 2> best = {LLONG_MAX, -1};
    for (int i = optl; i <= min(mid, optr); i++) {
        int inval = dp1[i] + getcost(i, mid);
        array<int, 2> cur = {inval, i};
        best = min(best, cur);
    }
    int opt = best[1];
    dp2[mid + 1] = best[0];
    calc(l, mid - 1, optl, opt);
    calc(mid + 1, r, opt, optr);
};
fr(i, 0, k) {
    calc(0, n-1, 0, n-1);
    dp1 = dp2;
    dp2 = vi(n+1, 1e15);
}
cout << dp1[n] << endl;