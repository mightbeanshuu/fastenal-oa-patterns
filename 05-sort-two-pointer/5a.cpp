// ============================================================================
// 5A — SORT + TWO-POINTER SWEEP : MINIMUM PLATFORMS
// ============================================================================
// TRIGGER WORDS : "minimum number of platforms/rooms/servers" · "maximum number
//                 of overlapping intervals" · "can this person attend all
//                 meetings" · anything with start[] and end[]
//
// THE IDEA : you do NOT need to know which train uses which platform. Sort the
//            arrivals and the departures INDEPENDENTLY, then sweep both with
//            two pointers, tracking how many are currently inside.
//
// TRAP : a departure at exactly the same time as an arrival. Decide the tie
//        from the statement. Below, `arr[i] <= dep[j]` means a train arriving
//        at the instant another leaves still needs its own platform (the usual
//        convention for this problem).
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

int minPlatforms(vector<int> arr, vector<int> dep) {
    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());            // sorted SEPARATELY — pairing is lost, and fine
    int i = 0, j = 0, cur = 0, best = 0;
    while (i < (int)arr.size()) {
        if (arr[i] <= dep[j]) { cur++; i++; best = max(best, cur); }
        else                  { cur--; j++; }
    }
    return best;
}

// the same sweep written as a +1/-1 event list — easier to adapt on the day
int minPlatformsEvents(const vector<int>& arr, const vector<int>& dep) {
    vector<pair<int,int>> ev;
    for (int x : arr) ev.push_back({x, +1});
    for (int x : dep) ev.push_back({x, -1});
    // +1 before -1 at equal times => a departure does not free the platform in time
    sort(ev.begin(), ev.end(), [](auto& a, auto& b){
        return a.first != b.first ? a.first < b.first : a.second > b.second;
    });
    int cur = 0, best = 0;
    for (auto& e : ev) { cur += e.second; best = max(best, cur); }
    return best;
}

// classic sibling: merge overlapping intervals
vector<pair<int,int>> mergeIntervals(vector<pair<int,int>> v) {
    sort(v.begin(), v.end());
    vector<pair<int,int>> out;
    for (auto& p : v) {
        if (!out.empty() && p.first <= out.back().second)
            out.back().second = max(out.back().second, p.second);
        else out.push_back(p);
    }
    return out;
}

// TIME O(n log n)   SPACE O(1) for the sweep
// ---------------------------------------------------------------------------
int main() {
    assert(minPlatforms({900,940,950,1100,1500,1800}, {910,1200,1120,1130,1900,2000}) == 3);
    assert(minPlatforms({900,1100,1235}, {1000,1200,1240}) == 1);
    assert(minPlatforms({100,200}, {200,300}) == 2);          // the tie case
    assert(minPlatformsEvents({900,940,950,1100,1500,1800}, {910,1200,1120,1130,1900,2000}) == 3);
    auto m = mergeIntervals({{1,3},{2,6},{8,10},{15,18}});
    assert((m == vector<pair<int,int>>{{1,6},{8,10},{15,18}}));
    puts("5a  sort + sweep            OK");
}
