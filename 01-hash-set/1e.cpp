// ============================================================================
// 1E — FIRST/LAST INTERVAL SCAN   *** FASTENAL ORIGINAL: String Letter Search ***
// ============================================================================
// THE PROBLEM : given a string and a character Y, the "distance" between two
//               occurrences of Y is the number of DISTINCT characters strictly
//               between them, ignoring whitespace. Return the largest distance.
//
// THE TWIST : distinct-count is MONOTONE — widening an interval can never
//             reduce the number of distinct characters inside it. Therefore the
//             maximum is ALWAYS between the FIRST and the LAST occurrence of Y.
//             You never test another pair. O(n^2) pair loop -> single O(n) scan.
//
// TRAPS : (1) whitespace is excluded from the count.
//         (2) fewer than two occurrences of Y -> answer 0.
//         (3) "strictly between" — do not count the two Y endpoints themselves.
//             (Read the statement on the day: some variants DO count interior
//              occurrences of Y. The code below excludes only the endpoints.)
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

int stringLetterSearch(const string& s, char y) {
    int first = -1, last = -1;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == y) { if (first == -1) first = i; last = i; }
    }
    if (first == -1 || first == last) return 0;      // 0 or 1 occurrence

    unordered_set<char> st;
    for (int i = first + 1; i < last; i++) {         // strictly between
        if (isspace((unsigned char)s[i])) continue;  // whitespace excluded
        st.insert(s[i]);
    }
    return (int)st.size();
}

// Brute force kept for a 30-second sanity check on the day. O(n^2 * 26).
int bruteForce(const string& s, char y) {
    vector<int> pos;
    for (int i = 0; i < (int)s.size(); i++) if (s[i] == y) pos.push_back(i);
    int best = 0;
    for (int a = 0; a < (int)pos.size(); a++)
        for (int b = a + 1; b < (int)pos.size(); b++) {
            unordered_set<char> st;
            for (int i = pos[a] + 1; i < pos[b]; i++)
                if (!isspace((unsigned char)s[i])) st.insert(s[i]);
            best = max(best, (int)st.size());
        }
    return best;
}

// TIME O(n)   SPACE O(distinct chars)
// ---------------------------------------------------------------------------
int main() {
    assert(stringLetterSearch("abcaXbca", 'a') == 4);  // between a[0] and a[7]: b c a X -> 4
    assert(stringLetterSearch("aXYZa", 'a') == 3);     // X Y Z
    assert(stringLetterSearch("a b c a", 'a') == 2);   // spaces excluded -> b,c
    assert(stringLetterSearch("hello", 'z') == 0);     // absent
    assert(stringLetterSearch("hello", 'h') == 0);     // single occurrence
    // the monotonicity claim: first-last must equal the best over all pairs
    for (const string& t : {string("aXaYaZa"), string("a  a b a"), string("zzazbzaz")})
        assert(stringLetterSearch(t, 'a') == bruteForce(t, 'a'));
    puts("1e  first/last interval     OK   (Fastenal original: String Letter Search)");
}
