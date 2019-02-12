OPT:= -multi -O2 -nodebug

CXX = u++					# compiler
CXXFLAGS = -g ${OPT} -Wall -Wextra -MMD -std=c++14 
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECT = q1.cc

EXEC1 = q1array
EXEC2 = q1vector1	
EXEC3 = q1vector2
EXEC4 = q1stack

EXECS = ${EXEC1} ${EXEC2} ${EXEC3} ${EXEC4}

all: ${EXECS}

${EXEC1}:
	${CXX}  ${CXXFLAGS} -DDARRAY q1.cc -o ${EXEC1}

${EXEC2}:
	${CXX} q1.cc ${CXXFLAGS} -DVECTOR1 -o ${EXEC2}
	
${EXEC3}:
	${CXX} q1.cc ${CXXFLAGS} -DVECTOR2 -o ${EXEC3}
	
${EXEC4}:
	${CXX} q1.cc ${CXXFLAGS} -DSTACK -o ${EXEC4}
	

#############################################################

.PHONY : all clean

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXECS} MatrixImpl BufImpl
