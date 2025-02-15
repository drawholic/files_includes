
CXX = g++
CXX_FLAGS = -I include -c

BUILD_DIR = build

SRC_DIR = src

all: ${BUILD_DIR}/main.o

${BUILD_DIR}/main.o: ${BUILD_DIR}/Preprocessor.o ${BUILD_DIR}/FileNode.o ${SRC_DIR}/main.cpp
	${CXX} -I include $^ -o $@

# PREPROCESSOR
${BUILD_DIR}/Preprocessor.o: ${BUILD_DIR}/FileNode.o ${SRC_DIR}/Preprocessor.cpp
	${CXX} ${CXX_FLAGS} $^ -o $@

# FILENODE
${BUILD_DIR}/FileNode.o: ${SRC_DIR}/FileNode.cpp
	${CXX} ${CXX_FLAGS} $^ -o $@



