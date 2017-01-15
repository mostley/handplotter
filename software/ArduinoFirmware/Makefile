COLOR_GREEN=\e[0;32m
COLOR_RED=\e[0;31m
COLOR_NC=\e[0m

ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

TESTFAIL=(echo $$'${COLOR_RED}$@ failed${COLOR_NC}' && exit 1)
TESTSUCCESS=@echo $$'${COLOR_GREEN}$@ succeeded${COLOR_NC}'

PRINT=@echo $$'\e[1;34mBuilding $<\e[0m'

vector.o: vector.cpp
	@g++ -g -c vector.cpp -o vector.o

test/vector: vector.o test/vector-test.cpp
	@g++ -I${ROOT_DIR} -o test/vector test/vector-test.cpp
	@chmod +x test/vector
	@test/vector || $(TESTFAIL)
	$(TESTSUCCESS)

all-tests: test/vector

clean:
	@rm -f vector.o test/vector

all: all-tests
