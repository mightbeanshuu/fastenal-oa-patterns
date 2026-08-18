# Family 7 — Grid flood fill (BFS / DFS)
**1 sighting** (Number of Islands) — but an Oct-2024 selected candidate independently listed
"graph traversal" as one of the three coding questions, so treat it as live.

## Files
| File | Content |
|---|---|
| `7a.cpp` | **Number of Islands** — BFS *and* DFS versions + largest island area |
| `7b.cpp` | **multi-source BFS** — rotting oranges + shortest path in a grid |

## The two ideas
**Flood fill:** scan every cell; on an unvisited land cell, increment the counter and flood the
whole component so it is never counted again. Sinking `'1' → '0'` in place is the cheapest
visited-marker — say so out loud if asked about extra space.

**Multi-source BFS:** push **all** sources into the queue *before* the loop. BFS expands them in
lockstep, so the level number **is** the answer. Running one BFS per source is the mistake.

## The traps
- **Recursion depth.** A 1000×1000 all-land grid is 10⁶ deep and blows the stack. Iterative BFS is the safe OA default.
- Mark visited **on push**, never on pop, or the same cell enters the queue many times.
- Bounds-check before indexing; handle the empty grid.
- Multi-source answer = `levels − 1`; then check nothing is left unreached → `-1`.
