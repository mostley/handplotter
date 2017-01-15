COLOR_GREEN=\e[0;32m
COLOR_RED=\e[0;31m
COLOR_NC=\e[0m

ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

TESTFAIL=(echo $$'${COLOR_RED}$@ failed${COLOR_NC}' && exit 1)
TESTSUCCESS=@echo $$'${COLOR_GREEN}$@ succeeded${COLOR_NC}'

PRINT=@echo $$'\e[1;34mBuilding $<\e[0m'


### DEFAULTS ###################################################################

all: clean all-tests

all-tests: test/vector test/orientation test/pathsegment test/kinematicresult test/ik-solver

clean:
	@rm -f vector.o test/vector orientation.o test/orientation pathsegment.o test/pathsegment kinematicresult.o test/kinematicresult ik-solver.o test/ik-solver


### VECTOR TEST ################################################################

vector.o: vector.cpp
	@g++ -g -c vector.cpp -o vector.o

test/vector: vector.o test/vector-test.cpp
	@g++ -I${ROOT_DIR} -o test/vector test/vector-test.cpp
	@chmod +x test/vector
	@test/vector || $(TESTFAIL)
	$(TESTSUCCESS)


### ORIENTATION TEST ###########################################################

orientation.o: orientation.cpp
	@g++ -g -c orientation.cpp -o orientation.o

test/orientation: orientation.o test/orientation-test.cpp
	@g++ -I${ROOT_DIR} -o test/orientation test/orientation-test.cpp
	@chmod +x test/orientation
	@test/orientation || $(TESTFAIL)
	$(TESTSUCCESS)


### PATHSEGMENT TEST ###########################################################

pathsegment.o: pathsegment.cpp
	@g++ -g -c pathsegment.cpp -o pathsegment.o

test/pathsegment: pathsegment.o test/pathsegment-test.cpp
	@g++ -I${ROOT_DIR} -o test/pathsegment test/pathsegment-test.cpp
	@chmod +x test/pathsegment
	@test/pathsegment || $(TESTFAIL)
	$(TESTSUCCESS)


### KINEMATICRESULT TEST ###########################################################

kinematicresult.o: kinematicresult.cpp
	@g++ -g -c kinematicresult.cpp -o kinematicresult.o

test/kinematicresult: kinematicresult.o test/kinematicresult-test.cpp
	@g++ -I${ROOT_DIR} -o test/kinematicresult test/kinematicresult-test.cpp
	@chmod +x test/kinematicresult
	@test/kinematicresult || $(TESTFAIL)
	$(TESTSUCCESS)


### IKSolver TEST ###########################################################

ik-solver.o: ik-solver.cpp
	@g++ -g -c ik-solver.cpp -o ik-solver.o

test/ik-solver: ik-solver.o test/ik-solver-test.cpp
	@g++ -I${ROOT_DIR} -o test/ik-solver test/ik-solver-test.cpp
	@chmod +x test/ik-solver
	@test/ik-solver || $(TESTFAIL)
	$(TESTSUCCESS)
