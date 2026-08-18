// ============================================================================
// 5B — TWO POINTERS ON A LINKED LIST  (LC 160 intersection, + the classics)
// ============================================================================
// TRIGGER WORDS : "intersection of two lists" · "middle node" · "detect a
//                 cycle" · "nth from the end" — especially with "O(1) extra
//                 space", which forbids the hash-set answer.
//
// THE INTERSECTION TRICK : walk pointer A over listA then listB, and pointer B
//     over listB then listA. Both travel exactly lenA + lenB, so they arrive at
//     the intersection simultaneously. If there is none, both hit null together
//     and the loop ends — no special case needed.
//
// TRAP : advance with  p = p ? p->next : headB;  NOT
//        p = p->next ? p->next : headB;  — the second never terminates on
//        non-intersecting lists.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

struct Node { int val; Node* next; Node(int v): val(v), next(nullptr) {} };

Node* getIntersection(Node* a, Node* b) {
    if (!a || !b) return nullptr;
    Node *p = a, *q = b;
    while (p != q) {
        p = p ? p->next : b;                 // switch heads exactly once
        q = q ? q->next : a;
    }
    return p;                                // the node, or nullptr
}

Node* middleNode(Node* h) {                  // slow/fast: second middle if even
    Node *s = h, *f = h;
    while (f && f->next) { s = s->next; f = f->next->next; }
    return s;
}

bool hasCycle(Node* h) {                     // Floyd
    Node *s = h, *f = h;
    while (f && f->next) {
        s = s->next; f = f->next->next;
        if (s == f) return true;
    }
    return false;
}

Node* reverseList(Node* h) {
    Node* prev = nullptr;
    while (h) { Node* nxt = h->next; h->next = prev; prev = h; h = nxt; }
    return prev;
}

// TIME O(m+n)   SPACE O(1)
// ---------------------------------------------------------------------------
static Node* build(vector<int> v) {
    Node *head = nullptr, *tail = nullptr;
    for (int x : v) { Node* n = new Node(x); if (!head) head = tail = n; else { tail->next = n; tail = n; } }
    return head;
}
int main() {
    Node* shared = build({8,4,5});
    Node* a = build({4,1});  a->next->next = shared;
    Node* b = build({5,6,1}); b->next->next->next = shared;
    assert(getIntersection(a, b) == shared);
    assert(getIntersection(build({1,2}), build({3,4})) == nullptr);   // no crash, no loop
    assert(middleNode(build({1,2,3,4,5}))->val == 3);
    assert(middleNode(build({1,2,3,4}))->val == 3);
    Node* c = build({1,2,3}); c->next->next->next = c;
    assert(hasCycle(c));
    assert(!hasCycle(build({1,2,3})));
    assert(reverseList(build({1,2,3}))->val == 3);
    puts("5b  linked-list two-pointer OK");
}
