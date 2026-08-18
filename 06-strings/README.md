# Family 6 — Explicit string construction & matching
**2 sightings.** Add Strings · Shortest Palindrome.
Fastenal's coding section is historically **string-heavy** — multiple candidate reports say so.

## Files
| File | Content |
|---|---|
| `6a.cpp` | **Add Strings** (digit carry) + multiply strings |
| `6b.cpp` | **Shortest Palindrome** + the KMP failure function + KMP substring search |

## The two skeletons
```cpp
// carry: one loop, three termination conditions fused — kills every edge case
while (i >= 0 || j >= 0 || carry) { ... }

// shortest palindrome: longest palindromic prefix via lps of  s + '#' + reverse(s)
```

## The traps
- Build the answer **backwards and reverse at the end**. Prepending inside the loop is O(n²).
- `'0' + digit` to convert back to a character — forget it and you emit control characters.
- The `'#'` in `s + '#' + rev` is **mandatory**. Without it prefix and suffix overlap and you get
  a length longer than `s`. This is the classic bug.
- In `buildLPS`, on a mismatch with `len > 0` you fall back — **do not** advance `i`.
- The corpus notes O(n²) is enough for Shortest Palindrome. KMP is here because the failure
  function itself is the reusable piece.
