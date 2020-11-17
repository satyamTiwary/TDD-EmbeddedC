#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = tdd
TARGET_LIB = \
	lib/lib$(COMPONENT_NAME).a
	
TEST_TARGET = \
	$(COMPONENT_NAME)_tests

#--- Inputs ----#
PROJECT_HOME_DIR = .
CPP_PLATFORM = Gcc
CPPUTEST_HOME = ./libs/cpputest

SRC_DIRS = \
	src/*\

TEST_SRC_DIRS = \
	tests \
	tests/devices \
	tests/scheduler \
	mocks
	
INCLUDE_DIRS =\
  $(CPPUTEST_HOME)/include/\
  include/*\
  mocks
  
CPPUTEST_USE_EXTENSIONS = Y
include ./CppUTestCompileFlags.mk
include $(CPPUTEST_HOME)/build/MakefileWorker.mk