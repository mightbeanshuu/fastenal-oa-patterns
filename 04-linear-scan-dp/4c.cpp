// ============================================================================
// 4C — 1-D DP : HOUSE ROBBER I  (LC 198)
// ============================================================================
// TRIGGER WORDS : "no two adjacent may be chosen" · "cannot pick neighbours"
//
// RECURRENCE : dp[i] = max( dp[i-1],            skip house i
//                           dp[i-2] + a[i] )    rob house i
//
// ROLLING VARIABLES — this is the form to write in an OA, it is O(1) space:
//     prev2 = 0, prev1 = 0
//     for x in a:  cur = max(prev1, prev2 + x); prev2 = prev1; prev1 = cur
//     return prev1
//
// TRAP : the update order. prev2 must receive the OLD prev1, so compute cur
//        first, then shift. Doing it inline in the wrong order silently gives
//        the wrong answer on inputs longer than 3.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

long long rob(const vector<int>& a) {
    long long prev2 = 0, prev1 = 0;
    for (int x : a) {
        long long cur = max(prev1, prev2 + x);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

// same thing with an explicit table, in case the interviewer asks for it
long long robTable(const vector<int>& a) {
    int n = (int)a.size();
    if (n == 0) return 0;
    vector<long long> dp(n);
    dp[0] = a[0];
    for (int i = 1; i < n; i++)
        dp[i] = max(dp[i-1], (i >= 2 ? dp[i-2] : 0LL) + a[i]);
    return dp[n-1];
}

// TIME O(n)   SPACE O(1)
// ---------------------------------------------------------------------------
int main() {
    assert(rob({1,2,3,1}) == 4);
    assert(rob({2,7,9,3,1}) == 12);
    assert(rob({}) == 0);
    assert(rob({5}) == 5);
    for (vector<int> t : {vector<int>{1,2,3,1}, {2,7,9,3,1}, {2,1,1,2}})
        assert(rob(t) == robTable(t));
    puts("4c  house robber I          OK");
}
