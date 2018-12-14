#!/bin/bash

echo `awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`
