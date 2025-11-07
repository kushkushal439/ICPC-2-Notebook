// Computes the GCD convolution of two sequences a and b modulo mod.
// c[k] = sum_{gcd(i, j) = k} a[i] * b[j]
template<typename T>
std::vector<T> gcdConvolution(const std::vector<T>& a, const std::vector<T>& b, T mod) {
    int n = a.size();
    std::vector<T> A(n, 0), B(n, 0), D(n, 0), result(n, 0);

    // Step 1: Compute Dirichlet prefix sums over divisors
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; j += i + 1) {
            A[i] = (A[i] + a[j]) % mod;
            B[i] = (B[i] + b[j]) % mod;
        }
        D[i] = (A[i] * B[i]) % mod;
    }

    // Step 2: Möbius inversion to compute GCD convolution
    for (int i = n - 1; i >= 0; --i) {
        result[i] = D[i];
        for (int j = 2 * i + 1; j < n; j += i + 1) {
            result[i] = (result[i] - result[j] + mod) % mod;
        }
    }

    return result;
}