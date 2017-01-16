COLOR_GREEN=\e[0;32m
COLOR_RED=\e[0;31m
COLOR_NC=\e[0m

ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

TESTFAIL=(echo $$'${COLOR_RED}$@ failed${COLOR_NC}' && exit 1)
TESTSUCCESS=@echo $$'${COLOR_GREEN}$@ succeeded${COLOR_NC}'

PRINT=@echo $$'\e[1;34mBuilding $<\e[0m'


### DEFAULTS ###################################################################

all: clean all-tests

all-tests: bin/vector-test bin/orientation-test bin/pathsegment-test bin/kinematicresult-test bin/ik-solver-test bin/motorcontroller-test

clean:
	@rm -rf bin/* *.o

ensure-bin-folder:
	@mkdir -p bin

### VECTOR TEST ################################################################

vector.o: vector.cpp
	@g++ -g -c vector.cpp -o vector.o

bin/vector-test: vector.o test/vector-test.cpp ensure-bin-folder
	@g++ -I${ROOT_DIR} -o bin/vector-test test/vector-test.cpp
	@chmod +x bin/vector-test
	@bin/vector-test || $(TESTFAIL)
	$(TESTSUCCESS)


### ORIENTATION TEST ###########################################################

orientation.o: orientation.cpp
	@g++ -g -c orientation.cpp -o orientation.o

bin/orientation-test: orientation.o test/orientation-test.cpp ensure-bin-folder
	@g++ -I${ROOT_DIR} -o bin/orientation-test test/orientation-test.cpp
	@chmod +x bin/orientation-test
	@bin/orientation-test || $(TESTFAIL)
	$(TESTSUCCESS)


### PATHSEGMENT TEST ###########################################################

pathsegment.o: pathsegment.cpp
	@g++ -g -c pathsegment.cpp -o pathsegment.o

bin/pathsegment-test: pathsegment.o test/pathsegment-test.cpp ensure-bin-folder
	@g++ -I${ROOT_DIR} -o bin/pathsegment-test test/pathsegment-test.cpp
	@chmod +x bin/pathsegment-test
	@bin/pathsegment-test || $(TESTFAIL)
	$(TESTSUCCESS)


### KINEMATICRESULT TEST #######################################################

kinematicresult.o: kinematicresult.cpp
	@g++ -g -c kinematicresult.cpp -o kinematicresult.o

bin/kinematicresult-test: kinematicresult.o test/kinematicresult-test.cpp ensure-bin-folder
	@g++ -I${ROOT_DIR} -o bin/kinematicresult-test test/kinematicresult-test.cpp
	@chmod +x bin/kinematicresult-test
	@bin/kinematicresult-test || $(TESTFAIL)
	$(TESTSUCCESS)


### IKSolver TEST ##############################################################

ik-solver.o: ik-solver.cpp
	@g++ -g -c ik-solver.cpp -o ik-solver.o

bin/ik-solver-test: ik-solver.o test/ik-solver-test.cpp ensure-bin-folder
	@g++ -I${ROOT_DIR} -o bin/ik-solver-test test/ik-solver-test.cpp
	@chmod +x bin/ik-solver-test
	@bin/ik-solver-test || $(TESTFAIL)
	$(TESTSUCCESS)


### MOTORCONTROLLER TEST #######################################################

motorcontroller.o: motorcontroller.cpp
	@g++ -std=c++11 -g -I${ROOT_DIR}/test/mocks -c motorcontroller.cpp -o motorcontroller.o

bin/motorcontroller-test: motorcontroller.o test/motorcontroller-test.cpp ensure-bin-folder
	@g++ -std=c++11 -g -I${ROOT_DIR}/test/mocks -I${ROOT_DIR} -o bin/motorcontroller-test test/motorcontroller-test.cpp
	@chmod +x bin/motorcontroller-test
	@bin/motorcontroller-test || $(TESTFAIL)
	$(TESTSUCCESS)
