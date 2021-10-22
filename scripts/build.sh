#!/bin/bash -xe

BUILD_DIR="${BUILD_DIR:?BUILD_DIR variable is not defined}"
BUILD_TARGET="${BUILD_FINAL_TARGET:-test}"

JOBS_NUM="$(( $(nproc 2>/dev/null || sysctl -n hw.ncpu) + 1 ))"
MAKE_ARGS="${MAKE_ARGS:-"-j$JOBS_NUM"}"

cd "$(dirname "$0")/.."

git submodule update --init

# see clang-tidy build in ci.yml github workflow
if [ "${BUILD_TARGET}" != "generated" ]
then
  cmake . -B"${BUILD_DIR}" -DBUILD_TESTS=ON "$@"
  cmake --build "${BUILD_DIR}" -- "${MAKE_ARGS}"
else
  cmake . -B"${BUILD_DIR}"
  cmake --build "${BUILD_DIR}" --target "${BUILD_TARGET}" -- "${MAKE_ARGS}"
fi
