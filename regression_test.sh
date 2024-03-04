#!/bin/bash

# Define the paths
RECOLOSSUS_PATH="/home/user/recolossus"
KLEE_PATH="${RECOLOSSUS_PATH}/build/bin/klee"
INCLUDE_PATH="${RECOLOSSUS_PATH}/klee/include"

# Define common KLEE options
KLEE_OPTIONS="--warnings-only-to-file --max-time=600 --max-fuzz-solver-time=30 --search=bfs -rewrite-equalities=false --external-calls=all"

# Get the directory from the command line argument
DIR=$1

# Loop over all .c files in the directory
for FILE in $DIR/*.c; do
  # Get the base name of the file (without .c extension)
  BASENAME=$(basename $FILE .c)

  # Compile the input file
  clang -I ${INCLUDE_PATH} -emit-llvm -g -c $FILE -o ${DIR}/${BASENAME}.bc

  # Invoke KLEE with Recolossus and output to a separate directory for each file
  ${KLEE_PATH} --recolossus ${KLEE_OPTIONS} --output-dir=${DIR}/klee-${BASENAME} ${DIR}/${BASENAME}.bc

  # Remove the unnecessary intermediate files
  rm ${DIR}/${BASENAME}.bc
done

