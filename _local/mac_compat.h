// Local-only shim. NOT part of any OA answer.
// Apple clang ships no unqualified ::__gcd (a GNU extension that the OA's
// g++ 9.2.0 does have), and macOS has no real <bits/stdc++.h>. run.sh puts
// _local/include on the include path and force-includes this file, so every
// drill compiles here exactly as it will on the day.
#pragma once
#include <bits/stdc++.h>
