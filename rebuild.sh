#!/bin/sh

# Define the paths
RECOLOSSUS_PATH="/home/user/recolossus"
KRPK_PATH="${RECOLOSSUS_PATH}/krpk"
BUILD_PATH="${RECOLOSSUS_PATH}/build"

# Build the cargo project
cd ${KRPK_PATH}
cargo build

# Build KLEE
cd ${BUILD_PATH}
ninja klee

# Return to the original directory
cd -

