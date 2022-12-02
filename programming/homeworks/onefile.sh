#!/bin/sh

IN_DIR="$1"
OUT="$2"

echo "// DISCLAIMER: из-за непонятного ограничения на кол-во загружаемых файлов пришлось загрузить ДЗ одним файлом." >> $OUT
for f in $IN_DIR/*; do
	printf "\n// $(basename "$f")\n" >> $OUT
	cat "$f" >> $OUT
done
