#!/bin/bash
set -xeuo pipefail

SCRIPT_DIR=$(dirname "$(realpath "$0")")
QMK_FIRMWARE_DIR="${HOME}"/Projects/qmk_firmware

qmk json2c "${SCRIPT_DIR}"/_keymap.json -o "${SCRIPT_DIR}"/keymap.c
qmk compile --clean -kb crkbd/rev4_1/standard -km miryoku_based

mkdir -p "${SCRIPT_DIR}"/out
mv "${QMK_FIRMWARE_DIR}"/*.uf2 "${SCRIPT_DIR}"/out/
cp "${SCRIPT_DIR}"/out/*.uf2 /System/Volumes/Data/Volumes/RPI-RP2
