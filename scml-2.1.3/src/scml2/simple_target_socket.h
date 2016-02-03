/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_SIMPLE_TARGET_SOCKET_H
#define SCML2_SIMPLE_TARGET_SOCKET_H

#include <tlm_utils/simple_target_socket.h>

namespace scml2{

template<typename MODULE, unsigned int BUSWIDTH=64,
		    typename TYPES = tlm::tlm_base_protocol_types>

class simple_target_socket :
    public tlm_utils::simple_target_socket<MODULE, BUSWIDTH, TYPES> {

    public:

        typedef tlm_utils::simple_target_socket<MODULE, BUSWIDTH, TYPES> base_type;

        simple_target_socket(): base_type(){}

        explicit simple_target_socket(const char* name): base_type(){}

        ~simple_target_socket(){}
}; //simple_target_socket

 
} //namespace scml2
#endif
