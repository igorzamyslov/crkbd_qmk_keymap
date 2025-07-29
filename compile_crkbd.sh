set -euo pipefail

qmk json2c -o keyboards/crkbd/keymaps/miryoku_based/keymap.c keyboards/crkbd/keymaps/miryoku_based/_keymap.json
qmk compile -kb crkbd/rev4_1/standard -km miryoku_based
mkdir -p out
mv *.uf2 out/
