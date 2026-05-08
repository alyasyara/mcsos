#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SRC="$ROOT_DIR/tests/toolchain/freestanding_probe.c"
OUT_DIR="$ROOT_DIR/build/proof"

mkdir -p "$OUT_DIR"

gcc \
  -std=c11 \
  -ffreestanding \
  -fno-builtin \
  -Wall \
  -Wextra \
  -Werror \
  -c "$SRC" \
  -o "$OUT_DIR/freestanding_probe.o"

echo "[ok] freestanding toolchain probe compiled"
