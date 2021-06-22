/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

typedef struct {
    PyObject_HEAD
    PyObject *node_ptr; //Py_Capsule
    PyObject *name;
    int number;

    /* weak references */
	PyObject *weakreflist;
    PyObject *parent;  
} Py_shader_object;


extern PyTypeObject Py_shader_type;

PyMODINIT_FUNC PyInit_shader(void);

