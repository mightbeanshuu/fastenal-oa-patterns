// ============================================================================
// 8B — NESTED STACK PARSING : DECODE STRING (LC 394)
// ============================================================================
// This is the Number-of-Atoms shape — the exact problem that fell OUTSIDE the
// seven-pattern set and forced family 8 to exist. If a nested-structure parse
// appears on the day, it will look like this.
//
// TRIGGER WORDS : "3[a2[c]]" · nested counts · nested brackets · "expand" ·
//                 chemical formulas · nested JSON-ish depth
//
// THE PATTERN : keep TWO stacks — one for the partial string built so far, one
//     for the repeat count in progress. On '[' push and reset; on ']' pop and
//     splice. Numbers can be multi-digit: num = num*10 + (c-'0').
//
// TRAP : multi-digit numbers. `12[ab]` breaks if you read one character.
// TRAP : on '[' you must reset BOTH cur and num after pushing them.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

string decodeString(const string& s) {
    stack<string> strs;
    stack<int> nums;
    string cur;
    int num = 0;
    for (char c : s) {
        if (isdigit((unsigned char)c)) num = num * 10 + (c - '0');   // multi-digit
        else if (c == '[') { strs.push(cur); nums.push(num); cur.clear(); num = 0; }
        else if (c == ']') {
            string inner = cur;
            cur = strs.top(); strs.pop();
            int k = nums.top(); nums.pop();
            while (k--) cur += inner;
            }
        else cur += c;
    }
    return cur;
}

// same two-stack skeleton, arithmetic flavour: evaluate "1+(2-3)*4" style input
// (kept short — the point is that the skeleton transfers)
int evalBasic(const string& s) {
    stack<int> st;
    int num = 0; char op = '+';
    for (int i = 0; i <= (int)s.size(); i++) {
        char c = i < (int)s.size() ? s[i] : '+';
        if (isdigit((unsigned char)c)) { num = num * 10 + (c - '0'); continue; }
        if (c == ' ') continue;
        if      (op == '+') st.push(num);
        else if (op == '-') st.push(-num);
        else if (op == '*') { int t = st.top(); st.pop(); st.push(t * num); }
        else if (op == '/') { int t = st.top(); st.pop(); st.push(t / num); }
        op = c; num = 0;
    }
    int sum = 0;
    while (!st.empty()) { sum += st.top(); st.pop(); }
    return sum;
}

// TIME O(output length)   SPACE O(depth)
// ---------------------------------------------------------------------------
int main() {
    assert(decodeString("3[a]2[bc]")   == "aaabcbc");
    assert(decodeString("3[a2[c]]")    == "accaccacc");   // nesting
    assert(decodeString("2[abc]3[cd]ef") == "abcabccdcdcdef");
    assert(decodeString("12[a]").size() == 12);            // multi-digit trap
    assert(decodeString("abc") == "abc");
    assert(evalBasic("3+2*2") == 7);
    assert(evalBasic("14-3/2") == 13);
    puts("8b  decode string (nested)  OK");
}
