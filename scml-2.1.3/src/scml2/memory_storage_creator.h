/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_STORAGE_CREATOR_H
#define SCML2_MEMORY_STORAGE_CREATOR_H

namespace scml2 {

class memory_storage_base;
class toplevel_memory_base;

class memory_storage_creator
{
public:
  typedef memory_storage_base* (*StorageCreator)(toplevel_memory_base&);

  void set_storage_creator(StorageCreator c);
  StorageCreator get_storage_creator() const;
  memory_storage_base* create_storage(toplevel_memory_base& m);

public:
  static memory_storage_creator& get_instance();

private:
  memory_storage_creator();
  memory_storage_creator(const memory_storage_creator&);
  memory_storage_creator& operator=(const memory_storage_creator&);

private:
  StorageCreator mStorageCreator;
};

}

#endif
