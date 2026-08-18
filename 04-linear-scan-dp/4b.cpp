// ============================================================================
// 4B — KADANE : MAXIMUM SUBARRAY SUM
// ============================================================================
// TRIGGER WORDS : "maximum sum of a contiguous subarray" · "best consecutive
//                 stretch" (contiguous is the keyword; if it says subsequence,
//                 this is the wrong tool)
//
// THE IDEA : at each index, the best subarray ENDING here either extends the
//            previous one or restarts at this element.
//                cur = max(x, cur + x);   best = max(best, cur);
//
// TRAP : all-negative input. Seeding best = 0 returns 0, which is wrong unless
//        the statement allows an empty subarray. Seed best = a[0].
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

long long maxSubarraySum(const vector<int>& a) {
    long long cur = a[0], best = a[0];        // seed from a[0], not 0
    for (int i = 1; i < (int)a.size(); i++) {
        cur = max((long long)a[i], cur + a[i]);
        best = max(best, cur);
    }
    return best;
}

// variant they like: also report the indices
tuple<long long,int,int> maxSubarrayWithBounds(const vector<int>& a) {
    long long cur = a[0], best = a[0];
    int s = 0, bl = 0, br = 0;
    for (int i = 1; i < (int)a.size(); i++) {
        if (cur + a[i] < a[i]) { cur = a[i]; s = i; }    // restart here
        else cur += a[i];
        if (cur > best) { best = cur; bl = s; br = i; }
    }
    return {best, bl, br};
}

// circular version (needed by 4d's mental model): answer is either the normal
// Kadane max, or total - (minimum subarray sum).
long long maxCircularSubarraySum(const vector<int>& a) {
    long long total = 0, curMax = a[0], bestMax = a[0], curMin = a[0], bestMin = a[0];
    for (int i = 0; i < (int)a.size(); i++) {
        total += a[i];
        if (i) {
            curMax = max((long long)a[i], curMax + a[i]); bestMax = max(bestMax, curMax);
            curMin = min((long long)a[i], curMin + a[i]); bestMin = min(bestMin, curMin);
        }
    }
    if (bestMax < 0) return bestMax;          // all negative -> wrap is illegal
    return max(bestMax, total - bestMin);
}

// TIME O(n)   SPACE O(1)
// ---------------------------------------------------------------------------
int main() {
    assert(maxSubarraySum({-2,1,-3,4,-1,2,1,-5,4}) == 6);
    assert(maxSubarraySum({-3,-1,-7}) == -1);           // the all-negative trap
    auto [v,l,r] = maxSubarrayWithBounds({-2,1,-3,4,-1,2,1,-5,4});
    assert(v == 6 && l == 3 && r == 6);
    assert(maxCircularSubarraySum({5,-3,5}) == 10);
    assert(maxCircularSubarraySum({-3,-2,-3}) == -2);
    puts("4b  kadane                  OK");
}
