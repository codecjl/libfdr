#!/usr/bin/bash

#echo " $1"

python3 -c '
import random

import sys
#print(sys.argv)

for i in range(0, int(sys.argv[1]) ):
    #print(i)
    print(random.randint(1,1000000))
' $1

