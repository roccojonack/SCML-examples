/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#pragma once

#define SCML2_FAIL(msg) \
  this->evaluate_assertion(false, msg, __FILE__, __LINE__)

#define SCML2_ASSERT_THAT(...) \
  this->evaluate_assertion(__VA_ARGS__, __FILE__, __LINE__)

