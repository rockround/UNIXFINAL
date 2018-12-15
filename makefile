makePi: pi.c 
	gcc $^ -o pi -lgsl -L$$HOME/local/gsl-2.5/lib -lgslcblas -I$$HOME/local/gsl-2.5/include
makeDealer: dealer.c
	gcc $^ -o dealer -lgsl -L$$HOME/local/gsl-2.5/lib -lgslcblas -I$$HOME/local/gsl-2.5/include
makeHand: hand.c
	gcc $^ -o Hand -lgsl -L$$HOME/local/gsl-2.5/lib -lgslcblas -I$$HOME/local/gsl-2.5/include
makeBoss: pitboss.c
	gcc $^ -o pitboss
makeMighty: mighty.c
	gcc $^ -o mighty
makeTerminator: terminator.c
	gcc $^ -o terminator -lm -lgsl -L$$HOME/local/gsl-2.5/lib -lgslcblas -I$$HOME/local/gsl-2.5/include
