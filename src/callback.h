
#pragma once

#include <node.h>
#include <nan.h>
#include <girepository.h>
#include <glib-object.h>
#include <ffi.h>
#include <girffi.h>

#include "closure.h"
#include "function.h"

namespace GNodeJS {

struct Callback {
    ffi_cif cif;
    ffi_closure *closure;
    Nan::Persistent<Function> persistent;
    GICallableInfo *info;
    GIScopeType scope_type;
    Parameter* call_parameters;

    Callback(Local<Function> fn, GICallableInfo* callback_info, GIScopeType scope_type_);
    ~Callback();

    static void DestroyNotify (void* user_data);
    static void AsyncFree ();
    static void Execute (GIArgument *result, GIArgument **args, Callback *callback);
    static void Call (ffi_cif *cif, void *result, void **args, gpointer user_data);
};

};
