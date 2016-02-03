##  Makefile.am --
##  Process this file with automake to produce a Makefile.in file.
##

SUBDIRS = \
	src \
	examples \
	.

INST_FILES = \
	AUTHORS \
	COPYING \
	ChangeLog \
	INSTALL \
	LICENSE \
	NEWS \
	README \
	RELEASENOTES \
	docs

debug:
	$(MAKE) all CXXFLAGS="$(EXTRA_CXXFLAGS) $(DEBUG_CXXFLAGS)"

opt:
	$(MAKE) all CXXFLAGS="$(EXTRA_CXXFLAGS) $(OPT_CXXFLAGS)"

pthreads:
	$(MAKE) all CXXFLAGS="$(EXTRA_CXXFLAGS) $(OPT_CXXFLAGS) -DSC_USE_PTHREADS=1"

pthreads_debug:
	$(MAKE) all CXXFLAGS="$(EXTRA_CXXFLAGS) $(DEBUG_CXXFLAGS) -DSC_USE_PTHREADS"

pthreads_check:
	$(MAKE) check CXXFLAGS="$(EXTRA_CXXFLAGS) -DSC_USE_PTHREADS" LDFLAGS="-lpthread"

install-data-local:
	@$(NORMAL_INSTALL)
	for file in $(INST_FILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    test -d $(prefix)/$$file \
	    || cp -pr $$d/$$file $(prefix) || :; \
	  else \
	    test -f $(prefix)/$$file \
	    || cp -p $$d/$$file $(prefix)/$$file || :; \
	  fi; \
	done
#@(cd ./examples; $(MAKE) install;)

uninstall-local:
	@$(NORMAL_UNINSTALL)
	w=`pwd`; cd $(srcdir); s=`pwd`; cd $$w; \
	if test $(prefix) != $$s; then \
	  for file in $(INST_FILES); do \
	    d=$(srcdir); \
	    if test -d $$d/$$file; then \
	      rm -rf $(prefix)/$$file; \
	    else \
	      rm -f $(prefix)/$$file; \
	    fi; \
	  done; \
	fi
	@(cd ./examples; $(MAKE) uninstall;)

## Taf!
