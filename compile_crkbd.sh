set -euo pipefail

SCRIPT_DIR=$(dirname "$(realpath "$0")")

qmk json2c "${SCRIPT_DIR}/_keymap.json" -o "${SCRIPT_DIR}/keymap.c"
qmk compile --clean -kb crkbd/rev4_1/standard -km miryoku_based
mkdir -p out
mv *.uf2 out/
