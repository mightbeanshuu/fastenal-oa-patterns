// ============================================================================
// 1B — SLIDING WINDOW + FREQUENCY MAP
// ============================================================================
// TRIGGER WORDS : "every window of size K" · "substring/subarray of length K" ·
//                 "longest contiguous ... such that" · "at most K distinct"
//
// WHY IT EXISTS : recomputing each window from scratch is O(n*k). A window that
//                 slides only ever gains ONE element on the right and loses ONE
//                 on the left, so update the map instead of rebuilding it.
//
// FIXED WINDOW skeleton:
//     add(a[i]);
//     if (i >= k)     remove(a[i-k]);      // window is now exactly k wide
//     if (i >= k-1)   record answer;
//
// VARIABLE WINDOW skeleton:
//     for r: add(a[r]);
//            while (window is illegal) { remove(a[l]); l++; }
//            best = max(best, r-l+1);
//
// TRAP : when a count hits 0 you must mp.erase(key), otherwise mp.size() keeps
//        counting keys that are no longer inside the window.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// Fastenal-relevant: number of DISTINCT elements in every window of size k
vector<int> distinctInEveryWindow(const vector<int>& a, int k) {
    unordered_map<int,int> cnt;              // value -> count INSIDE the window
    vector<int> res;
    for (int i = 0; i < (int)a.size(); i++) {
        cnt[a[i]]++;                         // element enters on the right
        if (i >= k) {                        // element leaves on the left
            int out = a[i-k];
            if (--cnt[out] == 0) cnt.erase(out);   // <-- the trap
        }
        if (i >= k-1) res.push_back((int)cnt.size());
    }
    return res;
}

// Variable window: longest substring with all-distinct characters
int longestUniqueSubstring(const string& s) {
    unordered_map<char,int> cnt;
    int l = 0, best = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        cnt[s[r]]++;
        while (cnt[s[r]] > 1) {              // illegal -> shrink from the left
            if (--cnt[s[l]] == 0) cnt.erase(s[l]);
            l++;
        }
        best = max(best, r - l + 1);
    }
    return best;
}

// Variable window: longest subarray with AT MOST k distinct values
int longestAtMostKDistinct(const vector<int>& a, int k) {
    unordered_map<int,int> cnt;
    int l = 0, best = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        cnt[a[r]]++;
        while ((int)cnt.size() > k) {
            if (--cnt[a[l]] == 0) cnt.erase(a[l]);
            l++;
        }
        best = max(best, r - l + 1);
    }
    return best;
}

// TIME  O(n) — every index enters once and leaves once.   SPACE O(k)
// ---------------------------------------------------------------------------
int main() {
    vector<int> r = distinctInEveryWindow({1,2,1,3,4,2,3}, 4);
    assert((r == vector<int>{3,4,4,3}));
    assert(longestUniqueSubstring("abcabcbb") == 3);
    assert(longestUniqueSubstring("bbbbb")    == 1);
    assert(longestAtMostKDistinct({1,2,1,2,3}, 2) == 4);
    puts("1b  sliding window + map    OK");
}
