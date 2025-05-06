BUILD = make 
CLEAN = make clean 
INSTALL = make install_headers
SOURCE_DIR := ./src
.PHONY: build clean install_headers

all: install build

build:
	@echo "##### BUILDING ALL MODULES #####"
	(cd src/tensors; $(BUILD))
	(cd src/system_solvers; $(BUILD))
	(cd tests/test-tensor; $(BUILD))
	(cd tests/test-vector; $(BUILD))
	(cd tests/test-matrix; $(BUILD))
	(cd tests/test-sparsematrix; $(BUILD))
	(cd tests/test-jacobi; $(BUILD))
	(cd tests/test-gaussseidel; $(BUILD))
	(cd tests/test-system_solvers; $(BUILD))
	(cd apps/Poisson2D; $(BUILD))

clean: 
	@echo "##### CLEANING ALL MODULES #####"
	(cd src/tensors; $(CLEAN))
	(cd src/system_solvers; $(CLEAN))
	(cd tests/test-tensor; $(CLEAN))
	(cd tests/test-vector; $(CLEAN))
	(cd tests/test-matrix; $(CLEAN))
	(cd tests/test-sparsematrix; $(CLEAN))
	(cd tests/test-jacobi; $(CLEAN))
	(cd tests/test-gaussseidel; $(CLEAN))
	(cd tests/test-system_solvers; $(CLEAN))
	(cd apps/Poisson2D; $(CLEAN))
	-rm -v iheaders/*
	-rm -rv objs/*

install: 
	@echo "##### INSTALLING HEADERS #####"
	(cd src/tensors; $(INSTALL))
	(cd src/system_solvers; $(INSTALL))
