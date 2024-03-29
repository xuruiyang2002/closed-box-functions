#!/bin/bash

# Define the paths
RECOLOSSUS_PATH="/home/user/recolossus"
KLEE_PATH="${RECOLOSSUS_PATH}/build/bin/klee"
INCLUDE_PATH="${RECOLOSSUS_PATH}/klee/include"

# Compile the input file
clang -I ${INCLUDE_PATH} -emit-llvm -g -c $1.c -o $1.bc

# Define common KLEE options
KLEE_OPTIONS="--max-time=600 --search=bfs --external-calls=all"
# KLEE_OPTIONS="--max-time=600 --max-fuzz-solver-time=30 --search=bfs --external-calls=all"

# Invoke KLEE with Recolossus
# ${KLEE_PATH} --recolossus ${KLEE_OPTIONS} $1.bc

# Invoke KLEE without Recolossus
${KLEE_PATH} --debug-z3-dump-queries=$1.smt2 ${KLEE_OPTIONS} $1.bc
