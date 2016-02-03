##  Makefile.am --
##  Process this file with automake to produce a Makefile.in file.
##

noinst_LIBRARIES = libModelingObjects.a

H_FILES = \
	scmlinc/scml.h \
        scmlinc/scml_array_base.h \
        scmlinc/scml_array.h \
        scmlinc/scml_array_notify_if.h \
        scmlinc/scml_bitfield_base.h \
        scmlinc/scml_bitfield_container.h \
        scmlinc/scml_bitfield_container_if.h \
        scmlinc/scml_bitfield.h \
        scmlinc/scml_clock_counter.h \
        scmlinc/scml_clock_enable.h \
        scmlinc/scml_clock_gate.h \
        scmlinc/scml_clock.h \
        scmlinc/scml_clock_b.h \
        scmlinc/scml_divided_clock.h \
        scmlinc/scml_memory_base.h \
        scmlinc/scml_memory.h \
        scmlinc/scml_memory_index_reference.h \
        scmlinc/scml_memory_operations.h \
        scmlinc/scml_memory_operations_podt_common.h \
        scmlinc/scml_memory_operations_pts_bool.h \
        scmlinc/scml_memory_operations_pts_char.h \
        scmlinc/scml_memory_operations_pts_signed_char.h \
        scmlinc/scml_memory_operations_pts_double.h \
        scmlinc/scml_memory_operations_pts_float.h \
        scmlinc/scml_memory_operations_pts_signed_int.h \
        scmlinc/scml_memory_operations_pts_signed_long_int.h \
        scmlinc/scml_memory_operations_pts_signed_long_long.h \
        scmlinc/scml_memory_operations_pts_signed_short_int.h \
        scmlinc/scml_memory_operations_pts_unsigned_char.h \
        scmlinc/scml_memory_operations_pts_unsigned_int.h \
        scmlinc/scml_memory_operations_pts_unsigned_long_int.h \
        scmlinc/scml_memory_operations_pts_unsigned_long_long.h \
        scmlinc/scml_memory_operations_pts_unsigned_short_int.h \
        scmlinc/scml_memory_pv_if.h \
        scmlinc/scml_memory_utils.h \
        scmlinc/scml_memsize.h \
        scmlinc/scml_pool.h \
        scmlinc/scml_post_if.h \
        scmlinc/scml_post_port.h \
        scmlinc/scml_pv_decoder.h \
        scmlinc/scml_pv_decoder_port.h \
        scmlinc/scml_pv_multi_port.h \
        scmlinc/scml_post_PV_transactor.h \
        scmlinc/scml_transaction_request.h \
        scmlinc/scml_types.h \
        scmlinc/scml_memory_registration.h \
        scmlinc/scml_memory_user.h \
	scmlinc/scml_property.h \
	scmlinc/scml_property_server_if.h \
	scmlinc/scml_property_registry.h \
	scmlinc/scml_simple_property_server.h \
	scmlinc/scml_inmemory_property_server.h \
	scmlinc/scml_memory_map_facade.h \
	scmlinc/scml_memory_map_observer_if.h \
	scmlinc/scml_transport_if.h \
	scmlinc/scml_synchroniser_registry.h  \
	scmlinc/scml_memory_iterator.h \
	scmlinc/scml_memory_algorithm.h \
	scmlinc/scml_router.h \
        scmlinc/scml_router_operations.h \
        scmlinc/scml_router_operations_podt_common.h \
        scmlinc/scml_router_operations_pts_unsigned_char.h \
        scmlinc/scml_router_operations_pts_unsigned_int.h \
        scmlinc/scml_router_operations_pts_unsigned_long_int.h \
        scmlinc/scml_router_operations_pts_unsigned_long_long.h \
        scmlinc/scml_router_operations_pts_unsigned_short_int.h \
        scmlinc/scml_command_processor.h \
	scmlinc/scml_pv_initiator_port.h \
       	scmlinc/scml_tlm2_target_adaptor_base.h \
       	scmlinc/scml_tlm2_initiator_adaptor_base.h \
       	scmlinc/scml_tlm2_target_adaptor.h \
       	scmlinc/scml_tlm2_initiator_adaptor.h \
       	scmlinc/scml_post_target_adaptor.h \
       	scmlinc/scml_mapable_if_to_T.h \
       	scmlinc/scml_mapable_if.h \
	scmlinc/scml_memory_operations_pts_sc_biguint_n.h \
	scmlinc/scml_router_operations_pts_sc_biguint_n.h \
	scmlinc/scml_transport_callback.h \
	scmlinc/scml_bitfield_callback_observer.h \
       	scmlinc/scml_bitfield_callback_observer_owner.h \
       	scmlinc/scml_bitfield_callback_observers.h \
       	scmlinc/scml_callback_observer.h \
       	scmlinc/scml_callback_observer_owner.h \
       	scmlinc/scml_callback_observers.h \
	scmlinc/scml_mapped_range.h \
       	scmlinc/scml_mapped_ranges_observer.h \
       	scmlinc/scml_mapped_ranges_observer_owner.h \
       	scmlinc/scml_mapped_ranges_observers.h \
       	scmlinc/scml_memory_callback_observer_if.h

LNKHEADERS = \
        scml.h \
	scml_memory.h \
	scml_clock.h

noinst_HEADERS = $(H_FILES)

CXX_FILES = \
	src/scml_array_base.cc \
	src/scml_array_notify_if.cc \
	src/scml_bitfield.cc \
	src/scml_bitfield_base.cc \
	src/scml_bitfield_container.cc \
	src/scml_clock_b.cc \
	src/scml_clock_counter.cc \
	src/scml_clock_enable.cc \
	src/scml_divided_clock.cc \
	src/scml_memory_base.cc \
	src/scml_memory_utils.cc \
	src/scml_memory_registration.cc \
	src/scml_memory_user.cc \
	src/scml_memory_operations_podt_common.cc \
	src/scml_memory_operations_pts_bool.cc \
        src/scml_memory_operations_pts_char.cc \
        src/scml_memory_operations_pts_signed_char.cc \
        src/scml_memory_operations_pts_signed_int.cc \
        src/scml_memory_operations_pts_signed_long_int.cc \
        src/scml_memory_operations_pts_signed_long_long.cc \
        src/scml_memory_operations_pts_signed_short_int.cc \
        src/scml_memory_operations_pts_unsigned_char.cc \
        src/scml_memory_operations_pts_unsigned_int.cc \
        src/scml_memory_operations_pts_unsigned_long_int.cc \
        src/scml_memory_operations_pts_unsigned_long_long.cc \
        src/scml_memory_operations_pts_unsigned_short_int.cc \
	src/scml_property.cc \
	src/scml_property_server_if.cc \
	src/scml_property_registry.cc \
	src/scml_simple_property_server.cc \
	src/scml_inmemory_property_server.cc \
	src/scml_memory_map_facade.cc \
        src/scml_synchroniser_registry.cc \
	src/scml_router_operations_podt_common.cc \
        src/scml_router_operations_pts_unsigned_char.cc \
        src/scml_router_operations_pts_unsigned_int.cc \
        src/scml_router_operations_pts_unsigned_long_int.cc \
        src/scml_router_operations_pts_unsigned_long_long.cc \
        src/scml_router_operations_pts_unsigned_short_int.cc \
       	src/scml_tlm2_target_adaptor_base.cc \
       	src/scml_tlm2_initiator_adaptor_base.cc \
	src/scml_memory_operations_pts_sc_biguint_n.cc \
	src/scml_router_operations_pts_sc_biguint_n.cc \
	src/scml_bitfield_callback_observers.cc \
	src/scml_mapped_ranges_observers.cc \
	src/scml_callback_observers.cc



NO_CXX_FILES =

libModelingObjects_a_SOURCES = $(H_FILES) $(CXX_FILES)

DEFS = -I.
INCLUDES = -I$(top_srcdir)/src -I$(srcdir)/scmlinc $(OSCITLM_INC) $(SYSC_INC)
  
INCLUDE_DIR = $(prefix)/include
SCMLINCLUDE_DIR = $(INCLUDE_DIR)/scmlinc

install-data-local:
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(INCLUDE_DIR)
	$(mkinstalldirs) $(SCMLINCLUDE_DIR)
	for file in $(noinst_HEADERS); do \
	  $(INSTALL_DATA) $(srcdir)/$$file $(INCLUDE_DIR)/$$file; \
	done
	for file in $(LNKHEADERS); do \
	  ln -f -s $(SCMLINCLUDE_DIR)/$$file $(INCLUDE_DIR)/$$file ; \
	done
	$(mkinstalldirs) $(prefix)/lib-$(TARGET_ARCH)
	$(INSTALL_DATA) $(MAIN_LIBRARY) \
	  $(prefix)/lib-$(TARGET_ARCH)/$(MAIN_LIBRARY)
	$(RANLIB) $(prefix)/lib-$(TARGET_ARCH)/$(MAIN_LIBRARY)

uninstall-local:
	@$(NORMAL_UNINSTALL)
	for file in $(noinst_HEADERS); do \
	  rm -f $(INCLUDE_DIR)/$$file; \
	done
	for file in $(LNKHEADERS); do \
	  rm -f $(INCLUDE_DIR)/$$file ; \
	done
	-rmdir $(SCMLINCLUDE_DIR)
	-rmdir $(INCLUDE_DIR)
	rm -f $(prefix)/lib-$(TARGET_ARCH)/$(MAIN_LIBRARY)
	-rmdir $(prefix)/lib-$(TARGET_ARCH)
