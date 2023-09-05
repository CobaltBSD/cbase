#!/usr/bin/zsh

PROG=${1}

while read LINE; do
	NMOUT=(`echo ${LINE}`)
	objcopy --redefine-sym ${NMOUT[3]}=${PROG}_${NMOUT[3]} ${PROG}.o
done < <(nm --defined-only ${PROG}.o)

