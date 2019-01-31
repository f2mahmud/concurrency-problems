#!/bin/bash

echo "values $1 $2 $3 $4"
echo "Original:"
/usr/bin/time -f "%Uu %Ss %E" ./../returnglobal $1 $2 $3 $4
echo "Updated: "
/usr/bin/time -f "%Uu %Ss %E" ./returnglobal $1 $2 $3 $4

