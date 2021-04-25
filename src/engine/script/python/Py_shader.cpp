/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

typedef struct {
    PyObject_HEAD
    /* Type-specific fields go here. */
    PyObject * asset_ptr;
} Py_asset_ptr_object;

static PyTypeObject Py_asset_ptr_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "GLX.asset_ptr",
    .tp_doc = "asset_ptr objects",
    .tp_basicsize = sizeof(Py_asset_ptr_object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
};

static PyModuleDef Py_GLX_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "GLX",
    .m_doc = "Example module that creates an extension type.",
    .m_size = -1,
};

PyMODINIT_FUNC
PyInit_GLX(void)
{
    PyObject *m;
    if (PyType_Ready(&Py_asset_ptr_type) < 0)
        return NULL;

    m = PyModule_Create(&Py_GLX_module);
    if (m == NULL)
        return NULL;

    Py_INCREF(&Py_asset_ptr_type);
    if (PyModule_AddObject(m, "asset_ptr", (PyObject *) &Py_asset_ptr_type) < 0) {
        Py_DECREF(&Py_asset_ptr_type);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
