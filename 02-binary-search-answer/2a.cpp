// ============================================================================
// 2A — BINARY SEARCH ON THE ANSWER : MINIMISE THE MAXIMUM
// ============================================================================
// *** The single highest-confidence prediction for the hard slot. Four
// *** independent sightings across three years. Drill this until it is reflex.
//
// TRIGGER WORDS : "minimum time" · "smallest speed/capacity" · "least number
//                 of days" · "minimum largest ..." — the thing being minimised
//                 is NOT an element of the array, it is a number you invent.
//
// THE INSIGHT : you are not searching the array. You are searching the ANSWER
//               SPACE [lo, hi]. Define a predicate
//                     can(mid) = "is mid a feasible answer?"
//               If can() is monotone (false false false TRUE TRUE TRUE) you can
//               binary search for the first TRUE.
//
// THE TEMPLATE — memorise this exact form, it never needs a +1:
//     long long lo = <smallest conceivable>, hi = <definitely feasible>;
//     while (lo < hi) {
//         long long mid = lo + (hi - lo) / 2;      // floor, biased LOW
//         if (can(mid)) hi = mid;                  // feasible -> maybe smaller
//         else          lo = mid + 1;              // infeasible -> must grow
//     }
//     return lo;                                   // lo == hi == first TRUE
//
// TRAPS : hi must be a value that is certainly feasible, or you return garbage.
//         Use long long for mid and for anything you multiply.
//         mid = lo + (hi-lo)/2, never (lo+hi)/2 — that overflows.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// Koko Eating Bananas (LC 875): smallest speed that finishes within h hours.
long long minEatingSpeed(const vector<int>& piles, long long h) {
    auto can = [&](long long speed) {
        long long hours = 0;
        for (int p : piles) hours += (p + speed - 1) / speed;   // ceil division
        return hours <= h;
    };
    long long lo = 1, hi = *max_element(piles.begin(), piles.end());  // hi is feasible
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (can(mid)) hi = mid;
        else          lo = mid + 1;
    }
    return lo;
}

// Capacity to Ship Packages in D Days (LC 1011): identical skeleton.
long long shipCapacity(const vector<int>& w, long long days) {
    auto can = [&](long long cap) {
        long long need = 1, cur = 0;
        for (int x : w) {
            if (x > cap) return false;              // one item cannot fit at all
            if (cur + x > cap) { need++; cur = 0; }
            cur += x;
        }
        return need <= days;
    };
    long long lo = *max_element(w.begin(), w.end());
    long long hi = accumulate(w.begin(), w.end(), 0LL);
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (can(mid)) hi = mid; else lo = mid + 1;
    }
    return lo;
}

// TIME O(n log(range))   SPACE O(1)
// ---------------------------------------------------------------------------
int main() {
    assert(minEatingSpeed({3,6,7,11}, 8) == 4);
    assert(minEatingSpeed({30,11,23,4,20}, 5) == 30);
    assert(minEatingSpeed({312884470}, 968709470) == 1);
    assert(shipCapacity({1,2,3,4,5,6,7,8,9,10}, 5) == 15);
    assert(shipCapacity({3,2,2,4,1,4}, 3) == 6);
    puts("2a  BS on answer: minimise  OK");
}
