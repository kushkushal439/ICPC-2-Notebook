mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int a, int b) {
  if (a > b) return 0;
  return a + rng() % (b - a + 1);
}
double random_double(double a, double b) {
  return a + (b - a) * (rng() / (double)rng.max());
}