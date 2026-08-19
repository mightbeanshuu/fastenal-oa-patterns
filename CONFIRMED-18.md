# The 18 confirmed questions → where each one lives

The repo is organised by **pattern**, not by problem, because that is how you recognise them under
time pressure. This file is the other index: every question the research confirmed Fastenal has
actually asked, and the file that solves it.

**All 18 are covered. All 18 compile and pass their assertions.**

| # | Confirmed question | Family | File | Function |
|---|---|---|---|---|
| 1 | ⭐ **Deliver Fasteners** *(Fastenal original — seen 2022 **and** 2023)* | 2 · binary search on answer | `02-binary-search-answer/2c.cpp` | `deliverFasteners` |
| 2 | ⭐ **String Letter Search** *(Fastenal original)* | 1 · hash/set bookkeeping | `01-hash-set/1e.cpp` | `stringLetterSearch` |
| 3 | ⭐ **Passwords** *(Fastenal original)* | 1 · canonical-form hashing | `01-hash-set/1d.cpp` | `countDistinctPasswords` |
| 4 | **GCD Sum** *(the only Hard in the corpus)* | 3 · totient + divisor sieve | `03-number-theory/3c.cpp` | `gcdSum` |
| 5 | House Robber II (LC 213) | 4 · 1-D DP, circular cut | `04-linear-scan-dp/4d.cpp` | `robCircular` |
| 6 | Shortest Palindrome (LC 214) | 6 · KMP failure function | `06-strings/6b.cpp` | `shortestPalindrome` |
| 7 | Intersection of Two Linked Lists (LC 160) | 5 · two-pointer alignment | `05-sort-two-pointer/5b.cpp` | `getIntersection` |
| 8 | Aggressive Cows (LC 1552) | 2 · maximise the minimum | `02-binary-search-answer/2b.cpp` | `maxMinDistance` |
| 9 | Minimum Platforms | 5 · sorted sweep | `05-sort-two-pointer/5a.cpp` | `minPlatforms` |
| 10 | Longest Subarray With Sum K (LC 560 family) | 1 · prefix sum + hash map | `01-hash-set/1c.cpp` | `longestSubarraySumK` |
| 11 | Maximum Subarray Sum (LC 53) | 4 · Kadane | `04-linear-scan-dp/4b.cpp` | `maxSubarraySum` |
| 12 | Add Strings (LC 415) | 6 · digit carry | `06-strings/6a.cpp` | `addStrings` |
| 13 | Largest Element in Array *(a real warm-up slot)* | 4 · linear scan | `04-linear-scan-dp/4a.cpp` | `largestElement` |
| 14 | Number of Islands (LC 200) | 7 · grid flood fill | `07-grid-bfs-dfs/7a.cpp` | `numIslandsBFS` |
| 15 | Koko Eating Bananas (LC 875) | 2 · minimise the maximum | `02-binary-search-answer/2a.cpp` | `minEatingSpeed` |
| 16 | Distinct Elements in Every Window of K | 1 · sliding window + freq map | `01-hash-set/1b.cpp` | `distinctInEveryWindow` |
| 17 | Sieve of Eratosthenes | 3 · number theory | `03-number-theory/3b.cpp` | `primesUpTo` |
| 18 | HCF / GCD | 3 · Euclid | `03-number-theory/3a.cpp` | `gcdIter` |

> **On the count.** `FAST-PATTERNS.md` §2 prints 17 table *rows* because rows 17 and 18 are merged
> into one line, "Sieve / HCF". They are two distinct confirmed questions, so the corpus total is
> **18**. If you ever see "17 confirmed questions" written elsewhere in these notes, this is the
> discrepancy — the same merged row, counted differently.

---

## Coverage arithmetic

| Family | Confirmed questions it carries |
|---|---|
| 1 · hash-map / set bookkeeping | 4 — #2, #3, #10, #16 |
| 2 · binary search on the answer | 3 — #1, #8, #15 |
| 3 · number theory | 3 — #4, #17, #18 |
| 4 · linear scan / 1-D DP | 3 — #5, #11, #13 |
| 5 · sort + two-pointer sweep | 2 — #7, #9 |
| 6 · string construction & matching | 2 — #6, #12 |
| 7 · grid flood fill | 1 — #14 |
| **Families 1–7** | **18 — 100 %, nothing left over** |
| 8 · stack | **0 confirmed** — the evidenced gap, see `08-stack/README.md` |

Four families carry 13 of the 18. The tail is flat (2, 2, 1), so *which* tail family you buy matters
far less than buying all of them.

---

## What is in the repo beyond the 18, and why

Nothing here is padding — each item either teaches the template the confirmed question needs, or
closes an evidenced risk.

| Extra | File | Why it is here |
|---|---|---|
| set / frequency / index-map templates | `1a` | the foundation every family-1 question stands on |
| longest-unique-substring · at-most-K-distinct | `1b` | the variable-window form, in case the window is not fixed |
| count-subarrays-sum-K · equal-0s-and-1s | `1c` | the same prefix map with a different key |
| group / count anagram classes | `1d` | the other canonical-form phrasing |
| Ship Capacity in D Days | `2a` | second rep of the minimise form |
| Split Array Largest Sum | `2b` | looks like maximise, **is** minimise — the form-choice trap |
| SPF sieve · divisor sieve · totient sieve | `3b` | the divisor sieve is what makes #4 possible at all |
| second largest · buy/sell · isSorted | `4a` | the warm-up slot is cheap; have several shapes ready |
| Kadane with indices · circular Kadane | `4b` | the two variants they ask as a follow-up |
| **House Robber I** | `4c` | the subroutine #5 calls twice — learn it first |
| event-list sweep · merge intervals | `5a` | the ±1 form adapts to any interval question |
| middle node · Floyd cycle · reverse | `5b` | the rest of the O(1)-space list toolkit |
| multiply strings | `6a` | the carry skeleton, one level up |
| KMP substring search · `buildLPS` | `6b` | the failure function is the reusable piece |
| DFS islands · largest island area | `7a` | the two follow-ups to #14 |
| rotting oranges · shortest grid path | `7b` | multi-source BFS — "graph traversal" was named by a selected candidate |
| **all of family 8** | `8a` `8b` `8c` | the one evidenced gap: a selected Oct-2024 candidate named "stack"; ~1 h closes it, and it takes the chance of meeting something unfamiliar from ~20 % to ~9 % |

---

## Verify it yourself

```bash
./run.sh all
```

24 files, all compile, all assertions pass. `3c` GCD Sum is additionally checked against a brute-force
double loop for every `n ≤ 200`, and `1e` String Letter Search proves its own first/last shortcut
against an all-pairs brute force — because both of those rest on a claim, not just an implementation.
