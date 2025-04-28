BUILD = make 
CLEAN = make clean 
INSTALL = make install_headers
SOURCE_DIR := ./src
.PHONY: build clean install_headers

all: install build

define  makeallmodules
	for idir in $(SOURCE_DIR)/*; \
		do \
		make -C $$dir $(1); \
		done
endef

build:
	@echo "##### BUILDING ALL MODULES #####"
	(cd src/tensors; $(BUILD))
	(cd src/system_solvers; $(BUILD))
	(cd tests/test-tensor; $(BUILD))
	(cd tests/test-vector; $(BUILD))
	(cd tests/test-matrix; $(BUILD))
	(cd tests/test-jacobi; $(BUILD))

clean: 
	@echo "##### CLEANING ALL MODULES #####"
	(cd src/tensors; $(CLEAN))
	(cd src/system_solvers; $(CLEAN))
	(cd tests/test-tensor; $(CLEAN))
	(cd tests/test-vector; $(CLEAN))
	(cd tests/test-matrix; $(CLEAN))
	(cd tests/test-jacobi; $(CLEAN))
	-rm -v iheaders/*

install: 
	@echo "##### INSTALLING HEADERS #####"
	(cd src/tensors; $(INSTALL))
	(cd src/system_solvers; $(INSTALL))
