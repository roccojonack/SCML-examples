##  examples/scml2/ExampleMemory/Makefile.am --
##  Process this file with automake to produce a Makefile.in file.

CXX_FILES = main.cpp

H_FILES = \
	ExampleMemory.h \
	MemoryCheck.h

check_PROGRAMS = main
TESTS = $(check_PROGRAMS) 

## INCLUDES = -I$(prefix)/include

main_SOURCES = $(CXX_FILES) $(H_FILES)

main_CPPFLAGS = $(COMMONINC)

main_LDADD = $(COMMONLIB)

main_INSTALLS = $(main_SOURCES) golden.log

all:
	@echo "To compile an run this example type"
	@echo "   make check"

install-data-local:
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) .
	for file in $(main_INSTALLS); do \
		$(INSTALL_DATA) $(srcdir)/$$file ./$$file; \
	done

uninstall-local:
	@$(NORMAL_UNINSTALL)
	for file in $(main_INSTALLS); do \
		rm -f ./$$file; \
	done



