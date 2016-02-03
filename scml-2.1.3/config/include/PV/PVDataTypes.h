/*****************************************************************************
 *                   Copyright (C) 1996-2010 Synopsys, Inc.                  *
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

#ifndef CWR_PVDATATYPES_H
#define CWR_PVDATATYPES_H

#include <systemc.h>
#include "PVCustomResp.h"
#include "PVCustomReq.h"
#include "PVProtocolReq.h"
#include "PVProtocolResp.h"

/*******************************************************************************
*	Predeclarations
*******************************************************************************/

class PVCustomReq;
class PVCustomResp;
class PVProtocolReq;
class PVProtocolResp;

template<typename DT>
class PVResp;

template<typename DT>
class PVRespData;

template <class REQ, class RESP>
class PVInitiator_port;

template <class REQ, class RESP>
class PVNode;

template <typename DT, typename AT>
class PVTlmIpt;

template <typename T>
class scv_extensions;

template <typename DT, typename AT, bool>
class scv_extensions_pv;

template <typename DT, typename AT>
class PostTlmIpt;

template <typename DT, typename AT, bool>
class scv_extensions_post;

class PVNode_base;

/*******************************************************************************
*	Enum definitions
*******************************************************************************/

enum PVType { pvWrite = 0, pvRead = 1};
enum PVResponse { pvOk = 0, pvError = 1};
enum PVBurstType { pvIncr = 0,
		   pvWrap = 2,
		   pvXor = 4,
		   pvStream = 5, 
		   pvUnknown = 6 };
enum PVMode { pvDefault = 0,
	      pvDebug = 1 };

/*******************************************************************************
*	PVReq class Definition
*******************************************************************************/

template <typename DT, typename AT = void>
class PVReq;

template <typename DT, typename AT>
class PVReq {
  public:
    typedef DT data_type;
    typedef AT address_type;

  private : 
    // disable
  PVReq(const PVReq&);
  PVReq& operator=(const PVReq&);

    //PVInitiator_port is declared as friend, as it needs to fill in
    //m_transactionID;   
    template <class REQ, class RESP>
    friend class PVInitiator_port;
    //PVNode is declared as friend, as it needs to fill in
    //m_transactionID;   
    template <class REQ, class RESP>
    friend class PVNode;

    template <typename T>
    friend class scv_extensions;
    template <typename DT_, typename AT_, bool>
    friend class scv_extensions_pv;
    template <typename DT_, typename AT_, bool>
    friend class scv_extensions_post;
  
protected:
    mutable unsigned    m_transactionID;
    unsigned    m_predecessorID;
  
public:
  // m_address public was made a public data member because of gcc 2.95.3 compiler
  // issues the friend class scml_pv_decoder; declaration
  mutable AT   	m_address;

protected:
    DT*          	m_writeData;
    PVType 	 	m_type;
    unsigned int 	m_dataSize;
    unsigned int 	m_offset;
    unsigned int 	m_burstCount;
    PVCustomReq* 	m_customData;
    PVProtocolReq* 	m_protocolData;
    PVResp<DT> * 	m_resp;
    PVRespData<DT> *    m_respData;
  PVBurstType  m_burstType;
  unsigned int m_threadID;
  PVMode       m_mode;

    
  public :
    //constructor
    PVReq();
    //destructor
    virtual ~PVReq();
    
    void setAddress( AT arg_address );
    AT getAddress() const;
    
    void setWriteDataSource( DT* arg_writeData);
    DT* getWriteDataSource() const;
    DT getWriteData(unsigned int arg_index = 0) const;
    
    void setType(PVType arg_type);
    PVType getType() const;
    
    void setDataSize(unsigned int arg_dataSize);
    unsigned int getDataSize() const;
    
    void setOffset(unsigned int arg_offset);
    unsigned int getOffset() const;
    
    virtual void setBurstCount(unsigned int arg_burstCount);    
    unsigned int getBurstCount() const;
    
    void setReadDataDestination(DT* arg_readData);
    DT* getReadDataDestination() const;
    
    void setCustomData(PVCustomReq& arg_customData);
    PVCustomReq& getCustomData() const;

    void setProtocolData(PVProtocolReq& arg_protocolData);
    PVProtocolReq& getProtocolData() const;

    void setProtocolRespData(PVProtocolResp& arg_protocolData);
    PVProtocolResp& getProtocolRespData() const;
    
    void setPredecessorHandle(unsigned h);
    unsigned getPredecessorHandle() const;

    PVResp<DT> obtainResp() const;

  virtual void copy_request( const PVReq & req);

  void setBurstType( PVBurstType );
  PVBurstType getBurstType() const;
  void setThreadID( unsigned int);
  unsigned int getThreadID() const;
  void setMode( PVMode);
  PVMode getMode() const;
};

template <typename DT>
class PVReq<DT,void> {
  public:
    typedef DT data_type;
    typedef void address_type;

  private : 
    // disable
  PVReq(const PVReq&);
  PVReq& operator=(const PVReq&);


    //PVInitiator_port is declared as friend, as it needs to fill in
    //m_transactionID;   
    template <class REQ, class RESP>
    friend class PVInitiator_port;
    //PVNode is declared as friend, as it needs to fill in
    //m_transactionID;   
    template <class REQ, class RESP>
    friend class PVNode;

    template <typename T>
    friend class scv_extensions;
    template <typename DT_, typename AT_, bool>
    friend class scv_extensions_pv;
    template <typename DT_, typename AT_, bool>
    friend class scv_extensions_post;

protected:
    mutable unsigned    m_transactionID;
    unsigned    m_predecessorID;
  
    DT*          	m_writeData;
    PVType 	 	m_type;
    unsigned int 	m_dataSize;
    unsigned int 	m_offset;
    unsigned int 	m_burstCount;
    PVCustomReq* 	m_customData;
    PVProtocolReq* 	m_protocolData;
    PVResp<DT> * 	m_resp;
    PVRespData<DT> *    m_respData;
  PVBurstType  m_burstType;
  unsigned int m_threadID;
  PVMode       m_mode;

  public :
    
    //constructor
    PVReq();
    //destructor
    virtual ~PVReq();
    
    void setWriteDataSource( DT* arg_writeData);
    DT* getWriteDataSource() const;
    DT getWriteData(unsigned int arg_index = 0) const;
    
    void setType(PVType arg_type);
    PVType getType() const;
    
    void setDataSize(unsigned int arg_dataSize);
    unsigned int getDataSize() const;
    
    void setOffset(unsigned int arg_offset);
    unsigned int getOffset() const;
    
    virtual void setBurstCount(unsigned int arg_burstCount);    
    unsigned int getBurstCount() const;
    
    void setReadDataDestination(DT* arg_readData);
    DT* getReadDataDestination() const;
    
    void setCustomData(PVCustomReq& arg_customData);
    PVCustomReq& getCustomData() const;

    void setProtocolData(PVProtocolReq& arg_protocolData);
    PVProtocolReq& getProtocolData() const;
    
    void setProtocolRespData(PVProtocolResp& arg_protocolData);
    PVProtocolResp& getProtocolRespData() const;

    void setPredecessorHandle(unsigned h);
    unsigned getPredecessorHandle() const;
    
    PVResp<DT> obtainResp() const;

  virtual void copy_request( const PVReq & req);

  void setBurstType( PVBurstType );
  PVBurstType getBurstType() const;
  void setThreadID( unsigned int);
  unsigned int getThreadID() const;
  void setMode( PVMode);
  PVMode getMode() const;
};


/*******************************************************************************
*	PVResp class Definition
*
*       Acts as a proxy to PVResp data, which contains the actual data.
*******************************************************************************/

template <typename DT>
class PVResp{
  public:
    typedef DT data_type;
  
  private : 
    PVRespData<DT> * m_respData;
  
    template <typename DT_,typename AT_> 
      friend class PVReq;
    void setReadDataDestination(DT* arg_readData);
    DT* getReadDataDestination() const;
    
    template <typename DT_, typename AT_>
    friend class PVTlmIpt;
    template <typename DT_, typename AT_>
    friend class PostTlmIpt;
    PVRespData<DT>& getRespData() const;

  public : 
    //constructor
    PVResp(PVRespData<DT>* theRespData);
    PVResp() : m_respData(0) {}

    //destructor
    virtual ~PVResp();
        
    void setResponse( PVResponse arg_response);
    PVResponse getResponse() const;
    
    void setLatency( unsigned int arg_latency);
    unsigned int getLatency() const;
    
    void setReadData(DT arg_data, unsigned int index = 0);
    DT getReadData( unsigned int index = 0) const;
    
    void setCustomData(PVCustomResp& arg_customData);
    PVCustomResp& getCustomData() const;
    void setProtocolData(PVProtocolResp& arg_protocolData);
    PVProtocolResp& getProtocolData() const;
    virtual void copy_response( const PVResp & resp);
};

/*******************************************************************************
*	PVRespData class Definition
*
*       Contains actual PVResp data members.  Can not be copied by accident, 
*       to avoid a hit on performance.
*	Members can only be accessed by PVResp class
*******************************************************************************/

template <typename DT>
class PVRespData{

  template <typename DT_, typename AT_> friend class PVReq; 
  template <typename DT_> friend class PVResp;  
  template <typename T> friend class scv_extensions;
  template <typename DT_, typename AT_> friend class PVTlmIpt;
  template <typename DT_, typename AT_> friend class PostTlmIpt;

  
  protected :
  
    //constructor
    PVRespData():
      m_response(pvOk),
      m_latency(0),
      m_readData(0),
      m_customData(0),
      m_protocolData(0)
    {}
    //destructor
    ~PVRespData(){};      
    //data members
    PVResponse m_response;
    unsigned int m_latency;
    DT* m_readData;
    PVCustomResp* m_customData;
    PVProtocolResp* m_protocolData;

  private :    
  
    //disable copy constructor
    PVRespData(const PVRespData& copy);
    //disable assignment
    PVRespData& operator = (const PVRespData&);
};

/*******************************************************************************
* 	PVReq member function implementations
*******************************************************************************/

template< typename DT, typename AT>
inline 
PVReq<DT,AT>::PVReq() : 
  m_transactionID( 0),
  m_predecessorID( 0),
  m_address( 0),
  m_writeData( 0),
  m_type( pvRead),
  m_dataSize( 32),
  m_offset( 0),
  m_burstCount( 0),
  m_customData( 0),
  m_protocolData( 0),
  m_resp( 0),
  m_respData( new PVRespData<DT>()),
  m_burstType( pvIncr),
  m_threadID( 0),
  m_mode( pvDefault )
{
  this->m_resp = new PVResp<DT>(m_respData);
};

template< typename DT>
inline
PVReq<DT,void>::PVReq() : 
  m_transactionID( 0),
  m_predecessorID( 0),
  m_writeData( 0),
  m_type( pvRead),
  m_dataSize( 32),
  m_offset( 0),
  m_burstCount( 0),
  m_customData( 0),
  m_protocolData( 0),
  m_resp( 0),
  m_respData( new PVRespData<DT>()),
  m_burstType( pvIncr),
  m_threadID( 0),
  m_mode( pvDefault )
{
  this->m_resp = new PVResp<DT>(m_respData);
};

template <typename DT, typename AT>
inline PVReq<DT,AT>::~PVReq(){
  delete this->m_resp;
  delete this->m_respData;
};

template <typename DT>
inline PVReq<DT,void>::~PVReq(){
  delete this->m_resp;
  delete this->m_respData;
};
    
template <typename DT, typename AT>
inline void PVReq<DT,AT>::setAddress( AT arg_address ){
  this->m_address = arg_address;
};

template <typename DT, typename AT>
inline AT PVReq<DT,AT>::getAddress() const{
  return this->m_address;
};

template <typename DT, typename AT>
inline void PVReq<DT,AT>::setWriteDataSource( DT* arg_writeData){
  this->m_writeData = arg_writeData;
};

template <typename DT>
inline void PVReq<DT,void>::setWriteDataSource( DT* arg_writeData){
  this->m_writeData = arg_writeData;
};

template <typename DT, typename AT>
inline DT* PVReq<DT,AT>::getWriteDataSource() const{
  return this->m_writeData;
};

template <typename DT>
inline DT* PVReq<DT,void>::getWriteDataSource() const{
  return this->m_writeData;
};

template <typename DT, typename AT>
inline DT PVReq<DT,AT>::getWriteData(unsigned int arg_index) const{
  return this->m_writeData[arg_index];
};

template <typename DT>
inline DT PVReq<DT,void>::getWriteData(unsigned int arg_index) const{
  return this->m_writeData[arg_index];
};

template <typename DT, typename AT>
inline void PVReq<DT,AT>::setType(PVType arg_type){
  this->m_type = arg_type;
};

template <typename DT>
inline void PVReq<DT,void>::setType(PVType arg_type){
  this->m_type = arg_type;
};

template <typename DT, typename AT>
inline PVType PVReq<DT,AT>::getType() const{
  return this->m_type;
};

template <typename DT>
inline PVType PVReq<DT,void>::getType() const{
  return this->m_type;
};


template <typename DT, typename AT>
inline void PVReq<DT,AT>::setDataSize(unsigned int arg_dataSize){
  this->m_dataSize = arg_dataSize;
};

template <typename DT>
inline void PVReq<DT,void>::setDataSize(unsigned int arg_dataSize){
  this->m_dataSize = arg_dataSize;
};

template <typename DT, typename AT>
inline unsigned int PVReq<DT,AT>::getDataSize() const{
  return this->m_dataSize;
};

template <typename DT>
inline unsigned int PVReq<DT,void>::getDataSize() const{
  return this->m_dataSize;
};

template <typename DT, typename AT>
inline void PVReq<DT,AT>::setOffset(unsigned int arg_offset){
  this->m_offset = arg_offset;
};

template <typename DT >
inline void PVReq<DT,void>::setOffset(unsigned int arg_offset){
  this->m_offset = arg_offset;
};

template <typename DT, typename AT>
inline unsigned int PVReq<DT,AT>::getOffset() const{
  return this->m_offset;
};

template <typename DT>
inline unsigned int PVReq<DT, void>::getOffset() const{
  return this->m_offset;
};

template <typename DT, typename AT>
inline void PVReq<DT,AT>::setBurstCount(unsigned int arg_burstCount){
  this->m_burstCount = arg_burstCount;
};

template <typename DT>
inline void PVReq<DT,void>::setBurstCount(unsigned int arg_burstCount){
  this->m_burstCount = arg_burstCount;
};


template <typename DT, typename AT>
inline unsigned int PVReq<DT,AT>::getBurstCount() const{
  return this->m_burstCount;
};

template <typename DT>
inline unsigned int PVReq<DT,void>::getBurstCount() const{
  return this->m_burstCount;
};

template <typename DT, typename AT>
inline void PVReq<DT,AT>::setCustomData(PVCustomReq& arg_customData){
  this->m_customData = &arg_customData;
};

template <typename DT>
inline void PVReq<DT,void>::setCustomData(PVCustomReq& arg_customData){
  this->m_customData = &arg_customData;
};


template <typename DT, typename AT>
inline PVCustomReq& PVReq<DT,AT>::getCustomData() const{
  return *(this->m_customData);
};

template <typename DT>
inline PVCustomReq& PVReq<DT,void>::getCustomData() const{
  return *(this->m_customData);
};

template <typename DT, typename AT>
inline PVProtocolReq& PVReq<DT,AT>::getProtocolData() const{
  return *(this->m_protocolData);
};

template <typename DT>
inline PVProtocolReq& PVReq<DT,void>::getProtocolData() const{
  return *(this->m_protocolData);
};

template <typename DT, typename AT>
inline PVProtocolResp& PVReq<DT,AT>::getProtocolRespData() const{
  return this->obtainResp().getProtocolData();
};

template <typename DT>
inline PVProtocolResp& PVReq<DT,void>::getProtocolRespData() const{
  return this->obtainResp().getProtocolData();
};

template <typename DT, typename AT>
inline void PVReq<DT,AT>::setProtocolData(PVProtocolReq& arg_protocolData){
  this->m_protocolData = &arg_protocolData;
};

template <typename DT>
inline void PVReq<DT,void>::setProtocolData(PVProtocolReq& arg_protocolData){
  this->m_protocolData = &arg_protocolData;
};

template <typename DT, typename AT>
inline void PVReq<DT,AT>::setProtocolRespData(PVProtocolResp& arg_protocolData){
  this->obtainResp().setProtocolData(arg_protocolData);
};

template <typename DT>
inline void PVReq<DT,void>::setProtocolRespData(PVProtocolResp& arg_protocolData){
  this->obtainResp().setProtocolData(arg_protocolData);
};


template <typename DT, typename AT>
inline void PVReq<DT,AT>::setPredecessorHandle(unsigned h) {
  this->m_predecessorID = h;
}

template <typename DT>
inline void PVReq<DT>::setPredecessorHandle(unsigned h) {
  this->m_predecessorID = h;
}

template <typename DT, typename AT>
inline unsigned PVReq<DT,AT>::getPredecessorHandle() const {
  return m_predecessorID;
}

template <typename DT>
inline unsigned PVReq<DT>::getPredecessorHandle() const {
  return m_predecessorID;
}



template <typename DT, typename AT>
inline PVResp<DT> PVReq<DT,AT>::obtainResp() const {
  return *(this->m_resp);
};

template <typename DT>
inline PVResp<DT> PVReq<DT,void>::obtainResp() const {
  return *(this->m_resp);
};

template <typename DT, typename AT>
inline void PVReq<DT,AT>::setReadDataDestination(DT* arg_readData) {
  this->m_resp->setReadDataDestination(arg_readData);
};

template <typename DT>
inline void PVReq<DT,void>::setReadDataDestination(DT* arg_readData) {
  this->m_resp->setReadDataDestination(arg_readData);
};

template <typename DT, typename AT>
inline DT* PVReq<DT,AT>::getReadDataDestination() const {
  return this->m_resp->getReadDataDestination();
};

template <typename DT>
inline DT* PVReq<DT,void>::getReadDataDestination() const {
  return this->m_resp->getReadDataDestination();
};

template< typename DT, typename AT>
inline
void PVReq< DT, AT>::copy_request( const PVReq & req)
{
  setAddress( req.getAddress());
  setWriteDataSource( req.getWriteDataSource());   
  setType( req.getType());
  setDataSize( req.getDataSize());
  setOffset( req.getOffset());
  setBurstCount( req.getBurstCount());
  setReadDataDestination( req.getReadDataDestination());
  setCustomData( req.getCustomData());
  setProtocolData( req.getProtocolData());
  setBurstType( req.getBurstType());
  setThreadID( req.getThreadID());
  setMode( req.getMode());
  m_predecessorID = req.m_predecessorID;
}

template< typename DT>
inline
void PVReq< DT, void>::copy_request( const PVReq & req)
{
  setWriteDataSource( req.getWriteDataSource());   
  setType( req.getType());
  setDataSize( req.getDataSize());
  setOffset( req.getOffset());
  setBurstCount( req.getBurstCount());
  setReadDataDestination( req.getReadDataDestination());
  setCustomData( req.getCustomData());
  setProtocolData( req.getProtocolData());
  setBurstType( req.getBurstType());
  setThreadID( req.getThreadID());
  setMode( req.getMode());
  m_predecessorID = req.m_predecessorID;
}

template< typename DT, typename AT>
inline
void PVReq< DT, AT>::setBurstType( PVBurstType a )
{
  this->m_burstType = a;
}

template< typename DT>
inline
void PVReq< DT, void>::setBurstType( PVBurstType a )
{
  this->m_burstType = a;
}

template< typename DT, typename AT>
inline
PVBurstType 
PVReq< DT, AT>::getBurstType() const
{
  return this->m_burstType;
}

template< typename DT>
inline
PVBurstType 
PVReq< DT, void>::getBurstType() const
{
  return this->m_burstType;
}

template< typename DT, typename AT>
inline
void
PVReq< DT, AT>::setThreadID( unsigned int a)
{
  this->m_threadID = a; 
}

template< typename DT>
inline
void
PVReq< DT, void>::setThreadID( unsigned int a)
{
  this->m_threadID = a; 
}

template< typename DT, typename AT>
inline
unsigned int 
PVReq< DT, AT>::getThreadID() const
{
  return this->m_threadID; 
}

template< typename DT>
inline
unsigned int 
PVReq< DT, void>::getThreadID() const
{
  return this->m_threadID; 
}

template< typename DT, typename AT>
inline
void
PVReq< DT, AT>::setMode( PVMode a)
{
  this->m_mode = a;
}

template< typename DT>
inline
void
PVReq< DT, void>::setMode( PVMode a)
{
  this->m_mode = a;
}

template< typename DT, typename AT>
inline
PVMode 
PVReq< DT, AT>::getMode() const
{
  return this->m_mode;
}

template< typename DT>
inline
PVMode 
PVReq< DT, void>::getMode() const
{
  return this->m_mode;
}

/*******************************************************************************
* 	PVRespData member function implementations
*******************************************************************************/

/*******************************************************************************
* 	PVResp member function implementations
*******************************************************************************/


template <typename DT>
inline void PVResp<DT>::setReadDataDestination(DT* arg_readData) {
  this->m_respData->m_readData = arg_readData;
};

template <typename DT>
inline DT* PVResp<DT>::getReadDataDestination() const {
  return this->m_respData->m_readData;
};

template <typename DT>
inline PVRespData<DT>& PVResp<DT>::getRespData() const
{
  assert(m_respData);
  return *m_respData;
}

template <typename DT>
inline PVResp<DT>::PVResp(PVRespData<DT>* theRespData) : m_respData(theRespData){
};

template <typename DT>
inline PVResp<DT>::~PVResp(){
};

template <typename DT>
inline void PVResp<DT>::setResponse( PVResponse arg_response){
  this->m_respData->m_response = arg_response;
};

template <typename DT>
inline PVResponse PVResp<DT>::getResponse() const {
  return this->m_respData->m_response;
};

template <typename DT>
inline void PVResp<DT>::setLatency( unsigned int arg_latency){
  this->m_respData->m_latency = arg_latency;
};

template <typename DT>
inline unsigned int PVResp<DT>::getLatency() const {
  return this->m_respData->m_latency;
};

template <typename DT>
inline void PVResp<DT>::setReadData(DT arg_data, unsigned int index){
  this->m_respData->m_readData[index] = arg_data;
};

template <typename DT>
inline DT
PVResp< DT>::getReadData( unsigned int index) const {
  return this->m_respData->m_readData[ index];
}; 

template <typename DT>
inline void PVResp<DT>::setCustomData(PVCustomResp& arg_customData){
  this->m_respData->m_customData = &arg_customData;
};

template <typename DT>
inline PVCustomResp& PVResp<DT>::getCustomData() const {
  return *(this->m_respData->m_customData);  
};

template <typename DT>
inline void PVResp<DT>::setProtocolData(PVProtocolResp& arg_protocolData){
  this->m_respData->m_protocolData = &arg_protocolData;
};

template <typename DT>
inline PVProtocolResp& PVResp<DT>::getProtocolData() const {
  return *(this->m_respData->m_protocolData);  
};

template< typename DT>
inline
void
PVResp<DT>::copy_response( const PVResp & resp)
{
  setResponse( resp.getResponse());
  setLatency( resp.getLatency());
  setCustomData( resp.getCustomData());
  setProtocolData( resp.getProtocolData());
}

#endif
