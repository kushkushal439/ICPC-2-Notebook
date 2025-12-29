/**
 * Author: Anonymous
 */
int MX = 1e7 + 1;
vi spf(MX + 1, INT32_MAX);
vector<int> is_prime(MX + 1, 1);
void sieve(int n = MX) {
  for (int i = 1; i <= n; i++) 
    spf[i] = i;
  is_prime[0] = is_prime[1] = 0;
  int cnt = 1;
  for (int i = 2; i <= n; i++) {
    if (is_prime[i]) {
      for (int j = i * i; j <= n; j += i) {
        is_prime[j] = 0;
        spf[j] = min(i, spf[j]);
      }
      is_prime[i] = cnt;
      cnt++;
    }
  }
  return;
}