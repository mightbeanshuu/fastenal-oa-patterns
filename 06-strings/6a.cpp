// ============================================================================
// 6A — DIGIT ARITHMETIC WITH CARRY : ADD STRINGS (LC 415)
// ============================================================================
// TRIGGER WORDS : "add two numbers given as strings" · "do not convert to
//                 integer" · "the numbers may be up to 10^4 digits"
//
// THE SKELETON — one loop, three termination conditions fused:
//     while (i >= 0 || j >= 0 || carry) { ... }
//   That single line removes every edge case (unequal lengths, trailing carry).
//
// TRAP : build the answer backwards and reverse at the end. Prepending to a
//        std::string inside the loop is O(n^2).
// TRAP : '0' + digit to convert back to a character; forgetting it emits
//        control characters, not digits.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

string addStrings(const string& a, const string& b) {
    int i = (int)a.size() - 1, j = (int)b.size() - 1, carry = 0;
    string out;
    while (i >= 0 || j >= 0 || carry) {
        int s = carry;
        if (i >= 0) s += a[i--] - '0';
        if (j >= 0) s += b[j--] - '0';
        out += char('0' + s % 10);
        carry = s / 10;
    }
    reverse(out.begin(), out.end());
    return out;
}

string multiplyStrings(const string& a, const string& b) {   // same idea, grid of carries
    if (a == "0" || b == "0") return "0";
    vector<int> res(a.size() + b.size(), 0);
    for (int i = (int)a.size() - 1; i >= 0; i--)
        for (int j = (int)b.size() - 1; j >= 0; j--) {
            int mul = (a[i]-'0') * (b[j]-'0') + res[i+j+1];
            res[i+j+1] = mul % 10;
            res[i+j]  += mul / 10;
        }
    string out;
    for (int x : res) if (!(out.empty() && x == 0)) out += char('0' + x);
    return out;
}

// TIME O(max(m,n))   SPACE O(max(m,n))
// ---------------------------------------------------------------------------
int main() {
    assert(addStrings("11", "123") == "134");
    assert(addStrings("456", "77")  == "533");
    assert(addStrings("999", "1")   == "1000");     // trailing carry
    assert(addStrings("0", "0")     == "0");
    assert(multiplyStrings("123", "456") == "56088");
    assert(multiplyStrings("0", "52") == "0");
    puts("6a  add strings / carry     OK");
}
