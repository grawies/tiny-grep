CC            := g++
CCFLAGS       := -std=c++11 -g -Wall
SRCEXT        := cpp

SRCDIR        := src
BUILDDIR      := build
BINDIR        := bin
TESTDIR       := test
LIBDIR        := lib
INCLUDE       := -Iinclude/
INCLUDE_TEST  := -I$(SRCDIR)/ -I$(LIBDIR)/cxxtest/
CXXTESTGENPY  := $(LIBDIR)/cxxtest/cxxtestgen.py

APP_FILE      := application.cpp
SOURCE_FILES  := $(shell find $(SRCDIR) ! -name $(APP_FILE) -type f -name *.$(SRCEXT))
OBJECT_FILES  := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCE_FILES:.$(SRCEXT)=.o))
TEST_SPEC     := $(BUILDDIR)/$(TESTDIR)/test_spec.cpp
FOOFOO := count_if_followed_by

.PHONY: obj_dirs build app test runtest clean all

obj_dirs:
	mkdir -p $(foreach DIR, $(OBJECT_FILES), $(dir $(DIR)))

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

build: obj_dirs $(OBJECT_FILES)

$(BUILDDIR)/test/%: $(TESTDIR)/%
	mkdir -p build
	cp --parents $(TESTDIR)/test_spec.cpp $(BUILDDIR)

app: build
	@echo " Building application endpoint..."
	$(CC) $(CCFLAGS) $(INCLUDE) $(INCLUDE_APP) -o $(BINDIR)/tinygrep \
          $(SRCDIR)/$(APP_FILE) $(OBJECT_FILES)

test: build $(TEST_SPEC)
	@echo " Building tests..."
	$(CXXTESTGENPY) --error-printer -o $(BUILDDIR)/tester.cpp \
          test/test_spec.cpp
	mkdir -p $(BINDIR)
	$(CC) $(CCFLAGS) $(INCLUDE) $(INCLUDE_TEST) -o $(BINDIR)/tester \
          $(BUILDDIR)/tester.cpp $(OBJECT_FILES)

runtest: test
	@echo " ====================="
	@echo " Running tests..."
	$(BINDIR)/tester

memtest: test
	@echo " Generating memory error log..."
	valgrind --tool=memcheck --leak-check=yes $(BINDIR)/tester | tee $(BINDIR)/memcheck.log

clean:
	@echo " Cleaning..."
	rm -rf $(BUILDDIR) $(BINDIR)

all: clean runtest app
