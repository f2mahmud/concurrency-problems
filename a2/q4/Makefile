CXX = u++				# compiler
CXXFLAGS = -g -Wall -Wextra -MMD -std=c++11 
EXEC1= q4
EXEC2 = mq4
EXECS = ${EXEC1} ${EXEC2}

all: ${EXECS}

${EXEC1}: 
	${CXX} ${CXXFLAGS} ${EXEC1}.cc -o ${EXEC1}
${EXEC2}: 
	${CXX} ${CXXFLAGS} -multi ${EXEC1}.cc -o ${EXEC2} 

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC1} ${EXEC2}
