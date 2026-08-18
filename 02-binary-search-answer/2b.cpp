// ============================================================================
// 2B — BINARY SEARCH ON THE ANSWER : MAXIMISE THE MINIMUM
// ============================================================================
// TRIGGER WORDS : "largest minimum distance" · "maximise the smallest" ·
//                 "place k items as far apart as possible"
//
// SAME idea as 2A, MIRRORED — and the midpoint must be biased HIGH or you
// loop forever:
//     while (lo < hi) {
//         long long mid = lo + (hi - lo + 1) / 2;   // <-- the +1 is mandatory
//         if (can(mid)) lo = mid;                   // feasible -> try bigger
//         else          hi = mid - 1;
//     }
//     return lo;
//
// WHY THE +1 : with lo=3, hi=4 the floor midpoint is 3; if can(3) is true you
//              set lo=3 and nothing changes -> infinite loop. Ceiling fixes it.
//
// HOW TO PICK THE FORM, in one question:
//   "is a SMALLER answer still feasible?"  -> 2A form (hi = mid, floor mid)
//   "is a LARGER answer still feasible?"   -> 2B form (lo = mid, ceil mid)
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// Aggressive Cows / Magnetic Force Between Two Balls (LC 1552).
long long maxMinDistance(vector<int> pos, int k) {
    sort(pos.begin(), pos.end());                      // sorting is mandatory
    auto can = [&](long long d) {                      // can we place k cows d apart?
        int placed = 1;
        long long last = pos[0];
        for (int i = 1; i < (int)pos.size(); i++)
            if (pos[i] - last >= d) { placed++; last = pos[i]; }
        return placed >= k;
    };
    long long lo = 1, hi = pos.back() - pos.front();
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;        // ceil
        if (can(mid)) lo = mid;
        else          hi = mid - 1;
    }
    return lo;
}

// Split Array Largest Sum (LC 410) — a 2A-form problem that LOOKS like 2B.
// Read carefully: it minimises the maximum, so it uses the FLOOR midpoint.
long long splitArrayMinLargestSum(const vector<int>& a, int k) {
    auto can = [&](long long cap) {
        long long parts = 1, cur = 0;
        for (int x : a) {
            if (x > cap) return false;
            if (cur + x > cap) { parts++; cur = 0; }
            cur += x;
        }
        return parts <= k;
    };
    long long lo = *max_element(a.begin(), a.end());
    long long hi = accumulate(a.begin(), a.end(), 0LL);
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (can(mid)) hi = mid; else lo = mid + 1;
    }
    return lo;
}

// TIME O(n log(range))  (+ O(n log n) for the sort)   SPACE O(1)
// ---------------------------------------------------------------------------
int main() {
    assert(maxMinDistance({1,2,4,8,9}, 3) == 3);
    assert(maxMinDistance({1,2,3,4,7}, 3) == 3);
    assert(maxMinDistance({5,4,3,2,1,1000000000}, 2) == 999999999);
    assert(splitArrayMinLargestSum({7,2,5,10,8}, 2) == 18);
    puts("2b  BS on answer: maximise  OK");
}
