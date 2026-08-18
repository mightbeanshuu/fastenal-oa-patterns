# Family 1 — Hash-map / set bookkeeping
**4 sightings — the largest family in the corpus, and the most likely middle slot.**
Instantiated by: String Letter Search · Passwords · Distinct Elements in Window K · Longest Subarray With Sum K.

## The one idea
While scanning once, remember what you have already seen, so you never go back and
re-search the old part of the array. That turns O(n²) into O(n).

## The four questions to ask a statement
| Question | Answer |
|---|---|
| Do I only need *existence*? | `unordered_set` |
| Do I need *how many times*? | `unordered_map<T,int>` → `mp[x]++` |
| Do I need *where*? | `unordered_map<T,int>` → `mp[x] = i` |
| Can I turn the object into a *key*? | canonical form + set |

## Files
| File | Sub-pattern | Trigger |
|---|---|---|
| `1a.cpp` | basic bookkeeping | distinct · duplicate · frequency · occurrence |
| `1b.cpp` | sliding window + freq map | "every window of size K" · "longest window such that" |
| `1c.cpp` | prefix sum + hash map | "subarray sum exactly K" **with negatives** |
| `1d.cpp` | canonical-form hashing ⭐ | "two X are the same if…" — **Fastenal original: Passwords** |
| `1e.cpp` | first/last interval scan ⭐ | "distinct chars between occurrences" — **Fastenal original: String Letter Search** |

## Say this in an interview
Not *"I'll use unordered_map"* — that is only the data structure.
Say **"a single linear scan maintaining a hash map of frequencies"**, or
**"a sliding window with a frequency map"**, or **"prefix sums stored in a hash map"**.
Pattern **and** structure.

## The traps that cost marks here
- `mp[x]++` works on a missing key. Never write the `if/else` version.
- `mp[x]++` **counts**; `mp[x] = i` **overwrites**. 1c depends on the difference.
- In a sliding window, `erase` the key when its count hits 0, or `mp.size()` lies.
- With negatives, a sliding window is **wrong** for sum-K. Use prefix sums.
- Canonical forms need a **separator**: `len#evens#odds`, or `("ab","c")` collides with `("a","bc")`.
