/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

void PyDict_SetVerstionString(PyObject * m, const char * version)
{
    ///
    PyObject *d = PyModule_GetDict(m);
            
    /* Make the version available */
    PyObject *v = PyUnicode_FromString(version);
    
    /* Make the version available */
    PyDict_SetItemString(d, "version", v);
    Py_DECREF(v);
    
    PyDict_SetItemString(d, "__version__", v);
    Py_DECREF(v);
}


