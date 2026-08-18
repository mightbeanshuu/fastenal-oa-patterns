// ============================================================================
// 4A — LINEAR SCAN WITH RUNNING STATE        (the warm-up slot — bank it fast)
// ============================================================================
// One confirmed Fastenal paper's cheap question was literally "find the largest
// element in the array". There is a cheap question in EVERY paper. Find it,
// bank it in 3 minutes, and spend the saved time on the hard slot.
//
// THE SHAPE : carry one or two variables across a single pass.
//     best = a[0];  for (x : a) best = max(best, x);
//
// TRAP : initialise from a[0], never from 0 — negatives break a 0 seed.
// TRAP : "second largest" needs strict inequality or duplicates fool it.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

int largestElement(const vector<int>& a) {
    int best = a[0];                          // NOT 0
    for (int x : a) best = max(best, x);
    return best;
}

// second largest DISTINCT value, or INT_MIN if there is none
int secondLargest(const vector<int>& a) {
    long long b1 = LLONG_MIN, b2 = LLONG_MIN;
    for (int x : a) {
        if (x > b1)      { b2 = b1; b1 = x; }
        else if (x < b1 && x > b2) b2 = x;    // strict < b1 skips duplicates
    }
    return b2 == LLONG_MIN ? INT_MIN : (int)b2;
}

// running state can be richer: best profit from one buy/sell (LC 121)
int maxProfit(const vector<int>& p) {
    int cheapest = INT_MAX, best = 0;
    for (int x : p) { best = max(best, x - cheapest); cheapest = min(cheapest, x); }
    return best;
}

// check sorted / count of pairs / prefix max — all the same single pass
bool isSorted(const vector<int>& a) {
    for (int i = 1; i < (int)a.size(); i++) if (a[i] < a[i-1]) return false;
    return true;
}

// TIME O(n)   SPACE O(1)
// ---------------------------------------------------------------------------
int main() {
    assert(largestElement({-5,-2,-9}) == -2);
    assert(largestElement({3,3,3})    == 3);
    assert(secondLargest({5,5,4,2})   == 4);
    assert(secondLargest({7,7,7})     == INT_MIN);
    assert(maxProfit({7,1,5,3,6,4})   == 5);
    assert(maxProfit({7,6,4,3,1})     == 0);
    assert(isSorted({1,2,2,3}) && !isSorted({2,1}));
    puts("4a  linear scan             OK");
}
