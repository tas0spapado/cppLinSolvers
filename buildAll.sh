#!/bin/sh 

mkdir -p linked_headers
rm -f linked_headers/*
for f in src/headers/*; do
    [ -f "$f" ] && ln -sf "$(realpath "$f")" linked_headers/$(basename "$f")
done

PROJ_ROOT_DIR=$(pwd) make 
