#! /bin/bash
i=0
for ((a=1; a<=100000 ; a++ , i++))
do
	if [ $i = 30 ] ; then
		rm -rf  ./team1
		rm -rf  ./team2
		rm -rf  ./team3
		rm -rf  ./team4
		git clone https://github.com/herebiohazarhackathon/team1.git
		git clone https://github.com/herebiohazarhackathon/team2.git
		git clone https://github.com/herebiohazarhackathon/team3.git
		git clone https://github.com/herebiohazarhackathon/team4.git
		((i=0))
	fi
	./game_engine
	printf $i
	#sleep 1
done
