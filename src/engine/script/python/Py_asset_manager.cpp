/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#include "Application.h"

#include "asset_manager.h"

#include "GL/GL_texture.h"

#include "texture.h"
#include "shader.h"

#include "PyUtils.h"

typedef struct {
    PyObject_HEAD
    /* Type-specific fields go here. */
    PyObject * asset_ptr;
} Py_asset_object;

static PyTypeObject Py_asset_object_type = {
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

static PyObject *
Py_asset_import(PyObject *self, PyObject *args)
{
    __function__
    
    const char *command;
    int sts;
    
    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;

    const char* xml_name = "sprite.shader.xml";

    char pathname[PATH_MAX];
    sprintf(pathname, "%s/%s", theApp->dataPath(), xml_name);

    auto tex1 = asset_manager::get()->import<GL::shader>(pathname);
    COUT << "1. tex1: " << (tex1 ? __typeid_name(*tex1):"nullptr") << ENDL;

    auto pp = PyObject_New(Py_asset_object, &Py_asset_ptr_type);
    pp->asset_ptr = Py_ptr(&tex1);

    return (PyObject*) pp;
}



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
