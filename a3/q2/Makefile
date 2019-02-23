OPT:= -multi # -O2
MIMPL:=TASK

CXX = u++					# compiler
CXXFLAGS = -g ${OPT} -Wall -Wextra -MMD -std=c++14 -D"${MIMPL}"
		
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = q2main.o q2printer.o q2task.o
EXEC1 = matrixmultiply				# 1st executable name



OBJECTS = ${OBJECTS1}		# all object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1}			# all executables

#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables

-include MatrixImpl

ifeq (${MATRIXIMPL},${MIMPL})			# same implementation type as last time ?

${EXEC1} :	${OBJECTS1}
	${CXX} ${CXXFLAGS} $^ -o $@
else

ifeq (${MIMPL},)				# no implementation type specified ?
# set type to previous type

MIMPL=${MATRIXIMPL}
${EXEC1} :	${OBJECTS1}
	${CXX} ${CXXFLAGS} $^ -o $@

else						# implementation type has changed
.PHONY : ${EXEC1}
${EXEC1} :
	rm -f MatrixImpl
	touch q2matrixmultiply.h
	${MAKE} ${EXEC1} MIMPL=${MIMPL}
endif
endif

MatrixImpl :
	echo "MATRIXIMPL=${MIMPL}" > MatrixImpl
	sleep 1


#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXECS} MatrixImpl
