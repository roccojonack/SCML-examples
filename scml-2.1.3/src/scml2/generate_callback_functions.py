#!/bin/env python

import sys

mode = sys.argv[1]

class Call :
  def __init__(self, name = "", parameters = []) :
    self.name = name
    self.parameters = parameters

  def to_string(self) :
    result = self.name 
    if self.parameters != None :
      result += "("
      params = []
      for param in self.parameters :
        if isinstance(param, str) :
          params.append(param)
        else :
          params.append(param.to_string())
      result += ", ".join(params)
      result += ")"
    return result

class Configuration :
  def __init__(self, behavior, callback_variant = None, tagged = False, timed = False, extensions = False) :
    self.behavior = behavior
    self.callback_variant = callback_variant
    self.tagged = tagged
    self.timed = timed
    self.extensions = extensions

def behavior_access_type(behavior) :
  if behavior in ["clear_on_read", "set_on_read", "mask_read", "read"] :
    return "read"
  if behavior in ["clear_on_write_0", "set_on_write_0", "clear_on_write_1", "set_on_write_1", "mask_write", "write", "write_once_ignore", "write_once_error"] :
    return "write"


# Create the set of configurations
behaviors = [
    "read", # Default read behavior
    "clear_on_read",
    "set_on_read",
    "write", # No write behavior
    "clear_on_write_0",
    "clear_on_write_1",
    "set_on_write_0",
    "set_on_write_1",
    "write_once_ignore",
    "write_once_error",
  ]
if mode == "memory" :
  behaviors += ["read+write"] # Default access behavior

configurations = []
for behavior in behaviors :
  # Behavior without callback
  if not behavior in ["read", "write", "read+write"] :
    configurations.append(Configuration(behavior)) 

  # Behavior with callback
  callback_variants = []
  if mode == "memory" :
    callback_variants += ["transport"]
    if behavior != "read+write" :
      callback_variants += [behavior_access_type(behavior), "word_" + behavior_access_type(behavior)]
  else :
      callback_variants += [behavior_access_type(behavior), "mask_" + behavior_access_type(behavior)]
  if behavior_access_type(behavior) == "write" :
    callback_variants += ["post_write"]

  for callback_variant in callback_variants :
    for tagged in [False, True] :
      for timed in [True, False] :
        for extensions in [False, True] :
          if extensions and mode == "bitfield" :
            continue
          if callback_variant == "post_write" and (timed or extensions) :
            continue
          if callback_variant == "transport" and extensions :
            continue
          configurations.append(Configuration(behavior, callback_variant, tagged, timed, extensions))

  
# Generate code for each configuration
print "#ifndef SCML2_" + mode.upper() + "_CALLBACK_FUNCTIONS_INCLUDE_H"
print "#define SCML2_" + mode.upper() + "_CALLBACK_FUNCTIONS_INCLUDE_H"

print "namespace scml2 {"
for conf in configurations :
  object = "mem" if mode == "memory" else "bitfield"

  #############
  # Signature
  #############

  return_type = "void"
  if conf.behavior in ["write_once_error", "write_once_ignore"] :
    return_type = "write_once_state*"

  if conf.callback_variant == None :
    if mode == "memory" :
      print "template <typename DT, template <typename> class MEM_OBJECT>"
      print "inline " + return_type + " set_" + conf.behavior + "(MEM_OBJECT<DT>& mem, SyncType syncType = AUTO_SYNCING) {"
    elif mode == "bitfield" :
      print "template <typename DT>"
      print "inline " + return_type + " set_" + conf.behavior + "(bitfield<DT>& bitfield, SyncType syncType = AUTO_SYNCING) {"
  else :
    adapter = ""
    if mode == "bitfield" :
      adapter = "bitfield_"
    extra_arguments = ""

    if not conf.timed and not conf.callback_variant == "post_write" :
      adapter += "untimed_"
    adapter += conf.callback_variant
    if conf.extensions :
      adapter += "_extensions"
    adapter += "_adapter"
    if conf.tagged :
      adapter += "_tagged"
      extra_arguments += ", int id"
    if mode == "memory" :
      if conf.callback_variant in ["transport", "post_write"] :
        adapter += "<C>"
      else :
        adapter += "<MEM_OBJECT<DT>,C>"
    elif mode == "bitfield" :
      adapter += "<DT,C>"

    synctype_default = " = AUTO_SYNCING"
    if conf.tagged :
      synctype_default = ""

    function_name = "set_" + conf.behavior + "_callback"
    if conf.behavior == "read+write" :
      function_name = "set_callback"
    elif conf.callback_variant == "post_write" :
      function_name = "set_post_" + conf.behavior + "_callback"
    elif conf.callback_variant in ["word_read", "word_write"] :
      function_name = "set_word_" + conf.behavior + "_callback"

    if mode == "memory" :
      print "template <typename DT, template <typename> class MEM_OBJECT, typename C>"
      print "inline " + return_type + " " + function_name + "(MEM_OBJECT<DT>& mem, C* c, typename " + adapter + "::CallbackType cb, const std::string& cbName, SyncType syncType" + synctype_default + extra_arguments + ") {"
    elif mode == "bitfield" :
      print "template <typename DT, typename C>"
      print "inline " + return_type + " "  + function_name + "(bitfield<DT>& bitfield, C* c, typename " + adapter + "::CallbackType cb, const std::string& cbName, SyncType syncType" + synctype_default + extra_arguments + ") {"

  #######
  # Body
  #######

  if not conf.timed and conf.callback_variant != None :
    print "  if (syncType == SELF_SYNCING) {"
    print "    SCML2_LOG(" + object + ".get_streams().error())"
    print "      << \"SELF_SYNCING not supported for untimed callbacks on '\""
    print "      << " + object + ".get_name() << \"\'\""
    print "      << std::endl;"
    print "  }"
  if conf.callback_variant != None :
    print "  assert(c);"


  # Callback adapter
  call = Call()
  if conf.callback_variant == None :
    if mode == "memory" :
      call.name = "null_adapter"
    elif mode == "bitfield" :
      call.name = "bitfield_null_adapter<DT>"
  else :
    if mode == "memory" :
      call.name = "create_" + conf.callback_variant + "_adapter"
    elif mode == "bitfield" :
      if conf.callback_variant == "mask_read" :
        actual_variant = "read"
      elif conf.callback_variant == "mask_write" :
        actual_variant = "write"
      else :
        actual_variant = conf.callback_variant
      call.name = "create_bitfield_" + actual_variant + "_adapter<DT>"
    call.parameters = ["*c", "cb"]
    if conf.tagged :
      call.parameters += ["id"]
    if mode == "memory" and not conf.callback_variant in ["transport", "post_write"] :
      call.parameters += [object]

  # Word unroller
  if mode == "memory" :
    if conf.callback_variant in ["read", "write"] :
      call = Call("create_word_access_unroller<DT>", [call])

  # Behavior adapter
  if conf.behavior in ["read", "read+write"] :
    call = Call("", [call, object])
    if mode == "memory" :
      call.name = "create_store_after_read_adapter"
    elif mode == "bitfield" :
      call.name = "create_bitfield_store_after_read_adapter<DT>"
  elif conf.behavior == "write" :
    if conf.callback_variant == "post_write" :
      call = Call("", [call, object])
      if mode == "memory" :
        call.name = "create_default_behavior_adapter"
      elif mode == "bitfield" :
        call.name = "create_bitfield_default_write_behavior_adapter"
  elif conf.behavior in ["clear_on_read", "set_on_read"] :
    if conf.callback_variant == None :
      call = Call("", [call, object])
      if mode == "memory" :
        call.name = "create_default_behavior_adapter"
      elif mode == "bitfield" :
        call.name = "create_bitfield_default_read_behavior_adapter<DT>"

    call = Call("", [call, object])
    if mode == "memory" :
      call.name = "create_set_on_read_adapter"
    elif mode == "bitfield" :
      call.name = "create_bitfield_set_on_read_adapter<DT>"
    if conf.behavior == "clear_on_read" :
      call.parameters += ["(DT) 0x0"]
    else :
      call.parameters += ["~(DT) 0x0"]
  elif behavior_access_type(conf.behavior) == "write" :
    if conf.behavior in ["write_once_error", "write_once_ignore"] :
      call = Call("", [call, object])
      if mode == "memory" :
        call.name = "create_default_behavior_adapter"
      elif mode == "bitfield" :
        call.name = "create_bitfield_default_write_behavior_adapter"

    call = Call("create_" + ("bitfield_" if mode == "bitfield" else "") + conf.behavior + "_adapter", [call, object])
    if conf.callback_variant == "post_write" :
      call.name += "<true>"
    else :
      call.name += "<false>"

  # Store the result state
  if conf.behavior in ["write_once_error", "write_once_ignore"] :
    print "  " + return_type + " result;"
    call.parameters += ["&result"];

  # Memory/bitfield callback
  if mode == "memory" :
    call = Call("create_memory_callback", [call, "cbName", "syncType"])
  elif mode == "bitfield" :
    call = Call("create_bitfield_" + behavior_access_type(conf.behavior) + "_callback<DT>", [call, "cbName", "syncType"])

  if conf.callback_variant == None :
    call.parameters[1] = "\"<" + conf.behavior + ">\""

  # Memory/bitfield callback registration
  call = Call(object + ".set_callback", [call])
  if conf.behavior != "read+write" :
    call.name = object + ".set_" + behavior_access_type(conf.behavior) + "_callback"

  print "  " + call.to_string() + ";"

  # Return result if necessary
  if conf.behavior in ["write_once_error", "write_once_ignore"] :
    print "  return result;"

  print "}\n"

print "}"

print "#endif"
