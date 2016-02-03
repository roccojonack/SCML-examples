/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_TYPES_H
#define SCML2_TYPES_H

namespace scml2 {

enum SyncType { AUTO_SYNCING, SELF_SYNCING, NEVER_SYNCING };

enum access_type { ACCESS_TYPE_UNKNOWN = 0,
                   ACCESS_TYPE_READ    = 1,
                   ACCESS_TYPE_WRITE   = 2,
                   ACCESS_TYPE_ACCESS  = 3 };
enum access_mode { ACCESS_MODE_UNKNOWN = 0,
                   ACCESS_MODE_REGULAR = 1,
                   ACCESS_MODE_DEBUG   = 2,
                   ACCESS_MODE_ACCESS  = 3 };
}

#endif
