#!/bin/bash

rm -f 'headers.am'

FILES=`find . | grep '\.h$' | sed 's/^\.\///g'`

echo -n 'nobase_include_HEADERS = ' >> 'headers.am'

for A in $FILES; do
	echo '\' >> 'headers.am'
	echo -n "$A " >> 'headers.am'
done
