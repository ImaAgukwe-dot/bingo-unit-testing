# Revision History -- at the bottom of the document
################################################################################
# The targets in this file are used in .gitlab-ci.yml and  the files created
# are found in the .gitignore
################################################################################
# Changing any names below can change the target names which will require that
# you update .gitlab_ci.yml and .gitignore
################################################################################

################################################################################
# Variable definitions
################################################################################

# Executable names
PROJECT = bingo
GTEST_CLEAN = test_clean
GTEST_BUGGY = test_buggy

# Compilation command and flags
CXX=g++
CXXVERSION= -std=c++14
CXXFLAGS= ${CXXVERSION} -g
LINKFLAGS= -lgtest

# Directories
BUGGY_OBJ_DIR = buggy_obj
CLEAN_OBJ_DIR = clean_obj
GTEST_DIR = test
GTEST_OBJ_DIR = test_obj
TEST_OUTPUT = ${GTEST_DIR}/output
SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

# Output Files
CARD = bingoCardTest
VALID = validityDisplayTest
INVALID = invalidDisplayTest
INSTRUCTIONS = bingoInstructions
VALID_CHECK = validityCheckDisplayTest
INSTRUCTIONS = bingoInstructions

# Tool variables
GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = results.coverage

COVERAGE_DIR = coverage
STATIC_ANALYSIS = cppcheck
STYLE_CHECK = cpplint
DESIGN_DIR = docs/design
DOXY_DIR = docs/code

################################################################################
# Targets
################################################################################

# Default goal
.DEFAULT_GOAL := compileProject

################################################################################
# Clean-up targets
################################################################################

.PHONY: clean-docs
clean-docs:
	rm -rf docs/code/src/html docs/code/src/doxyErrors.txt

.PHONY: clean-exec
clean-exec:
	rm -rf ${PROJECT} ${GTEST_CLEAN} ${GTEST_CLEAN}.exe \
	${GTEST_BUGGY} ${GTEST_BUGGY}.exe \
	${TEST_OUTPUT}/*.actual

.PHONY: clean-obj
clean-obj:
	rm -rf ${GTEST_DIR}/Test*.o ${GTEST_DIR}/main.o \
	Test*.o main.o

.PHONY: clean-temp
clean-temp:
	rm -rf *~ \#* .\#* \
	${GTEST_DIR}/*~ ${GTEST_DIR}/\#* ${GTEST_DIR}/.\#* \
	${SRC_INCLUDE}/*~ ${SRC_INCLUDE}/\#* ${SRC_INCLUDE}/.\#* \
	${DESIGN_DIR}/*~ ${DESIGN_DIR}/\#* ${DESIGN_DIR}/.\#* \
	*.gcov *.gcda *.gcno 

.PHONY: clean
clean: clean-docs clean-exec clean-obj clean-temp

################################################################################
# Compilaton targets
################################################################################

# default rule for compiling .cpp to .o
%.o: %.cpp
	${CXX} ${CXXVERSION} -c $< -o $@

# Compilation targets

# compilation for performing testing on the buggy code
# using the files in include, buggy_obj, and test
${GTEST_BUGGY}: ${GTEST_DIR} ${GTEST_OBJ_DIR} ${BUGGY_OBJ_DIR}
	${CXX} ${CXXVERSION} -o ./${GTEST_BUGGY} ${INCLUDE} \
	${GTEST_DIR}/*.cpp ${GTEST_OBJ_DIR}/*.o ${BUGGY_OBJ_DIR}/*.o \
	${LINKFLAGS}

# compilation for performing testing on the bug-free code
# using the files in include, clean_obj, and test
${GTEST_CLEAN}: ${GTEST_DIR} ${GTEST_OBJ_DIR} ${CLEAN_OBJ_DIR}
	${CXX} ${CXXVERSION} -o ./${GTEST_CLEAN} ${INCLUDE} \
	${GTEST_DIR}/*.cpp ${GTEST_OBJ_DIR}/*.o ${CLEAN_OBJ_DIR}/*.o \
	${LINKFLAGS}

################################################################################
# Test targets
################################################################################

# To perform all tests with the clean library
all_clean: ${GTEST_CLEAN} test_output_diff_clean memcheck_clean docs static style

all_buggy: ${GTEST_BUGGY} test_output_diff_buggy memcheck_buggy docs static style

all: ${GTEST_CLEAN} test_output_diff_clean memcheck_clean ${GTEST_BUGGY} test_output_diff_buggy memcheck_buggy docs static style

# To compare actual and expected output
.PHONY: test_output_diff_clean 
test_output_diff_clean: ${GTEST_CLEAN}
	./${GTEST_CLEAN}
	diff -s ${TEST_OUTPUT}/${CARD}.actual ${TEST_OUTPUT}/${CARD}.expected
	diff -s ${TEST_OUTPUT}/${VALID}.actual ${TEST_OUTPUT}/${VALID}.expected
	diff -s ${TEST_OUTPUT}/${INVALID}.actual ${TEST_OUTPUT}/${INVALID}.expected
	diff -s ${TEST_OUTPUT}/${VALID_CHECK}.actual ${TEST_OUTPUT}/${VALID_CHECK}.expected
	diff -s ${TEST_OUTPUT}/${INSTRUCTIONS}.actual ${TEST_OUTPUT}/${INSTRUCTIONS}.expected

.PHONY: test_output_diff_buggy
test_output_diff_buggy: ${GTEST_BUGGY}
	./${GTEST_BUGGY}
	diff -s ${TEST_OUTPUT}/${CARD}.actual ${TEST_OUTPUT}/${CARD}.expected
	diff -s ${TEST_OUTPUT}/${VALID}.actual ${TEST_OUTPUT}/${VALID}.expected
	diff -s ${TEST_OUTPUT}/${INVALID}.actual ${TEST_OUTPUT}/${INVALID}.expected
	diff -s ${TEST_OUTPUT}/${VALID_CHECK}.actual ${TEST_OUTPUT}/${VALID_CHECK}.expected
	diff -s ${TEST_OUTPUT}/${INSTRUCTIONS}.actual ${TEST_OUTPUT}/${INSTRUCTIONS}.expected

# To perform the memory checks
memcheck_clean: ${GTEST_CLEAN}
	valgrind --tool=memcheck --leak-check=yes ./${GTEST_CLEAN}

fullmemcheck_clean: ${GTEST_CLEAN}
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./${GTEST_CLEAN}

memcheck_buggy: ${GTEST_BUGGY}
	valgrind --tool=memcheck --leak-check=yes ./${GTEST_BUGGY}

fullmemcheck_buggy: ${GTEST_BUGGY}
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./${GTEST_BUGGY}

# To perform the static check on all .cpp files in test



static: ${GTEST_DIR}
	${STATIC_ANALYSIS} --verbose --enable=all ${GTEST_DIR} \
	${SRC_INCLUDE} --suppress=missingInclude --suppress=missingIncludeSystem --error-exitcode=1

# To perform the style check on all .cpp files in test and .h files in include
style: ${GTEST_DIR} ${SRC_INCLUDE}
	${STYLE_CHECK} ${GTEST_DIR}/* ${SRC_INCLUDE}/*	

################################################################################
# Documentation target
################################################################################

# To produce the documentation
.PHONY: docs
docs: ${SRC_INCLUDE}
	doxygen ${DOXY_DIR}/doxyfile

################################################################################
# Revision History
################################################################################
# Updated: 2023-11-07 Nicole Wilson [n.wilsong@uleth.ca]
# to perform tests for both the buggy and clean libraries
################################################################################
# Updated: 2023-10-19 Nicole Wilson <n.wilson@uleth.ca>
#  Updated and added compilation targets so that compilation normally doesn't
# use -g (debug - includes source code) but targets that do use it are available.
################################################################################
# Updated: 2022-12-15 Nicole Wilson <n.wilson@uleth.ca>
#  Removed all references to OS as the pipelines are now running on Ubuntu
################################################################################
# Updated: 2022-10-19 Dr. J. Anvik <john.anvik@uleth.ca>
#  Changed the static command to make the pipeline fail on exit with errors.
################################################################################
# Updated: 2022-09-11 Nicole Wilson <n.wilson@uleth.ca>
#  Added reference to OS in setting of STYLE_CHECK.
#  This is a temporary measure until the pipelines are running on Ubuntu
################################################################################
