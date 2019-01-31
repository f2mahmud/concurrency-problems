CXX = g++				# compiler
CXXFLAGS = -g -Wall -Wextra -MMD -std=c++11
EXEC1= q1internal
EXEC2 = q1external
EXECS = ${EXEC1} ${EXEC2}

all: ${EXECS}

${EXEC1}: 
	${CXX} ${CXXFLAGS} ${EXEC1}.cc -o ${EXEC1}
${EXEC2}: 
	${CXX} ${CXXFLAGS} ${EXEC2}.cc -o ${EXEC2}

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC1} ${EXEC2}
