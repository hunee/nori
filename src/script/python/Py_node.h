/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

typedef struct {
    PyObject_HEAD
    PyObject *node_ptr; //Py_Capsule
    PyObject *name;
    int number;

    /* weak references */
	PyObject *weakreflist;
    PyObject *owner;  
} Py_node_object;


extern PyTypeObject Py_node_type;

PyMODINIT_FUNC PyInit_node(void);

