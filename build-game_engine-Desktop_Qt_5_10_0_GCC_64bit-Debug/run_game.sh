#! /bin/bash
for ((a=1; a<=100000 ; a++))
do
	./game_engine
	printf "run step \n"
	sleep 1
done
