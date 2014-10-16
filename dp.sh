#!/bin/sh
Check=./right
Now=./my
while true; do
./data < 1.txt
$Check
$Now
diff -b ou.txt ou.ans -q
if [ $? -eq 0 ]; then
   echo "Accpeted"
else {
   echo "Wrong Answer"
   break
}
fi
done