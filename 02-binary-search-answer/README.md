# Family 2 — Binary search on the answer
**The highest-confidence call in the whole research: 4 independent sightings across 3 years,
and in *both* papers where the hardest slot is identifiable, it was this.**
Instantiated by: Deliver Fasteners · Aggressive Cows · Koko Eating Bananas.

## The one idea
You are not searching the array. You are searching the **answer space**. Define
`can(mid)` = "is `mid` a feasible answer?". If `can` is monotone
(`false false false TRUE TRUE TRUE`) you can binary search for the boundary.

## The two forms — the only thing you must not mix up
```cpp
// MINIMISE (2a): "is a SMALLER answer still feasible?"
while (lo < hi) { long long mid = lo + (hi-lo)/2;      if (can(mid)) hi = mid;   else lo = mid+1; }

// MAXIMISE (2b): "is a LARGER answer still feasible?"
while (lo < hi) { long long mid = lo + (hi-lo+1)/2;    if (can(mid)) lo = mid;   else hi = mid-1; }
//                                        ^^^ the +1 is mandatory or you loop forever
```

## Files
| File | Form | Problems |
|---|---|---|
| `2a.cpp` | minimise the maximum | Koko Eating Bananas · Ship Capacity in D Days |
| `2b.cpp` | maximise the minimum | Aggressive Cows · Split Array Largest Sum |
| `2c.cpp` | ⭐ **Deliver Fasteners** — Fastenal original, **seen in 2022 AND 2023** | the only proof of bank reuse in the corpus |

## The traps
- `hi` must be a value that is **certainly feasible**, or you return garbage.
- `mid = lo + (hi-lo)/2`, never `(lo+hi)/2` — that overflows.
- The maximise form **needs** the ceiling midpoint. With `lo=3, hi=4` the floor midpoint is 3, `can(3)` is true, `lo` stays 3 — infinite loop.
- **2c specifically:** `x = 0` must cost **0**, but `F(S,0) = S`. Every idle truck otherwise inflates the answer. And the answer reaches 99,999,000,010 — `long long` throughout.
