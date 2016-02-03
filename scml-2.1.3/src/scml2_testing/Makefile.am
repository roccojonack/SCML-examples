noinst_LIBRARIES = libscml2_testing.a libscml2_testing_systemc_main.a

H_FILES = \
	assertion_macros.h \
	equals.h \
	initiator_socket_proxy.h \
	initiator_socket_proxy_base.h \
	input_clock_proxy.h \
	input_pin_proxy.h \
	input_output_pin_proxy.h \
	memory_element_value_proxy.h \
	memory_if.h \
	output_pin_proxy.h \
	output_pin_proxy_base.h \
	parameter_configuration.h \
	parameter_configurations.h \
	pin_value_proxy.h \
	predicate.h \
	property_proxy.h \
	property_server.h \
	proxy.h \
	register_value_proxy.h \
	reporter_if.h \
	stdout_reporter.h \
	systemc_test_runner.h \
	target_socket_proxy.h \
	target_socket_proxy_base.h \
	test.h \
	test_base.h \
	test_exception.h \
	test_group.h \
	test_group_base.h \
	test_group_factory.h \
	test_group_factory_base.h \
	test_group_registration.h \
	test_group_registry.h \
	test_group_registry_base.h \
	test_macros.h \
	test_memory.h \
	test_memory_element.h \
	test_runner.h

PRIVATE_H_FILES =

noinst_HEADERS = $(H_FILES)

CXX_FILES = \
	initiator_socket_proxy_base.cc \
	memory_element_value_proxy.cc \
	memory_if.cc \
	property_server.cc \
	reporter_if.cc \
	stdout_reporter.cc \
	systemc_test_runner.cc \
	target_socket_proxy_base.cc \
	test_base.cc \
	test_group_base.cc \
	test_group_factory_base.cc \
	test_group_registry.cc \
	test_group_registry_base.cc \
	test_memory.cc \
	test_memory_element.cc \
	test_runner.cc

libscml2_testing_a_SOURCES = $(H_FILES) $(PRIVATE_H_FILES) $(CXX_FILES)

libscml2_testing_systemc_main_a_SOURCES = \
	systemc_main.cc

INCLUDES = -I$(srcdir)/.. -I../scml2 -I$(srcdir)/../ModelingObjects -I../scml2_logging $(OSCITLM_INC) $(SYSC_INC)

INCLUDE_DIR = $(prefix)/include
LIB_DIR = $(prefix)/lib-$(TARGET_ARCH)

	
.PHONY: scml2_testing.h
scml2_testing.h:
	@rm -rf $@
	@echo "// Copyright (C) 2011 Synopsys, Inc." > $@
	@echo "// All rights reserved worldwide." >> $@
	@echo "" >> $@
	@echo "#ifndef SCML2_TESTING_H" >> $@
	@echo "#define SCML2_TESTING_H" >> $@
	@echo "" >> $@
	@for file in $(noinst_HEADERS) ; do \
	  echo "#include \"scml2_testing/$$file\"" >> $@ ; \
	done
	@echo "" >> $@
	@echo "#endif" >> $@

install-data-local: scml2_testing.h
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(INCLUDE_DIR)/scml2_testing
	for file in $(noinst_HEADERS); do \
	  $(INSTALL_DATA) $(srcdir)/$$file $(INCLUDE_DIR)/scml2_testing/$$file; \
	done
	$(INSTALL_DATA) scml2_testing.h $(INCLUDE_DIR)/scml2_testing.h; \
	$(mkinstalldirs) $(LIB_DIR)
	$(INSTALL_DATA) libscml2_testing.a $(LIB_DIR)/libscml2_testing.a
	$(RANLIB) $(LIB_DIR)/libscml2_testing.a
	$(INSTALL_DATA) libscml2_testing_systemc_main.a $(LIB_DIR)/libscml2_testing_systemc_main.a
	$(RANLIB) $(LIB_DIR)/libscml2_testing_systemc_main.a

uninstall-local:
	@$(NORMAL_UNINSTALL)
	for file in $(noinst_HEADERS); do \
	  rm -f $(INCLUDE_DIR)/scml2_testing/$$file; \
	done
	-rmdir $(INCLUDE_DIR)/scml2_testing
	rm -f $(LIB_DIR)/libscml2_testing.a
	rm -f $(LIB_DIR)/libscml2_testing_systemc_main.a
	-rmdir $(prefix)/lib-$(TARGET_ARCH)
