# Family 3 — Number theory
**3 sightings.** GCD Sum · Sieve of Eratosthenes · HCF.

## Files
| File | Content |
|---|---|
| `3a.cpp` | Euclid (iterative + recursive), lcm, gcd of an array |
| `3b.cpp` | prime sieve · smallest-prime-factor sieve · **divisor sieve** · totient sieve |
| `3c.cpp` | **GCD Sum** — the only Hard in the corpus, verified against brute force for n ≤ 200 |

## The piece that actually wins points
The **divisor sieve**: for every `d`, walk its multiples. Total work `Σ N/d = O(N log N)`.
That single loop is what turns GCD Sum from impossible into 30 lines.

## GCD Sum, derived (they reopen OA problems in the interview)
Count pairs whose gcd is exactly `d`. Write `i = d·a`, `j = d·b` with `gcd(a,b)=1`, `a < b ≤ N/d`.
The number of coprime pairs up to `m` is `C(m) = Σ_{b=2..m} φ(b)`.
So **`answer = Σ_{d=1..N} d · C(N/d)`**.

## The traps
- **GCD Sum is the one problem where brute force provably scores 0/120.** Everywhere else, write the brute force. Not here.
- The answer overflows int32 immediately — `long long`.
- `lcm(a,b) = a / gcd(a,b) * b` — **divide first** or you overflow.
- `__gcd` is a GNU extension: fine on the OA, absent in Apple clang.
