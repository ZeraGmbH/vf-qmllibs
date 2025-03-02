#!/bin/sh

po_dir=$(dirname "$0")
for po_file in `find "$po_dir" -name '*.po'`; do
    language=`basename "$po_file" | sed 's:.po::'` 
    ts_filename="timezones_$language.ts"
    echo "Creating $ts_filename..."
    lconvert -locations none --target-language "$language" $po_file -o "$po_dir/$ts_filename"
done
