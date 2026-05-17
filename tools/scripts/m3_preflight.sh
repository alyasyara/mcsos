#!/usr/bin/env bash
set -euo pipefail

echo "[M3] preflight checks"

need() {
    command -v "$1" >/dev/null 2>&1 || {
        echo "[fail] missing dependency: $1"
        exit 1
    }
}

need clang
need ld.lld
need qemu-system-x86_64
need xorriso
need git

echo "[ok] required tools detected"

mkdir -p build/meta

{
    echo "timestamp=$(date -u +"%Y-%m-%dT%H:%M:%SZ")"
    echo "clang=$(clang --version | head -n1)"
    echo "lld=$(ld.lld --version | head -n1)"
    echo "qemu=$(qemu-system-x86_64 --version | head -n1)"
} > build/meta/m3-preflight.txt

echo "[ok] metadata written to build/meta/m3-preflight.txt"
echo "[M3] preflight completed"
