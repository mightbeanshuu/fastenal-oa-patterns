// ============================================================================
// 3C — GCD SUM              *** the only HARD in the corpus. Brute force = 0. ***
// ============================================================================
// STATEMENT : compute  sum over all pairs 1 <= i < j <= N  of  gcd(i, j).
//
// WHY BRUTE FORCE SCORES ZERO : N is large; the double loop is O(N^2 log N).
//                 This is the ONE problem in the corpus where a brute force
//                 provably fails every test. It is sieve or nothing.
//
// THE DERIVATION (know it, they reopen OA problems in the interview):
//   Count pairs whose gcd is exactly d. Write i = d*a, j = d*b with gcd(a,b)=1
//   and a < b <= N/d. The number of such coprime pairs with m = N/d is
//       C(m) = sum_{b=2..m} phi(b)
//   So  answer = sum_{d=1..N}  d * C(N/d).
//
// TWIST : the answer overflows int32 immediately. long long everywhere.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

long long gcdSum(int n) {
    if (n < 2) return 0;
    // phi[1..n]
    vector<long long> phi(n + 1);
    iota(phi.begin(), phi.end(), 0LL);
    for (int i = 2; i <= n; i++)
        if (phi[i] == i)
            for (int j = i; j <= n; j += i) phi[j] -= phi[j] / i;

    // C[m] = number of coprime pairs (a,b) with 1 <= a < b <= m
    vector<long long> C(n + 1, 0);
    for (int b = 2; b <= n; b++) C[b] = C[b-1] + phi[b];

    long long ans = 0;
    for (int d = 1; d <= n; d++) ans += 1LL * d * C[n / d];
    return ans;
}

// O(n^2 log n) reference, used only to prove the fast version on small n.
long long gcdSumBrute(int n) {
    long long s = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) s += __gcd(i, j);
    return s;
}

// TIME O(n log log n)   SPACE O(n)
// ---------------------------------------------------------------------------
int main() {
    for (int n = 1; n <= 200; n++) assert(gcdSum(n) == gcdSumBrute(n));
    assert(gcdSum(4) == 7);                 // 1+1+1+2+1+1
    assert(gcdSum(1000000) > 2147483647LL); // overflow proof
    puts("3c  GCD Sum                 OK   (the corpus Hard)");
}
