// ============================================================================
// 8C — MONOTONIC STACK : NEXT GREATER ELEMENT
// ============================================================================
// TRIGGER WORDS : "next greater / next smaller element" · "how many days until
//                 a warmer temperature" · "largest rectangle in a histogram" ·
//                 "span" — anything asking, for every index, about the NEAREST
//                 index on one side satisfying a comparison.
//
// THE IDEA : keep a stack whose values are strictly decreasing. When the
//     incoming value is larger, it is the answer for everything it beats — pop
//     them all. Each index is pushed once and popped once, so the whole thing
//     is O(n) despite the inner while.
//
// THE FOUR VARIANTS, all the same loop:
//     next greater  -> scan left->right, pop while top <= cur
//     next smaller  -> scan left->right, pop while top >= cur
//     prev greater  -> scan right->left, pop while top <= cur
//     prev smaller  -> scan right->left, pop while top >= cur
//
// TRAP : store INDICES, not values, whenever the answer is a distance.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

vector<int> nextGreater(const vector<int>& a) {      // -1 if none
    int n = (int)a.size();
    vector<int> res(n, -1);
    stack<int> st;                                    // indices, decreasing values
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) { res[st.top()] = a[i]; st.pop(); }
        st.push(i);
    }
    return res;
}

vector<int> dailyTemperatures(const vector<int>& t) { // distance version
    int n = (int)t.size();
    vector<int> res(n, 0);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && t[st.top()] < t[i]) { res[st.top()] = i - st.top(); st.pop(); }
        st.push(i);
    }
    return res;
}

// circular next greater (LC 503): walk the array twice, modulo n
vector<int> nextGreaterCircular(const vector<int>& a) {
    int n = (int)a.size();
    vector<int> res(n, -1);
    stack<int> st;
    for (int i = 0; i < 2*n; i++) {
        int k = i % n;
        while (!st.empty() && a[st.top()] < a[k]) { res[st.top()] = a[k]; st.pop(); }
        if (i < n) st.push(k);                        // only push on the first pass
    }
    return res;
}

long long largestRectangleHistogram(vector<int> h) {
    h.push_back(0);                                   // sentinel flushes the stack
    stack<int> st;
    long long best = 0;
    for (int i = 0; i < (int)h.size(); i++) {
        while (!st.empty() && h[st.top()] >= h[i]) {
            long long height = h[st.top()]; st.pop();
            long long left = st.empty() ? -1 : st.top();
            best = max(best, height * (i - left - 1));
        }
        st.push(i);
    }
    return best;
}

// TIME O(n) — each index is pushed and popped at most once.   SPACE O(n)
// ---------------------------------------------------------------------------
int main() {
    assert((nextGreater({4,5,2,10,8}) == vector<int>{5,10,10,-1,-1}));
    assert((nextGreater({3,2,1}) == vector<int>{-1,-1,-1}));
    assert((dailyTemperatures({73,74,75,71,69,72,76,73}) == vector<int>{1,1,4,2,1,1,0,0}));
    assert((nextGreaterCircular({1,2,1}) == vector<int>{2,-1,2}));
    assert(largestRectangleHistogram({2,1,5,6,2,3}) == 10);
    puts("8c  monotonic stack         OK");
}
