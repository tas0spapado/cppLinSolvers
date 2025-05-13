SRC_FILE = test-swap.cpp
TARGET_NAME = test-swap
BUILD_MODE = RELEASE

# FLAGS 
OPT_FLAGS = -O2
WARN_FLAGS = -Wall -Wextra -Werror
USER_DEFINES =
USER_INC_PATHS =
LIBS = -ltensors -lsystemsolvers
USER_LIB_DIRS =
USER_LIBS =

# DIRECTORIES
PROJ_ROOT_DIR_0 = ../..
PROJ_ROOT_DIR = $(shell echo $$PROJ_ROOT_DIR)
ifeq ($(PROJ_ROOT_DIR),)
	PROJ_ROOT_DIR = $(PROJ_ROOT_DIR_0)
endif
LIB_DIR = $(PROJ_ROOT_DIR)/libs
HEAD_DIR = $(PROJ_ROOT_DIR)/iheaders
BIN_DIR = $(PROJ_ROOT_DIR)/bins

# ATTRIBUTES 
BUILD_TIMESTAMP = $(shell date +'%d-%m-%Y.%H-%M-%S.%N')

# COMPILER & LINKER
CXX := $(or $(CXX),g++)

# FLAGS 
STD_FLAG = -std=c++20
DEBUG_FLAGS = -pipe -g
RELEASE_FLAGS = -pipe $(OPT_FLAGS)
BUILD_FLAGS = $(if $(filter $(BUILD_MODE),DEBUG),$(DEBUG_FLAGS),$(RELEASE_FLAGS))
DEFINES = -DBUILD_TIMESTAMP_STR=\"$(BUILD_TIMESTAMP)\" \
		  -DPROJ_ROOT_DIR=\"$(PROJ_ROOT_DIR)\" \
		  $(USER_DEFINES)
INC_FLAGS = $(foreach inc,$(USER_INC_PATHS),-I$(inc)) -I$(HEAD_DIR)
CXXFLAGS = $(STD_FLAG) $(BUILD_FLAGS) $(DEFINES) $(WARN_FLAGS) $(INC_FLAGS)
RPATH = -Wl,-rpath,$(LIB_DIR) $(foreach libdir,$(USER_LIB_DIRS),-Wl,-rpath,$(libdir))
USER_LIB_DIR_FLAGS = $(foreach libdir,$(USER_LIB_DIRS),-L$(libdir))
LDFLAGS = -L$(LIB_DIR) $(LIBS) $(USER_LIB_DIR_FLAGS) $(USER_LIBS) $(RPATH)

# CREATE BINARY 

TARGET = $(BIN_DIR)/$(TARGET_NAME)

.PHONY: clean

all: $(TARGET)

$(TARGET): $(SRC_FILE)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean: 
	-rm -v $(TARGET)













