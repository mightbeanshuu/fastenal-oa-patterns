// ============================================================================
// 3B — SIEVE OF ERATOSTHENES (and the divisor / smallest-prime-factor sieves)
// ============================================================================
// TRIGGER WORDS : "all primes up to N" · "count primes" · "prime factorise many
//                 numbers" · "sum over all divisors"
//
// IDEA : instead of testing each number, cross out multiples. O(N log log N).
//
// THE PATTERN THAT ACTUALLY WINS FASTENAL POINTS is the divisor sieve at the
// bottom: for every d, walk its multiples. Total work sum(N/d) = O(N log N).
// That one loop is what turns GCD Sum (3c) from "impossible" into 30 lines.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

vector<int> primesUpTo(int n) {
    vector<char> comp(n + 1, 0);
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (!comp[i]) {
            primes.push_back(i);
            for (long long j = 1LL * i * i; j <= n; j += i) comp[j] = 1;  // start at i*i
        }
    }
    return primes;
}

// Smallest prime factor sieve -> O(log x) factorisation of ANY x <= n
vector<int> spfSieve(int n) {
    vector<int> spf(n + 1);
    iota(spf.begin(), spf.end(), 0);
    for (long long i = 2; i * i <= n; i++)
        if (spf[i] == i)
            for (long long j = i * i; j <= n; j += i)
                if (spf[j] == j) spf[j] = (int)i;
    return spf;
}
vector<int> factorise(int x, const vector<int>& spf) {
    vector<int> f;
    while (x > 1) { f.push_back(spf[x]); x /= spf[x]; }
    return f;
}

// THE DIVISOR SIEVE — the shape that carries GCD Sum
vector<int> divisorCount(int n) {
    vector<int> d(n + 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i) d[j]++;      // i divides j
    return d;
}

// Euler's totient for every value up to n (needed by 3c)
vector<long long> totientSieve(int n) {
    vector<long long> phi(n + 1);
    iota(phi.begin(), phi.end(), 0LL);
    for (int i = 2; i <= n; i++)
        if (phi[i] == i)                              // i is prime
            for (int j = i; j <= n; j += i) phi[j] -= phi[j] / i;
    return phi;
}

// TIME O(n log log n) / O(n log n) for the divisor sieve   SPACE O(n)
// ---------------------------------------------------------------------------
int main() {
    vector<int> p = primesUpTo(30);
    assert((p == vector<int>{2,3,5,7,11,13,17,19,23,29}));
    vector<int> spf = spfSieve(1000);
    assert((factorise(360, spf) == vector<int>{2,2,2,3,3,5}));
    vector<int> d = divisorCount(12);
    assert(d[12] == 6 && d[7] == 2 && d[1] == 1);
    vector<long long> phi = totientSieve(12);
    assert(phi[1] == 1 && phi[6] == 2 && phi[12] == 4 && phi[7] == 6);
    puts("3b  sieves                  OK");
}
