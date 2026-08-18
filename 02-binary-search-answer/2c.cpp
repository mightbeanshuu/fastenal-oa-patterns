// ============================================================================
// 2C — DELIVER FASTENERS        *** FASTENAL ORIGINAL — seen 2022 AND 2023 ***
// ============================================================================
// This is the only proof of question-bank reuse in the whole corpus. It is the
// single most likely named problem in the hard slot. Learn it cold.
//
// STATEMENT : N trucks. Truck i has speed S[i]. A truck that delivers x boxes
//             takes  F(x) = S * (x*x - x + 1)  units of time. All trucks work
//             in parallel. Deliver `total` boxes; minimise the completion time
//             (i.e. the maximum time taken by any single truck).
//
// SHAPE : minimise-the-maximum -> 2A template, hi = mid, floor midpoint.
//         can(T) = "can all trucks together move >= total boxes within T?"
//         Per truck, the most boxes within T is the largest x with
//         S*(x^2 - x + 1) <= T. Find it with an inner binary search (or the
//         quadratic formula; the inner search is safer under exam pressure).
//
// *** TWIST 1 *** x = 0 must cost 0, but the raw formula gives F(S,0) = S.
//                 Every idle truck would otherwise inflate the answer. Special-
//                 case it.
// *** TWIST 2 *** the answer reaches 99,999,000,010 — about 46x past int32 —
//                 and x*x overflows far earlier. Use long long EVERYWHERE,
//                 even though the OA signature returns int.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// boxes a truck of speed s can deliver within time T
static long long boxesWithin(long long s, long long T) {
    if (T < s) return 0;                       // cannot even manage x = 1
    long long lo = 0, hi = 2000000000LL;       // generous upper bound on x
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;          // maximise x -> ceil
        // careful: mid*mid can be astronomically large, so bound it first
        if (mid > 3000000000LL) { hi = mid - 1; continue; }
        long long cost = s * (mid * mid - mid + 1);
        if (cost <= T) lo = mid; else hi = mid - 1;
    }
    return lo;
}

// ---- Read only region start -------------------------------------------------
// int deliverFasteners(int input1, int input2, int input3[])
//   input1 = number of trucks N, input2 = total boxes, input3 = speeds
// ---- Read only region end ---------------------------------------------------
long long deliverFasteners(int n, long long total, const vector<long long>& speed) {
    auto can = [&](long long T) {
        long long done = 0;
        for (int i = 0; i < n; i++) {
            done += boxesWithin(speed[i], T);
            if (done >= total) return true;    // early exit, also stops overflow
        }
        return done >= total;
    };

    long long lo = 0;
    // hi: one truck (the fastest) does everything -> certainly feasible
    long long s = *min_element(speed.begin(), speed.end());
    long long hi = s * (total * total - total + 1);
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;    // minimise -> floor midpoint
        if (can(mid)) hi = mid;
        else          lo = mid + 1;
    }
    return lo;
}

// TIME O(n * log(answer) * log(x))   SPACE O(1)
// ---------------------------------------------------------------------------
int main() {
    // 1 truck, speed 1, 1 box:  F(1) = 1*(1-1+1) = 1
    assert(deliverFasteners(1, 1, {1}) == 1);
    // 2 trucks speed 1, 2 boxes: one each -> 1 each -> answer 1
    assert(deliverFasteners(2, 2, {1,1}) == 1);
    // 1 truck speed 1, 2 boxes: F(2) = 1*(4-2+1) = 3
    assert(deliverFasteners(1, 2, {1}) == 3);
    // 1 truck speed 5, 3 boxes: F(3) = 5*(9-3+1) = 35
    assert(deliverFasteners(1, 3, {5}) == 35);
    // twist 1: an idle truck must not cost anything
    assert(deliverFasteners(3, 1, {1, 1000000, 1000000}) == 1);
    // twist 2: the int32 blow-up case
    assert(deliverFasteners(1, 316228, {1}) > 2147483647LL);
    puts("2c  Deliver Fasteners       OK   (Fastenal original)");
}
