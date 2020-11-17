# https://github.com/jwgrenning/cpputest-starter-project/blob/master/makefile
#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = tdd

#--- Inputs ----#
PROJECT_HOME_DIR = .
CPPUTEST_HOME = ./cpputest
ifeq "$(CPPUTEST_HOME)" ""
$(error The environment variable CPPUTEST_HOME is not set. \
Set it to where cpputest is installed)
endif

# SRC_FILES += src/Example.cpp
SRC_FILES += src/devices/MotorController.cpp

TEST_SRC_FILES += tests/devices/MotorController.cpp

TEST_SRC_DIRS += tests
TEST_SRC_DIRS += tests/devices

# --- MOCKS_SRC_DIRS ---
# MOCKS_SRC_DIRS specifies a directories where you can put your
# mocks, stubs and fakes.  You can also just put them in TEST_SRC_DIRS
MOCKS_SRC_DIRS +=

# Turn on CppUMock
CPPUTEST_USE_EXTENSIONS = Y

# INCLUDE_DIRS are searched in order after the included file's
# containing directory
INCLUDE_DIRS += $(CPPUTEST_HOME)/include
INCLUDE_DIRS += $(CPPUTEST_HOME)/include/Platforms/Gcc
INCLUDE_DIRS += include
INCLUDE_DIRS += include/devices
# INCLUDE_DIRS += tests/exploding-fakes

# --- CPPUTEST_OBJS_DIR ---
CPPUTEST_OBJS_DIR = build/obj

CPPUTEST_LIB_DIR = build/lib

# --- LD_LIBRARIES -- Additional needed libraries can be added here.
# commented out example specifies math library
#LD_LIBRARIES += -lm

include targets.mk

include CppUTestCompileFlags.mk
include $(CPPUTEST_HOME)/build/MakefileWorker.mk

# --- TEST ---
test: cpputest/lib/libCppUTest.a

cpputest/lib/libCppUTest.a:
	cd cpputest; autoreconf . -i && ./configure && make tdd
