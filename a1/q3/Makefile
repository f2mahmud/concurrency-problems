CXX = u++				# compiler
CXXFLAGS = -g -Wall -Wextra -MMD -Wno-implicit-fallthrough # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}# makefile name

OBJECTS5 = q3printf.o q3main.o		# 5th executable object files
EXEC5 = printf				# 5th executable name

OBJECTS = ${OBJECTS1} ${OBJECTS2} ${OBJECTS3} ${OBJECTS4} ${OBJECTS5}
DEPENDS = ${OBJECTS:.o=.d}
EXECS = ${EXEC1} ${EXEC2} ${EXEC3} ${EXEC4} ${EXEC5}

${EXEC5} : ${OBJECTS5}			# compile and link 5th executable
	${CXX} ${CXXFLAGS} $^ -o $@

${OBJECTS} : ${MAKEFILE_NAME}		# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}			# include *.d files containing program dependences

clean :					# remove files that can be regenerated
	rm -f *.d *.o ${EXEC01} ${EXEC02} ${EXECS}
	
