# Family 5 — Sort + two-pointer sweep
**2 sightings.** Minimum Platforms · Intersection of Two Linked Lists.

## Files
| File | Content |
|---|---|
| `5a.cpp` | **Minimum Platforms** (two-pointer sweep *and* the ±1 event-list form) + merge intervals |
| `5b.cpp` | linked-list two pointers: intersection · middle · Floyd cycle · reverse |

## The two ideas
**Intervals:** you do not need to know *which* train uses *which* platform. Sort arrivals and
departures **independently**, sweep both, track how many are currently inside.

**Lists:** walk pointer A over listA-then-listB and pointer B over listB-then-listA. Both travel
exactly `lenA + lenB`, so they meet at the intersection. If there is none, both hit `null`
together and the loop ends — **no special case needed**.

## The traps
- The equal-time tie in Minimum Platforms: decide from the statement. `arr[i] <= dep[j]` means a
  train arriving as another leaves still needs its own platform (the usual convention).
- Advance with `p = p ? p->next : headB`, **not** `p = p->next ? p->next : headB` — the second
  never terminates on non-intersecting lists.
- "O(1) extra space" in the statement is what forbids the hash-set answer. That phrase *is* the trigger.
