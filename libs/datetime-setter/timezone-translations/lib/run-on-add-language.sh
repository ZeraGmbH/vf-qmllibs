#!/bin/sh

LCONVERT=lconvert-qt5
LRELEASE=lrelease-qt5

po_dir=$(dirname "$0")
for po_file in `find "$po_dir" -name '*.po'`; do
    language=`basename "$po_file" | sed 's:.po::'` 
    ts_filename="timezones_$language.ts"
    echo "Creating $ts_filename..."
    $LCONVERT -locations none --target-language "$language" $po_file -o "$po_dir/$ts_filename"

    qm_filename="timezones_$language.qm"
    echo "Creating $qm_filename..."
    $LRELEASE "$po_dir/$ts_filename"
done
