PROGS=$@

for PROG in ${PROGS}; do
	echo "extern int ${PROG}_main(int argc, char *argv[], char *envp[]);"
done

echo # Extra newline
echo "struct stub entry_points[] = {"
echo "	{ EXECNAME, crunched_main },"
for PROG in ${PROGS}; do
	echo "	{ \"${PROG}\", ${PROG}_main },"
done
echo "	{ NULL, NULL }"
echo "};"
