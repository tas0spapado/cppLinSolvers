SRC_FILES = openmp_settings/openmp_settings.cpp
TARGET_NAME = openmp_settings
BUILD_MODE = RELEASE

# FLAGS 
OPT_FLAGS = -O2
WARN_FLAGS = -Wall -Wextra #-Werror
USER_DEFINES = 		#extra user defines, like macros or other flags like -pthread 
USER_INC_PATHS =  	#for extra header dir, other than share_headers
LIBS = 				#libs in $(LIB_DIR) 
USER_LIB_DIRS = 	#directories of extra libraries that will be linked to the current library 
USER_LIBS = 		#names of the libraries 

# DIRECTORIES 
PROJ_ROOT_DIR_0 = ../..
PROJ_ROOT_DIR = $(shell echo $$PROJ_ROOT_DIR)
ifeq ($(PROJ_ROOT_DIR),)
	PROJ_ROOT_DIR = $(PROJ_ROOT_DIR_0)
endif
OBJ_DIR = $(PROJ_ROOT_DIR)/objs
LIB_DIR = $(PROJ_ROOT_DIR)/libs
HEAD_DIR = $(PROJ_ROOT_DIR)/linked_headers

#====================================================

# ATTRIBUTES 
BUILD_TIMESTAMP = $(shell date +'%d-%m-%Y.%H-%M-%S.%N')

# COMPILER & LINKER
CXX := $(or $(CXX),g++)
LDXX := $(or $(LDXX),g++)

# FLAGS
STD_FLAG = -std=c++20
DEBUG_FLAGS = -pipe -g -fPIC
RELEASE_FLAGS = -pipe -fPIC $(OPT_FLAGS)
ADDITIONAL_CXXFLAGS = -fopenmp
ADDITIONAL_LDFLAGS = -fopenmp
BUILD_FLAGS = $(if $(filter $(BUILD_MODE),DEBUG),$(DEBUG_FLAGS),$(RELEASE_FLAGS))
DEFINES = -DBUILD_TIMESTAMP_STR=\"$(BUILD_TIMESTAMP)\" \
		  -DPROJ_ROOT_DIR=\"$(PROJ_ROOT_DIR)\" \
		  $(USER_DEFINES)
INC_FLAGS = $(foreach inc,$(USER_INC_PATHS),-I$(inc)) -I$(HEAD_DIR)
CXXFLAGS = $(STD_FLAG) $(BUILD_FLAGS) $(DEFINES) $(WARN_FLAGS) $(INC_FLAGS) $(ADDITIONAL_CXXFLAGS)
RPATH = -Wl,-rpath,$(LIB_DIR) $(foreach libdir,$(USER_LIB_DIRS),-Wl,-rpath,$(libdir))
USER_LIB_DIR_FLAGS = $(foreach libdir,$(USER_LIB_DIRS),-L$(libdir))
LDFLAGS = -L$(LIB_DIR) $(LIBS) $(USER_LIB_DIR_FLAGS) $(ADDITIONAL_LDFLAGS) $(USER_LIBS) $(RPATH)

# OBJECT FILES 
OBJ = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# CREATE SHARED LIBRARY 
TARGET = $(LIB_DIR)/lib$(TARGET_NAME).so

.PHONY: all clean install_headers check

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(LIB_DIR)
	$(LDXX) -shared -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp %.h
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

install_headers:
	@mkdir -p $(HEAD_DIR)
	@for src in $(SRC_FILES); do \
		hdr="$${src%.cpp}.h"; \
		if [ -f "$$hdr" ]; then \
			ln -sf "$$(realpath --relative-to=$(HEAD_DIR) "$$hdr")" "$(HEAD_DIR)/$$(basename "$$hdr")"; \
			echo "Linked: $$hdr → $(HEAD_DIR)/$$(basename "$$hdr")"; \
		else \
			echo "Warning: $$hdr not found."; \
		fi \
	done

clean: 
	-rm -v $(TARGET)
	-rm -v $(OBJ)

check:
	@echo "LDFLAGS: " $(LDFLAGS)

