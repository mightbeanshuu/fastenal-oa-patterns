# Fastenal OA — the eight families

Drill repo for the Fastenal India **IT Trainee** on-campus OA (Mercer Mettl, 120 min).
Every `.cpp` file here is **self-contained and runnable**: a commented template, the traps
that actually cost marks, and a `main()` full of assertions that proves it works.

> **All 24 files compile clean and pass every assertion.**

---

## The exam, in four lines

| | |
|---|---|
| **Format** | 120 min · Coding 60 min / **3 questions** · then MCQ 60 min. Sections are **one-way**; unused time does not carry forward. |
| **Composition** | Every observed 3-question paper is **1 Easy + 2 Moderate**. Not one has contained a Hard. |
| **Harness** | **Function-body-only.** A fixed signature sits between `// Read only region start/end` with `// Write code here`. **No `main()`, no `cin`.** Monaco editor, `gcc 5.4.0`/`9.2.0`, buttons *Compile and Test* / *Submit Code*. |
| **Grading** | **Per test case.** A brute force that runs still scores. The one exception is GCD Sum (3c), where brute force provably scores 0. |

---

## Progress tracker

| # | Family | Files | Status |
|---|---|---|---|
| **1** | Hash-map / set bookkeeping | `1a` `1b` `1c` `1d` `1e` | ⬜ |
| **2** | Binary search on the answer | `2a` `2b` `2c` | ⬜ |
| **3** | Number theory — gcd, sieve, totient | `3a` `3b` `3c` | ⬜ |
| **4** | Linear scan with running state / 1-D DP | `4a` `4b` `4c` `4d` | ⬜ |
| **5** | Sort + two-pointer sweep | `5a` `5b` | ⬜ |
| **6** | Explicit string construction & matching | `6a` `6b` | ⬜ |
| **7** | Grid flood fill (BFS/DFS) | `7a` `7b` | ⬜ |
| **8** | Stack — parsing & monotonic | `8a` `8b` `8c` | ⬜ |

Families 1–7 cover **100 % of the 18 confirmed questions** — see **[CONFIRMED-18.md](CONFIRMED-18.md)**
for the question-by-question index of which file solves each one. Family 8 closes the only
evidenced gap and takes the chance of meeting something unfamiliar from ~20 % to ~9 %.

⭐ **The three Fastenal-authored originals** — not on LeetCode, so grinding cannot reach them:
`1d` Passwords · `1e` String Letter Search · `2c` Deliver Fasteners.

---

## Run it

```bash
./run.sh all                    # compile + run every drill
./run.sh 01-hash-set/1a.cpp     # just one
```

`_local/` holds a macOS-only shim: Apple clang has no real `<bits/stdc++.h>` and no
unqualified `__gcd`. `run.sh` force-includes it so drills behave **exactly** as they will
on the OA's g++. Nothing in `_local/` is part of an answer.

---

## The trigger card — read the statement, match the phrase, reach for the file

| If the statement says… | Reach for |
|---|---|
| "minimum time" / "smallest speed" / "least capacity" | **2a** — binary search on the answer (floor midpoint, `hi = mid`) |
| "largest minimum distance" / "maximise the smallest" | **2b** — binary search on the answer (**ceil** midpoint, `lo = mid`) |
| "subarray with sum exactly K" **and negatives allowed** | **1c** — prefix sum + hash map (a sliding window is *wrong* here) |
| "every window of size K" / "longest window such that…" | **1b** — sliding window + frequency map |
| "two X are the same if you can transform one into the other — count distinct" | **1d** — canonical-form hashing |
| "distance = number of **distinct** characters between occurrences" | **1e** — first/last interval scan |
| "maximum sum of a **contiguous** subarray" | **4b** — Kadane |
| "no two adjacent may be chosen" (circular if it wraps) | **4c / 4d** — 1-D DP, run twice for the circle |
| "sum of gcd over all pairs 1..N" | **3c** — totient + divisor sieve |
| "minimum platforms/rooms" / "max overlapping intervals" | **5a** — sort + two-pointer sweep |
| "intersection / middle / cycle, **O(1) extra space**" | **5b** — linked-list two pointers |
| "add two numbers given as strings, do not convert to int" | **6a** — digit carry |
| "shortest palindrome by adding in front" / "longest prefix that is also a suffix" | **6b** — KMP failure function |
| "count islands/regions" / "minutes to spread across a grid" | **7a / 7b** — flood fill, multi-source BFS |
| nested brackets / nested counts / "next greater" | **8a / 8b / 8c** — stack |

---

## The 60 minutes

**T+0:00 — click question tab 2.** Whether it moves decides your plan. Costs one second.

- **If navigation is free:** read all three (4 min), then solve in *your* difficulty order — 10 / 18 / 22, 5 spare.
- **If forward-only** (~65 % likely): hard caps **12 / 18 / 25**, 5 in reserve. Deliberately asymmetric — an even 20/20/20 overspends the cheap slot.

**Abandon triggers**
- 8 minutes with no working approach → **write the brute force now.** Grading is per test case.
- At your cap → submit and advance regardless.
- **Exception: GCD Sum.** Sieve or nothing.
- Never start new code in the last 5 minutes.

**There is a cheap question in every paper.** Two-thirds of the time it is genuinely trivial
(one paper's was literally "find the largest element in the array"). Find it early, bank it.

---

## Two traps worth thirty seconds each

1. **`long long` everywhere in 2c.** Deliver Fasteners' answer reaches 99,999,000,010 — 46× past
   int32 — and `x*x` overflows far earlier. The signature returns `int`; compute in `long long` anyway.
2. **`__gcd` is a GNU extension.** Fine on the OA, absent in Apple clang. If you ever doubt it,
   Euclid is one line: `while(b){T t=a%b;a=b;b=t;} return a<0?-a:a;`

---

*Companion research on the Desktop: `FAST-PATTERNS.md` (the closure argument),
`FASTENAL-OA-RESEARCH.md` (full sourced dossier).
Practice environment: `~/Desktop/fastenal-oa-clone` · https://fastenal-oa-clone.vercel.app*
