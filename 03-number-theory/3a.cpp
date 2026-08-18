// ============================================================================
// 3A — GCD / EUCLID / LCM
// ============================================================================
// TRIGGER WORDS : gcd · hcf · lcm · "reduce the fraction" · "co-prime"
//
// EUCLID, one line, memorise it:   while (b) { t = a % b; a = b; b = t; }
//
// TRAP : __gcd(a,b) is a GNU extension. It exists on the OA's g++ 9.2.0 but NOT
//        in Apple clang's libc++ — a local failure there is the toolchain, not
//        you. std::gcd (<numeric>, C++17) is portable. Hand-rolling is safest.
// TRAP : lcm(a,b) = a / gcd(a,b) * b  — divide FIRST or you overflow.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

long long gcdIter(long long a, long long b) {
    while (b) { long long t = a % b; a = b; b = t; }
    return a < 0 ? -a : a;
}
long long gcdRec(long long a, long long b) { return b ? gcdRec(b, a % b) : (a < 0 ? -a : a); }
long long lcmSafe(long long a, long long b) { return a / gcdIter(a, b) * b; }   // divide first

long long gcdOfArray(const vector<long long>& v) {
    long long g = 0;                        // gcd(0, x) == x, so 0 is the identity
    for (long long x : v) g = gcdIter(g, x);
    return g;
}

// TIME O(log min(a,b))   SPACE O(1)
// ---------------------------------------------------------------------------
int main() {
    assert(gcdIter(12, 18) == 6);
    assert(gcdIter(0, 5)   == 5);
    assert(gcdRec(270, 192) == 6);
    assert(lcmSafe(4, 6) == 12);
    assert(lcmSafe(1000000000LL, 999999999LL) == 999999999000000000LL);
    assert(gcdOfArray({12, 18, 30}) == 6);
    assert(__gcd(12, 18) == 6);             // compiles on the OA; shimmed locally
    puts("3a  gcd / euclid / lcm      OK");
}
