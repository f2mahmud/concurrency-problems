#/!/bin/bash

echo "running external 1 args = 10000 2500"

/usr/bin/time -f "%Uu %Ss %E" ./q1external 10000 2500 > /dev/null
 
echo "running external 2 args = 10000 5000"

/usr/bin/time -f "%Uu %Ss %E" ./q1external 10000 5000 > /dev/null
 
echo "running external 3 args = 15000 2500"

/usr/bin/time -f "%Uu %Ss %E" ./q1external 15000 2500 > /dev/null
 
echo "running external 4 args = 15000 5000"

/usr/bin/time -f "%Uu %Ss %E" ./q1external 15000 5000 > /dev/null
 
echo "running external 4 args = 15000 5000"



echo "running internal 1 args = 10000 2500"

/usr/bin/time -f "%Uu %Ss %E" ./q1internal 10000 2500 > /dev/null
 
echo "running internal 2 args = 10000 5000"

/usr/bin/time -f "%Uu %Ss %E" ./q1internal 10000 5000 > /dev/null
 
echo "running internal 3 args = 15000 2500"

/usr/bin/time -f "%Uu %Ss %E" ./q1internal 15000 2500 > /dev/null
 
echo "running internal 4 args = 15000 5000"

/usr/bin/time -f "%Uu %Ss %E" ./q1internal 15000 5000 > /dev/null
