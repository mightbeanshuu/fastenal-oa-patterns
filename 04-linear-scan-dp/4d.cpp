// ============================================================================
// 4D — HOUSE ROBBER II : the circular cut  (LC 213)
// ============================================================================
// TRIGGER WORDS : House Robber I's wording PLUS "the houses are arranged in a
//                 circle" / "the first and last are adjacent".
//
// THE WHOLE TRICK : house 0 and house n-1 can never both be taken. So there are
//                   exactly two worlds:
//                       A) allow 0 .. n-2      (drop the last)
//                       B) allow 1 .. n-1      (drop the first)
//                   Answer = max(A, B). Call the linear solver twice.
//
// TRAP : n == 1 must be handled before slicing, or both ranges are empty and
//        you return 0 instead of a[0].
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// the 4C routine, on a half-open index range [lo, hi)
static long long robRange(const vector<int>& a, int lo, int hi) {
    long long prev2 = 0, prev1 = 0;
    for (int i = lo; i < hi; i++) {
        long long cur = max(prev1, prev2 + a[i]);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

long long robCircular(const vector<int>& a) {
    int n = (int)a.size();
    if (n == 0) return 0;
    if (n == 1) return a[0];                 // the trap
    return max(robRange(a, 0, n - 1),        // drop the last house
               robRange(a, 1, n));           // drop the first house
}

// TIME O(n)   SPACE O(1)
// ---------------------------------------------------------------------------
int main() {
    assert(robCircular({2,3,2}) == 3);       // cannot take both 2s
    assert(robCircular({1,2,3,1}) == 4);
    assert(robCircular({1,2,3}) == 3);
    assert(robCircular({5}) == 5);           // n == 1
    assert(robCircular({}) == 0);
    assert(robCircular({200,3,140,20,10}) == 340);
    puts("4d  house robber II         OK");
}
