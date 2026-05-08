#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
OUT="$ROOT/build/meta"

mkdir -p "$OUT"

{
echo "mcsos_milestone=M1"
echo "date_utc=$(date -u +"%Y-%m-%dT%H:%M:%SZ")"
echo "repo=$ROOT"

echo
echo "[tool-versions]"
git --version
make --version | head -n 1
clang --version | head -n 1
gcc --version | head -n 1
qemu-system-x86_64 --version | head -n 1
python3 --version

} | tee "$OUT/toolchain-versions.txt"

echo "[ok] metadata collected"
