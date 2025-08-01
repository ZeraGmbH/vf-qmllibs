#!/bin/sh

basedir=`dirname -- "$( readlink -f -- "$0"; )";`
resourcefile="$basedir/test-svgs.qrc"

rm -f $resourcefile
echo '<RCC>' >> $resourcefile
echo '    <qresource prefix="/">' >> $resourcefile

cd $basedir
for svgfile in `find 'svgs' -name '*.svg'`; do
    echo '        <file>'$svgfile'</file>' >> $resourcefile
done

echo '    </qresource>' >> $resourcefile
echo '</RCC>' >> $resourcefile

