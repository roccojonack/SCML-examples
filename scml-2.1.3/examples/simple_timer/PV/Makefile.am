##  examples/simple_timer/PV/Makefile.am --
##  Process this file with automake to produce a Makefile.in file.

CXX_FILES = \
	    main.cpp \
	    top_PV.cpp

H_FILES = \
	  simple_timer_PV.h \
	  simple_timer_PV_TB.h \
	  top_PV.h

check_PROGRAMS = simple_timer
TESTS = $(check_PROGRAMS) 

simple_timer_SOURCES = $(CXX_FILES) $(H_FILES)

AM_CPPFLAGS = $(COMMONINC)

LDADD = $(COMMONLIB)

simple_timer_INSTALLS = $(simple_timer_SOURCES) golden.log

all:
	@echo "To compile an run this example type"
	@echo "   make check"

install-data-local:
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) .
	for file in $(simple_timer_INSTALLS); do \
		$(INSTALL_DATA) $(srcdir)/$$file ./$$file; \
	done

uninstall-local:
	@$(NORMAL_UNINSTALL)
	for file in $(simple_timer_INSTALLS); do \
		rm -f ./$$file; \
	done

