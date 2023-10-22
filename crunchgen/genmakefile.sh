#!/usr/bin/zsh

echo "all: entry_points.h"

PROGS=()

TOTALOBJS=()

EXECNAME=${EXECNAME:=crunchgen}

while read LINE; do
	BUILDRULE=(`echo ${LINE}`)
	PROG=${BUILDRULE[1]}
	PROGS+=${PROG}
	OBJS=()

	unset 'BUILDRULE[1]'
	SRCS=(${BUILDRULE[@]})

	for SRC in ${SRCS}; do
		OBJ=${SRC%.*}.o
		OBJS+=${OBJ}
		TOTALOBJS+=${OBJ}
		echo "	\${CC} \${CFLAGS} -I${PROG} -c ${PROG}/${SRC} -o ${PROG}/${OBJ}"
	done
	echo "	\${LD} \${LDFLAGS} -r $(printf "${PROG}/%s " ${OBJS}) -o ${PROG}.o" # Combine all objects of the executable into one
	echo "	$(dirname $0)/manglesymbols.sh ${PROG}"
done < crunchgen.conf

if [[ ${EXECNAME} != crunchgen ]]; then
	EXECNAMEFLAG=-DEXECNAME=\\\"${EXECNAME}\\\"
fi

echo "	\${CC} \${CFLAGS} -Wno-deprecated-non-prototype $(dirname $0)/crunchgen.c $(printf "%s.o " ${PROGS}) ${LIBS} ${EXECNAMEFLAG} -o $(dirname $0)/${EXECNAME}"
echo "	rm -fv $(printf "%s.o " ${PROGS}) $(dirname $0)/entry_points.h ${TOTALOBJS}" # Delete intermediary objects
echo
echo "entry_points.h:"
echo "	$(dirname $0)/mkentrypoints.sh ${PROGS} > $(dirname $0)/entry_points.h"
