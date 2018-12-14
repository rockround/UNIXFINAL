#!/bin/bash
goodVals=0;
time=$(date +%s)
if [ $1 == "s" ]
then
	stopTime=$((time+$2))
	trials=0;
	while [ $(date +%s) -le $stopTime ]
	do
		trials=$((trials+1))
		rand1=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`;
		rand2=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`;
		if (( `echo "scale = 7; sqrt( $rand1*$rand1 + $rand2*$rand2) <= 1"|bc -l` ));then
			goodVals=$((goodVals + 1));
		fi
	done
	echo `echo "4*$goodVals / $trials"|bc -l`
	echo $trials
elif [ $1 == "t" ]
then
	trials=$(($2+0));
	for i in `seq 1 $trials`;
	do
		rand1=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`;
		rand2=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`;
		if (( `echo "scale=7; sqrt( $rand1*$rand1 + $rand2*$rand2) <= 1"|bc -l` ));then
			goodVals=$((goodVals + 1));
		fi
	done
	echo $trials"	"
	echo $(($(date +%s)-time))"	"
	pihat=`echo "4*$goodVals / $trials"|bc -l`
	echo $pihat"	"
	diff=`echo "scale=7; $pihat - 3.1415926535898" | bc -l`
	if (( `echo "$diff < 0" | bc -l` ))
	then
		diff=` echo "scale=13; $diff * -1" | bc -l`;
	fi
	echo $diff"	"
	echo `echo "scale=7; $diff / 3.1415926535898"|bc -l`"	"
fi

