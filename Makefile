
CXX = g++
CXX_FLAGS = -I include -c

BUILD_DIR = build

TEST_DIR = tests

SRC_DIR = src

all: ${BUILD_DIR}/main

${BUILD_DIR}/main: ${BUILD_DIR}/Preprocessor.o ${BUILD_DIR}/FileNode.o ${SRC_DIR}/main.cpp
	${CXX} -I include $^ -o $@

# PREPROCESSOR
${BUILD_DIR}/Preprocessor.o: ${BUILD_DIR}/FileNode.o ${SRC_DIR}/Preprocessor.cpp
	${CXX} ${CXX_FLAGS} $^ -o $@

# FILENODE
${BUILD_DIR}/FileNode.o: ${SRC_DIR}/FileNode.cpp
	${CXX} ${CXX_FLAGS} $^ -o $@


test: ${TEST_DIR}/FileNodeTest.o
	./$^

${TEST_DIR}/FileNodeTest.o: ${TEST_DIR}/FileNode/test1.cpp ${BUILD_DIR}/FileNode.o
	${CXX} $^ -I include -o $@



