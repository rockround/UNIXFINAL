#!/bin/bash
goodVals=0;
trials=$(($1+20));
for i in `seq 1 $trials`;
do
	rand1=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`;
	rand2=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`;
	if (( `echo "sqrt( $rand1*$rand1 + $rand2*$rand2) <= 1"|bc -l` ));
	then
		goodVals=$((goodVals + 1));
	fi
done
echo `echo "4*$goodVals / $trials"|bc -l`
