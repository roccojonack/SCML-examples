##  examples/Memory/TLM2/Makefile.am --
##  Process this file with automake to produce a Makefile.in file.

CXX_FILES = \
	    main.cpp \
	    Memory_TLM2.cpp \
	    top_TLM2.cpp

H_FILES = \
	  Memory_TLM2.h \
	  top_TLM2.h \
	  TrafficGen_TLM2.h


check_PROGRAMS = Memory
TESTS = $(check_PROGRAMS) 

Memory_SOURCES = $(CXX_FILES) $(H_FILES)

AM_CPPFLAGS = $(COMMONINC)

LDADD = $(COMMONLIB)

Memory_INSTALLS = $(Memory_SOURCES) golden.log

all:
	@echo "To compile an run this example type"
	@echo "   make check"

install-data-local:
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) .
	for file in $(Memory_INSTALLS); do \
		$(INSTALL_DATA) $(srcdir)/$$file ./$$file; \
	done



uninstall-local:
	@$(NORMAL_UNINSTALL)
	for file in $(Memory_INSTALLS); do \
		rm -f ./$$file; \
	done

