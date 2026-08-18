// ============================================================================
// 8A — STACK : VALID PARENTHESES (LC 20)          [family 8 = the closed gap]
// ============================================================================
// WHY THIS FAMILY EXISTS : an Oct-2024 selected candidate described the coding
// section as "stack, binary search and graph traversal". Stack is the only
// label in that sentence with no named instance in the corpus — so it is the
// one evidenced hole. This family closes it in about an hour.
//
// TRIGGER WORDS : brackets · nested · "balanced" · "matching" · "innermost"
//
// THE IDEA : a stack is the data structure for "the most recent unresolved
//            thing". Push openers; every closer must match the top.
//
// TRAP : check st.empty() BEFORE st.top(). Calling top() on an empty stack is
//        undefined behaviour, not an exception — it may even appear to work.
// TRAP : return st.empty() at the end. Leftover openers mean invalid.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

bool isValid(const string& s) {
    stack<char> st;
    unordered_map<char,char> match{{')','('}, {']','['}, {'}','{'}};
    for (char c : s) {
        if (c=='('||c=='['||c=='{') st.push(c);
        else if (match.count(c)) {
            if (st.empty() || st.top() != match[c]) return false;  // empty check FIRST
            st.pop();
        }
    }
    return st.empty();                          // leftovers => invalid
}

// counting variant with one bracket type — no stack needed, just a counter
bool isBalancedSimple(const string& s) {
    int bal = 0;
    for (char c : s) {
        if (c=='(') bal++;
        else if (c==')' && --bal < 0) return false;   // closed too early
    }
    return bal == 0;
}

int longestValidParentheses(const string& s) {       // stack of INDICES
    stack<int> st; st.push(-1);                      // sentinel base
    int best = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i]=='(') st.push(i);
        else {
            st.pop();
            if (st.empty()) st.push(i);              // new base
            else best = max(best, i - st.top());
        }
    }
    return best;
}

// TIME O(n)   SPACE O(n)
// ---------------------------------------------------------------------------
int main() {
    assert(isValid("()[]{}"));
    assert(!isValid("(]"));
    assert(!isValid("]"));                 // the empty-stack trap
    assert(!isValid("("));                 // the leftover trap
    assert(isValid(""));
    assert(isBalancedSimple("(())") && !isBalancedSimple("())("));
    assert(longestValidParentheses(")()())") == 4);
    assert(longestValidParentheses("(()") == 2);
    puts("8a  valid parentheses       OK");
}
