OPT:= -multi # -O2
MIMPL:=COFOR_
BIMPL:=NOBUSY
TYPE:=int
SENTINEL:=-1

CXX = u++					# compiler
CXXFLAGS = -g ${OPT} -Wall -Wextra -MMD -std=c++14 -D"${MIMPL}" -D"${BIMPL}" \
		   -DTYPE="${TYPE}" -DSENTINEL="${SENTINEL}" # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS2 = q3main.o q3consumer.o q3producer.o
EXEC2 = buffer					# 2nd executable name

OBJECTS = ${OBJECTS1} ${OBJECTS2}		# all object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1} ${EXEC2}			# all executables

#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables

-include BufImpl

ifeq (${BUFIMPL},${BIMPL})			# same implementation type as last time ?
${EXEC2} : ${OBJECTS2}
	${CXX} ${CXXFLAGS} $^ -o $@
else
ifeq (${BIMPL},)				# no implementation type specified ?
# set type to previous type
BIMPL=${BUFIMPL}
${EXEC2} : ${OBJECTS2}
	${CXX} ${CXXFLAGS} $^ -o $@
else						# implementation type has changed
.PHONY : ${EXEC2}
${EXEC2} :
	rm -f BufImpl
	touch q3buffer.h
	sleep 1
	${MAKE} ${EXEC2} BIMPL="${BIMPL}"
endif
endif

BufImpl :
	echo "BUFIMPL=${BIMPL}" > BufImpl
	sleep 1

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXECS} MatrixImpl BufImpl
