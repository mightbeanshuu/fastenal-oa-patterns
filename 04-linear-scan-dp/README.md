# Family 4 — Linear scan with running state (incl. 1-D DP)
**3 sightings.** Largest Element · Maximum Subarray Sum · House Robber II.
This family owns the **cheap slot** — one confirmed paper's Q1 was literally
"find the largest element in the array".

## Files
| File | Content | Budget |
|---|---|---|
| `4a.cpp` | largest · second largest · best buy/sell · isSorted | 3 min |
| `4b.cpp` | **Kadane** + index-reporting variant + circular Kadane | 10 min |
| `4c.cpp` | House Robber I — the rolling-variable 1-D DP form | 15 min |
| `4d.cpp` | **House Robber II** — the circular cut | 10 min |

## The two skeletons
```cpp
// Kadane: extend the previous best, or restart here
cur = max(x, cur + x);   best = max(best, cur);

// 1-D DP, O(1) space: compute cur FIRST, then shift
cur = max(prev1, prev2 + x);   prev2 = prev1;   prev1 = cur;
```

## House Robber II, in one sentence
House 0 and house n−1 can never both be taken, so there are exactly two worlds —
`[0, n-1)` and `[1, n)` — and the answer is the max of running the linear solver on each.

## The traps
- Seed `best` from `a[0]`, **never from 0**. All-negative input is the standard hidden test.
- Second-largest needs a **strict** inequality or duplicates fool it.
- The DP shift order: compute `cur` before reassigning `prev2`, or it silently breaks past n=3.
- House Robber II with `n == 1`: handle it before slicing, or both ranges are empty and you return 0.
