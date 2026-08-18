#!/bin/bash
# Usage: ./run.sh 01-hash-set/1a.cpp     (or ./run.sh all)
set -u
BASE="$(cd "$(dirname "$0")" && pwd)"
FLAGS=(-std=c++17 -O2 -Wall -I "$BASE/_local/include" -include "$BASE/_local/mac_compat.h")

compile_run () {
  f="$1"
  out="/tmp/fq_$(basename "${f%.cpp}")"
  if clang++ "${FLAGS[@]}" "$f" -o "$out" 2>/tmp/fq_err; then
    "$out" || echo "  !! runtime failure: $f"
  else
    echo "  !! COMPILE FAIL: $f"; head -20 /tmp/fq_err
  fi
}

if [ "${1:-all}" = "all" ]; then
  for f in "$BASE"/0*/*.cpp; do compile_run "$f"; done
else
  compile_run "$BASE/$1"
fi
