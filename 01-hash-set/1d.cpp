// ============================================================================
// 1D — CANONICAL-FORM HASHING       *** FASTENAL ORIGINAL: "Passwords" ***
// ============================================================================
// TRIGGER WORDS : "two X are considered the SAME if you can transform one into
//                 the other" · "count how many DISTINCT ..." · "can swap/
//                 rearrange" · "group anagrams"
//
// IDEA : you cannot hash the objects themselves, because equal-but-different
//        objects must collapse. So map each object to a CANONICAL FORM — one
//        string that every member of the equivalence class produces — then the
//        answer is just set.size().
//
// THE PROBLEM : you may swap characters at positions i and j whenever
//               (i + j) % 2 == 0. How many distinct passwords are reachable?
//
// THE TWIST : (i+j) even  <=>  i and j have the SAME parity.
//             So even-indexed characters permute freely among themselves and
//             odd-indexed characters among themselves — but never across.
//             Canonical form = (length, sorted even chars, sorted odd chars).
//
// TRAP : you MUST use a separator. Without it ("ab","c") and ("a","bc") both
//        become "abc" and collide. Encode as  len#evens#odds.
// TRAP : length must be in the key too — "aa" and "aaaa" would otherwise share
//        a canonical form once the halves are concatenated.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

string canonical(const string& s) {
    string even, odd;
    for (int i = 0; i < (int)s.size(); i++) (i % 2 == 0 ? even : odd) += s[i];
    sort(even.begin(), even.end());
    sort(odd.begin(),  odd.end());
    return to_string(s.size()) + "#" + even + "#" + odd;   // separators matter
}

int countDistinctPasswords(const vector<string>& v) {
    unordered_set<string> st;
    for (const string& s : v) st.insert(canonical(s));
    return (int)st.size();
}

// Sibling shape you may see instead: group anagrams / count distinct anagrams.
// Canonical form there is simply the sorted string (or a 26-length count key).
int countDistinctAnagramClasses(const vector<string>& v) {
    unordered_set<string> st;
    for (string s : v) { sort(s.begin(), s.end()); st.insert(s); }
    return (int)st.size();
}

// TIME O(n * L log L)   SPACE O(n * L)
// ---------------------------------------------------------------------------
int main() {
    // "abcd" and "cbad": swap indices 0 and 2 -> same class.
    assert(canonical("abcd") == canonical("cbad"));
    // "abcd" vs "bacd": that swap is 0<->1, parities differ, NOT allowed.
    assert(canonical("abcd") != canonical("bacd"));
    assert(countDistinctPasswords({"abcd","cbad","bacd"}) == 2);
    // separator regression: without '#' these two would collide
    assert(canonical("ab") != canonical("ba"));
    assert(countDistinctAnagramClasses({"eat","tea","tan","ate","nat","bat"}) == 3);
    puts("1d  canonical hashing       OK   (Fastenal original: Passwords)");
}
