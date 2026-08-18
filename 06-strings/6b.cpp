// ============================================================================
// 6B — SHORTEST PALINDROME + KMP FAILURE FUNCTION  (LC 214)
// ============================================================================
// TRIGGER WORDS : "add characters IN FRONT to make it a palindrome" · "longest
//                 prefix that is also a suffix" · substring search
//
// THE REDUCTION : you want the LONGEST PALINDROMIC PREFIX of s. Everything
//     after it gets mirrored onto the front. Build  t = s + '#' + reverse(s)
//     and run the KMP failure function; lps.back() is exactly the length of
//     that palindromic prefix.
//
// WHY THE '#' : without a separator the prefix and suffix can overlap and you
//               get a length longer than s. This is the classic bug.
//
// NOTE : the corpus says O(n^2) is enough here. The KMP version is below
//        because the failure function itself is the reusable piece.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

vector<int> buildLPS(const string& p) {      // lps[i] = longest proper prefix
    vector<int> lps(p.size(), 0);            //           that is also a suffix
    int len = 0;
    for (int i = 1; i < (int)p.size(); ) {
        if (p[i] == p[len]) lps[i++] = ++len;
        else if (len)       len = lps[len-1];      // fall back, do NOT i++
        else                lps[i++] = 0;
    }
    return lps;
}

string shortestPalindrome(const string& s) {
    if (s.empty()) return s;
    string rev(s.rbegin(), s.rend());
    string t = s + '#' + rev;                // the '#' is mandatory
    int k = buildLPS(t).back();              // longest palindromic prefix length
    return string(rev.begin(), rev.begin() + (s.size() - k)) + s;
}

// KMP substring search — the other thing the failure function buys you
vector<int> kmpSearch(const string& text, const string& pat) {
    vector<int> lps = buildLPS(pat), hits;
    for (int i = 0, j = 0; i < (int)text.size(); ) {
        if (text[i] == pat[j]) { i++; j++; if (j == (int)pat.size()) { hits.push_back(i-j); j = lps[j-1]; } }
        else if (j) j = lps[j-1];
        else i++;
    }
    return hits;
}

bool isPalindrome(const string& s) {
    for (int i = 0, j = (int)s.size()-1; i < j; i++, j--) if (s[i] != s[j]) return false;
    return true;
}

// TIME O(n)   SPACE O(n)
// ---------------------------------------------------------------------------
int main() {
    assert(shortestPalindrome("aacecaaa") == "aaacecaaa");
    assert(shortestPalindrome("abcd")     == "dcbabcd");
    assert(shortestPalindrome("")         == "");
    assert(shortestPalindrome("aba")      == "aba");
    assert(isPalindrome(shortestPalindrome("abcd")));
    assert((buildLPS("aabaaab") == vector<int>{0,1,0,1,2,2,3}));
    assert((kmpSearch("ababcabab", "abab") == vector<int>{0,5}));
    puts("6b  shortest palindrome/KMP OK");
}
