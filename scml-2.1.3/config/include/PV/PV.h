/*****************************************************************************
 *                   Copyright (C) 1996-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
/*
// Modifications :
//
// Purpose of file : 
//
*/

#ifndef CWR_PV_H
#define CWR_PV_H

#include <systemc.h>
#include <string>
#include "PVDataTypes.h"
#include "tlm_transport_if.h"


using std::string;

/*******************************************************************************
*	Forward declarations
*******************************************************************************/


template <typename DT, typename AT = void>
class PVTarget_port;

template <typename DT, typename AT = void>
class PVTarget_process;

/*******************************************************************************
*	PV interface definition.
*******************************************************************************/

template <typename DT, typename AT = void>
class PV_if : virtual public tlm::tlm_transport_if< PVReq<DT,AT>, PVResp<DT> > 
{
  public :
    PV_if<DT,AT>() {}
    using tlm::tlm_transport_if< PVReq<DT,AT>, PVResp<DT> >::transport;
    virtual PVResp<DT> transport(const PVReq< DT, AT >& arg_Req) = 0;
  private:
    // disabled
    PV_if<DT,AT>(const PV_if<DT,AT>&);
    PV_if<DT,AT>& operator=(const PV_if<DT,AT>&);
};

/*******************************************************************************
*	PVInitiator_port_base definition  (used as return type of decoder only)
*******************************************************************************/

class PVInitiator_port_base
{
  protected:
    PVInitiator_port_base(){};
    ~PVInitiator_port_base(){};
    PVInitiator_port_base(const PVInitiator_port_base& copy);
};

/*******************************************************************************
*	PVInitiator_port definition (for convenience)
*******************************************************************************/

template <typename DT, typename AT = void>
class PVInitiator_port: public PVInitiator_port_base,
			public sc_port< PV_if< DT, AT > >
{
  
  private:
    		         
  protected:

    typedef sc_port< PV_if< DT, AT> > parentPortType;
    typedef PV_if< DT, AT> interfaceType;
    typedef PVTarget_process< DT, AT > targetProcessType;
    
    interfaceType* operator -> () {return parentPortType::operator -> (); }    
    const interfaceType * operator -> () const { return parentPortType::operator -> (); }

    
    //contains pointer to PVTarget_port process if connected to 
    //a PVTarget_port.    
    targetProcessType* m_targetProcess;
    bool m_connectedToTarget;    

    void end_of_elaboration();
            
  public:
    explicit PVInitiator_port(const char* name);
    PVInitiator_port();
  
    PVResp<DT> transport(const PVReq< DT, AT >& arg_Req);
};

/*******************************************************************************
*	PVTarget_process definition, implements PVTarget interface
*******************************************************************************/


template <typename DT, typename AT>
class PVTarget_process : virtual public PV_if< DT, AT>
{
  private :
    //func ptr to transport function of slave.
    PVResp<DT> ( sc_module::*m_cb) (const PVReq< DT, AT >& arg_Req); 
    sc_module* m_mod; 
  public :
    PVTarget_process ();
    PVResp<DT> nonVirtualTransport(const PVReq< DT, AT >& arg_Req);
    using PV_if<DT, AT>::transport;
    PVResp<DT> transport(const PVReq< DT, AT >& arg_Req);
    //function call to  ptr to slave's transport function.
    template< class Module>
    void CB(Module* arg_module, 
	PVResp<DT> ( Module::*arg_cb) (const PVReq< DT, AT >& arg_Req));
};

/*******************************************************************************
*	PVTarget_port definition, can connect to PVTarget interface.
*	contains a PVTarget_process.  
*******************************************************************************/

template <typename DT, typename AT>
class PVTarget_port: public sc_export< PV_if< DT, AT> >
{
  private :    
    PVTarget_process< DT, AT>* m_proc;
    
  public :
    PVTarget_port();
    explicit PVTarget_port( const char* name );
  
    ~PVTarget_port();
    template <class Module>
    void CB(Module* arg_module,
		    PVResp<DT>( Module::*arg_cb) (const PVReq< DT, AT >& arg_Req));
};

/*******************************************************************************
*	pv_module definition
*******************************************************************************/

class pv_module: public sc_module 
{
public:
  pv_module (sc_module_name name) : sc_module(name) {};
};

/*******************************************************************************
* 	PVInitiator_port implementation
*******************************************************************************/

template <typename DT, typename AT>
inline PVInitiator_port< DT, AT>::PVInitiator_port(const char* name)
			:sc_port< PV_if< DT, AT> >(name)
{
  m_targetProcess = 0;

};

template <typename DT, typename AT>
inline PVInitiator_port< DT, AT>::PVInitiator_port()
			:sc_port< PV_if< DT, AT> >()
{
  m_targetProcess = 0;

};

template <typename DT, typename AT>
inline void PVInitiator_port< DT, AT>::end_of_elaboration() 
{

  
  m_targetProcess = dynamic_cast< targetProcessType*> ( this->get_interface());
  m_connectedToTarget = m_targetProcess != 0;
  
};

template <typename DT, typename AT>
inline PVResp<DT> PVInitiator_port< DT, AT>::transport(const PVReq< DT, AT >& arg_Req)
{
  PVResp<DT> resp;
    resp = (*this)->transport(arg_Req);

  return resp;
};

/*******************************************************************************
* 	PVTarget_process implementation
*******************************************************************************/

template <typename DT, typename AT>
inline PVTarget_process< DT, AT >::PVTarget_process ()
{
  m_cb  = 0;
  m_mod = 0;   
};

template <typename DT, typename AT>
inline PVResp<DT> PVTarget_process< DT, AT >::transport(const PVReq< DT, AT >& arg_Req)
{
  return nonVirtualTransport(arg_Req);
};

template <typename DT, typename AT>
inline PVResp<DT> PVTarget_process< DT, AT >::nonVirtualTransport(const PVReq< DT, AT >& arg_Req)
{
  return ((m_mod->*m_cb)(arg_Req));
};

template <typename DT, typename AT>
template < class Module>
inline void PVTarget_process< DT, AT >::CB(Module* arg_module, 
		PVResp<DT> ( Module::*arg_cb) (const PVReq< DT, AT >& arg_Req))
{
  m_mod = arg_module;
  m_cb = static_cast< 
		  PVResp<DT>( sc_module::*) (const PVReq< DT, AT >& arg_Req) 
		  > 
		  (arg_cb);
};

/*******************************************************************************
* 	PV_Target_export member funtion implementation
*******************************************************************************/

template <typename DT, typename AT>
inline PVTarget_port< DT, AT >::PVTarget_port() : 
  sc_export< PV_if< DT, AT> > (), m_proc(0) {};

template <typename DT, typename AT>
inline PVTarget_port< DT, AT >::PVTarget_port( const char * name ) : 
  sc_export< PV_if< DT, AT> > ( name ), m_proc(0) {};

template <typename DT, typename AT>
inline PVTarget_port< DT, AT >::~PVTarget_port()
{
  delete m_proc;
};

template <typename DT, typename AT>
template <class Module>
inline void PVTarget_port< DT, AT >::CB(Module* arg_module, 
		  PVResp<DT> ( Module::*arg_cb) (const PVReq< DT, AT >& arg_Req))
{
  //create new process.
  m_proc = new PVTarget_process< DT, AT >();
  //connect process to export.
  (*this)(*m_proc);
  // callback to process;
  m_proc->CB(arg_module, arg_cb);
}

#define REGISTER_PVSLAVE( port, process) \
port.CB( this, &SC_CURRENT_USER_MODULE::process)


#endif
