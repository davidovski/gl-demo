PROG=gltest
CC=gcc

${PROG}: ${PROG}.c
	${CC} ${PROG}.c -o ${PROG} `pkg-config -libs glfw3 gl glew`
