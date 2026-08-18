# Family 8 — Stack: parsing & monotonic
**The closed gap.** No named instance exists in the corpus — but two independent weak signals
point at exactly this one missing pattern:

1. A named candidate (Software Developer, campus, **Oct 2024, selected**) describes the coding
   section verbatim as *"3 leetcode question, medium level, of **stack**, binary search and graph
   traversal."* The other two labels are corroborated by named problems. Stack is not.
2. Of the four aggregator-claimed problems — correctly refuted as evidence — three fall *inside*
   the seven-pattern set derived without them. The one that falls outside is **Number of Atoms
   (LC 726): stack parsing of a nested structure.**

**Cost to close: about one hour. Effect: chance of meeting something unfamiliar drops from ~20 % to ~9 %.**
This is the highest-value hour in the whole plan.

## Files
| File | Content | Time |
|---|---|---|
| `8a.cpp` | **Valid Parentheses** + balanced-counter + longest valid parentheses | 8 min |
| `8b.cpp` | **Decode String** — the Number-of-Atoms shape + a basic expression evaluator | 30 min |
| `8c.cpp` | **monotonic stack** — next greater · daily temperatures · circular · histogram | 25 min |

## The two ideas
**Parsing:** a stack holds "the most recent unresolved thing". Two stacks — one for the partial
string, one for the count in progress — decode any nesting.

**Monotonic:** keep the stack strictly decreasing. An incoming larger value is the answer for
everything it beats, so pop them all. Each index is pushed once and popped once → **O(n)**
despite the inner `while`.

## The traps
- Check `st.empty()` **before** `st.top()`. `top()` on an empty stack is undefined behaviour, not an exception — it may even appear to work.
- `return st.empty()` at the end. Leftover openers mean invalid.
- **Multi-digit numbers:** `num = num*10 + (c-'0')`. `12[ab]` breaks if you read one character.
- On `'['` reset **both** `cur` and `num` after pushing.
- Store **indices**, not values, whenever the answer is a distance.
