#! /bin/bash
for ((a=1; a<=100000 ; a++))
do
	rm -rf  ./team1
	rm -rf  ./team2
	rm -rf  ./team3
	rm -rf  ./team4
	git clone https://github.com/herebiohazarhackathon/team1.git
	git clone https://github.com/herebiohazarhackathon/team2.git
	git clone https://github.com/herebiohazarhackathon/team3.git
	git clone https://github.com/herebiohazarhackathon/team4.git
	sleep 10
done
