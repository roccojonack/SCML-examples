##  examples/simple_IPE/PV/Makefile.am --
##  Process this file with automake to produce a Makefile.in file.

CXX_FILES = \
	    main.cpp

H_FILES = \
	  simple_IPE_PV.h \
	  simple_IPE_PV_testbench.h

check_PROGRAMS = simple_IPE
TESTS = $(check_PROGRAMS) 

simple_IPE_SOURCES = $(CXX_FILES) $(H_FILES)

AM_CPPFLAGS = $(COMMONINC)

LDADD = $(COMMONLIB)

simple_IPE_INSTALLS = $(simple_IPE_SOURCES) golden.log

all:
	@echo "To compile an run this example type"
	@echo "   make check"

install-data-local:
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) .
	for file in $(simple_IPE_INSTALLS); do \
		$(INSTALL_DATA) $(srcdir)/$$file ./$$file; \
	done

uninstall-local:
	@$(NORMAL_UNINSTALL)
	for file in $(simple_IPE_INSTALLS); do \
		rm -f ./$$file; \
	done

