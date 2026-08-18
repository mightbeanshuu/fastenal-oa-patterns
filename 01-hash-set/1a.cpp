// ============================================================================
// 1A — HASH / SET : BASIC BOOKKEEPING
// ============================================================================
// TRIGGER WORDS : distinct · unique · duplicate · repeated · frequency ·
//                 occurrence · "seen before" · count characters
//
// IDEA : while scanning once, remember what you have already seen, so you never
//        go back and re-search the old part of the array.  O(n^2) -> O(n).
//
//   need existence?      unordered_set
//   need how many?       unordered_map<T,int>  ->  mp[x]++
//   need where?          unordered_map<T,int>  ->  mp[x] = i
//
// TRAP : mp[x]++ works on a missing key (value-initialised to 0). Never write
//        the if (mp.count(x)) ... else ... version.
// TRAP : mp[x]++ counts, mp[x] = i overwrites. Do not mix them up — 1C depends
//        on the index form.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// --- Template 1 : seen / not seen -------------------------------------------
int firstRepeat(const vector<int>& a) {
    unordered_set<int> seen;                 // values already visited
    for (int x : a) {
        if (seen.count(x)) return x;         // x appeared earlier -> answer
        seen.insert(x);                      // remember for the future
    }
    return -1;                               // nothing repeats
}

// --- Template 2 : count distinct --------------------------------------------
int countDistinct(const vector<int>& a) {
    unordered_set<int> st(a.begin(), a.end()); // duplicates simply never enter
    return (int)st.size();
}

// --- Template 3 : frequency map (this is Anshu's own OA-style solution) ------
// If ties must break to the SMALLEST element, use the commented condition.
int mostFrequent(const vector<int>& a) {
    unordered_map<int,int> mpp;              // element -> frequency
    for (int x : a) mpp[x]++;

    int max_freq = 0, most_freq_el = 0;
    for (auto it : mpp) {                    // it.first = key, it.second = count
        if (it.second > max_freq) {
        //  || (it.second == max_freq && it.first < most_freq_el)   <-- tie rule
            max_freq = it.second;
            most_freq_el = it.first;
        }
    }
    return most_freq_el;
}

// --- Template 4 : value -> index (the seed of 1C) ---------------------------
unordered_map<int,int> lastIndexOf(const vector<int>& a) {
    unordered_map<int,int> mp;
    for (int i = 0; i < (int)a.size(); i++) mp[a[i]] = i;   // overwrites, keeps LAST
    return mp;
}

// --- Character frequency: same pattern, different key type ------------------
int distinctChars(const string& s) {
    unordered_set<char> st;
    for (char c : s) if (!isspace((unsigned char)c)) st.insert(c);
    return (int)st.size();
}

// TIME  O(n) average   SPACE O(n)
// ---------------------------------------------------------------------------
int main() {
    assert(firstRepeat({4,7,2,7,5}) == 7);
    assert(firstRepeat({1,2,3})     == -1);
    assert(countDistinct({4,2,7,4,9,2}) == 4);
    assert(mostFrequent({5,3,8,3,5,5,9}) == 5);
    assert(lastIndexOf({5,8,5})[5] == 2);
    assert(distinctChars("a b c a") == 3);
    puts("1a  basic bookkeeping        OK");
}
