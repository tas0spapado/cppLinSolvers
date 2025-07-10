#!/usr/bin/env bash

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"      # script directory

# venv
if [ ! -d "$SCRIPT_DIR/venv" ]; then
    python3 -m venv "$SCRIPT_DIR/venv"
    source "$SCRIPT_DIR/venv/bin/activate"
    pip install --upgrade pip
    pip install numpy matplotlib
else
    source "$SCRIPT_DIR/venv/bin/activate"
fi

python "$SCRIPT_DIR/plot_iso_u.py"

deactivate
