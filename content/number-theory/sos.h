/**
 * Author: Anonymous
 * Description: sos dp
 */
vector<int> sos_dp(const vector<int>& A) {
    int n = __builtin_ctz(A.size());
    vector<int> F(A.begin(), A.end());
    for(int i = 0; i < n; ++i) {
        for(int mask = 0; mask < (1 << n); ++mask) {
            if(mask & (1 << i)) {
                F[mask] += F[mask ^ (1 << i)];
            }
        }
    }
    return F;
}