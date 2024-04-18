#!/bin/bash

# 1. Define the paths and configurations
RECOLOSSUS_PATH="/home/user/recolossus"
KLEE_PATH="${RECOLOSSUS_PATH}/build/bin/klee"
INCLUDE_PATH="${RECOLOSSUS_PATH}/klee/include"

EXTERNAL_FUNCTION="abs,atoi,memchr,memcpy,memset,strchr,strcoll,strcspn,strlen,strncmp,strpbrk,strspn,strtok,memcmp,memmove,strcat,strcmp,strcpy,strerror,strncat,strncpy,strrchr,strstr,strxfrm"

# 2. Compile the input file
clang -I ${INCLUDE_PATH} -emit-llvm -g -c $1.c -o $1.bc

# 3. Define common KLEE options
KLEE_OPTIONS="--max-time=600s --search=bfs --external-calls=all"

# 4. Invoke KLEE with Recolossus
${KLEE_PATH} \
  --max-solver-time=30s \
  --recolossus \
  --max-fuzz-solver-time=30 \
  --recolossus-external-function=${EXTERNAL_FUNCTION} \
  ${KLEE_OPTIONS} $1.bc
