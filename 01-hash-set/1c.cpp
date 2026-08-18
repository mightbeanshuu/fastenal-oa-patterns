// ============================================================================
// 1C — PREFIX SUM + HASH MAP          (Fastenal corpus: Longest Subarray Sum K)
// ============================================================================
// TRIGGER WORDS : "subarray whose sum is exactly K" · "count subarrays with
//                 sum K" · "longest subarray with sum K"  AND negatives allowed
//
// WHY NOT A SLIDING WINDOW : a window only works when growing it can never
//                 decrease the sum, i.e. all values >= 0. The moment negatives
//                 are allowed, shrinking is not a valid repair. Use prefix sums.
//
// THE IDENTITY :   sum(l..r) = pre[r] - pre[l-1]
//                  sum(l..r) = K   <=>   pre[l-1] = pre[r] - K
//        So while scanning r, ask the map: have I ever seen prefix (cur - K)?
//
// TWO DIFFERENT MAPS — do not confuse them:
//        LONGEST  -> map stores prefix -> EARLIEST index   (insert only if absent)
//        COUNT    -> map stores prefix -> how many times seen (always ++)
//
// TRAP : seed the map with prefix 0 (index -1 / count 1) or you miss every
//        subarray that starts at index 0.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// Longest subarray with sum exactly k (works with negatives and zeros)
int longestSubarraySumK(const vector<int>& a, long long k) {
    unordered_map<long long,int> first;      // prefix sum -> EARLIEST index
    first[0] = -1;                           // empty prefix ends before index 0
    long long cur = 0;
    int best = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        cur += a[i];
        auto it = first.find(cur - k);
        if (it != first.end()) best = max(best, i - it->second);
        if (!first.count(cur)) first[cur] = i;   // keep the EARLIEST only
    }
    return best;
}

// Count of subarrays with sum exactly k  (LC 560)
int countSubarraysSumK(const vector<int>& a, long long k) {
    unordered_map<long long,int> seen;       // prefix sum -> how many times
    seen[0] = 1;
    long long cur = 0;
    int res = 0;
    for (int x : a) {
        cur += x;
        auto it = seen.find(cur - k);
        if (it != seen.end()) res += it->second;
        seen[cur]++;
    }
    return res;
}

// Same skeleton, different key: longest subarray with equal 0s and 1s
// (map 0 -> -1 and the problem becomes "longest subarray with sum 0")
int longestEqualZeroOne(const vector<int>& a) {
    unordered_map<int,int> first{{0,-1}};
    int cur = 0, best = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        cur += (a[i] == 0 ? -1 : 1);
        auto it = first.find(cur);
        if (it != first.end()) best = max(best, i - it->second);
        else first[cur] = i;
    }
    return best;
}

// TIME O(n) average   SPACE O(n)
// ---------------------------------------------------------------------------
int main() {
    assert(longestSubarraySumK({10,5,2,7,1,9}, 15) == 4);   // 5 2 7 1
    assert(longestSubarraySumK({-1,1,1},        1) == 3);   // needs negatives
    assert(longestSubarraySumK({1,2,3},        10) == 0);
    assert(countSubarraysSumK({1,1,1}, 2) == 2);
    assert(countSubarraysSumK({1,-1,0}, 0) == 3);
    assert(longestEqualZeroOne({0,1,0,1,1,0}) == 6);
    puts("1c  prefix sum + hash map   OK");
}
