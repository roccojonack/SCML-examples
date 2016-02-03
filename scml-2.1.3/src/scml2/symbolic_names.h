/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_SYMBOLIC_NAMES_H
#define SCML2_SYMBOLIC_NAMES_H

#include <string>
#include <vector>
#include <map>

namespace scml2 {

class symbolic_names
{
public:
  typedef std::pair<std::vector<unsigned char>, std::string> SymbolicName;
  typedef std::vector<SymbolicName> SymbolicNames;
  typedef SymbolicNames::iterator SymbolicNamesIterator;
  typedef SymbolicNames::const_iterator SymbolicNamesConstIterator;
  
public:
  virtual ~symbolic_names();

  bool set_symbolic_name(const std::vector<unsigned char>& value,
                         const std::string& name);
  unsigned int collect_symbolic_names(SymbolicNames& symbolicNames) const;

private:
  typedef std::map<std::vector<unsigned char>, std::string> ValueNameMap;
  ValueNameMap mValueNameMap;
  typedef std::map<std::string, std::vector<unsigned char> > NameValueMap;
  NameValueMap mNameValueMap;
};

}

#endif
