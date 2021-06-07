/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#include "Py_GL.h"
#include "Py_ext.h"

#include "asset/asset_manager.h"

#include "renderer/GL/GL_ext.h"
#include "renderer/GL/GL_texture.h"

#include "renderer/texture.h"
#include "renderer/shader.h"

#include "core/Application.h"

/**
 * @brief 
 * 
 */
static PyObject * PyGL_error_;

typedef struct {
    PyObject_HEAD
    PyObject *first; /* first name */
    PyObject *last;  /* last name */
    int number;
} CustomObject;


extern PyTypeObject CustomType;

/**
 * @brief 
 * 
 * @param self 
 * @param args 
 * @return PyObject* 
 */
static PyObject *
PyGL_ActiveTexture(PyObject *self, PyObject *args)
{
    __function__
    
    const char *command;
    int sts;
    
    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;

    sts = system(command);
    if (sts < 0)
    {
        PyErr_SetString(PyGL_error_, "System command failed");
        return NULL;
    }

    return PyLong_FromLong(sts);

#if 0
    const char* xml_name = "sprite.shader.xml";

    char pathname[PATH_MAX];
    sprintf(pathname, "%s/%s", theApp->dataPath(), xml_name);

    auto tex1 = asset_manager::get()->import<GL::shader>(pathname);
    COUT << "1. tex1: " << (tex1 ? __typeid_name(*tex1):"nullptr") << ENDL;

/*
        // Build the name object
        PyObject *pName, *pFunc, *pValue, *presult;
        pName = PyUnicode_FromString("noddy");
        
        // Load the module object
        PyImport_Import(pName);
        
        PyObject* pModule = NoddyType.tp_new(&NoddyType, NULL, NULL);
        
        Object args, kwds;
        args=Py_BuildValue("ssi", "first", "last", 100);
        NoddyType.tp_init(pModule, args, kwds);
        
        
        ///
        pFunc = PyObject_GetAttrString(pModule, "name");
        if (PyCallable_Check(pFunc))
        {
            //pValue=Py_BuildValue("(z)", "ls -l");
            PyErr_Print();
            printf("Noddy.name\n");
            presult=PyObject_CallObject(pFunc, pValue);
            PyErr_Print();
        } else
        {
            PyErr_Print();
        }
    }
*/

        PyObject* pModule = CustomType.tp_new(&CustomType, NULL, NULL);
        
        //PyObject *args1, *kwds;
        //args1=Py_BuildValue("ssi", "first", "last", 100);
        //CustomType.tp_init(pModule, args1, kwds);

    //return Py_ptr(&tex1);

    
    return pModule;
#endif    
}


/*
static PyObject *
PyApplication_dataPath(PyObject *self, PyObject *args)
{
    __function__
    
    return PyUnicode_FromString(theApp->dataPath());
}*/

/**
 * @brief 
 * 
 * @param self 
 * @param args 
 * @return PyObject* 
 */
static PyObject *
PyGL_ClientActiveTexture(PyObject *self, PyObject *args)
{
    __function__
    
    int command;
    int sts = 1;
    
    if (!PyArg_ParseTuple(args, "i", &command))
        return NULL;
    
    printf("i = %d\n", command);
    
    return PyLong_FromLong(sts);
}


/**
 * @brief 
 * 
 */
static PyMethodDef PyGL_methods[] =
{
    {   "ActiveTexture",
        (PyCFunction) PyGL_ActiveTexture,
        METH_VARARGS,
        "Execute a shell command."
    },
    {   "ClientActiveTexture",
        (PyCFunction) PyGL_ClientActiveTexture,
        METH_VARARGS,
        "Execute a shell command."
    },
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


/**
 * @brief 
 * 
 */
static struct PyModuleDef PyGL_module =
{
    PyModuleDef_HEAD_INIT,

    "GL",   /* name of module */
    "Example module that creates an extension type.", /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
               or -1 if the module keeps state in global variables. */
    PyGL_methods
};


/**
 * @brief 
 * 
 */
static const char * PyGL_Version_ = "0.0.1";


/**
 * @brief 
 * 
 * @return PyMODINIT_FUNC 
 */
PyMODINIT_FUNC PyInit_GL(void)
{
    //__function__
        
    ///
    PyObject *m;
    m = PyModule_Create(&PyGL_module);
    if (m == NULL)
        return NULL;

    /* For exception curses.error */
    PyGL_error_ = PyErr_NewException("GL.error", NULL, NULL);
    Py_INCREF(PyGL_error_);

    ///PyDict_SetItemString(d, "error", PyApplication_error);

    if (PyModule_AddObject(m, "error", PyGL_error_) < 0) 
    {
        Py_XDECREF(PyGL_error_);
        Py_CLEAR(PyGL_error_);
        Py_DECREF(m);
        return NULL;
    }

    PyDict_SetVerstionString(m, PyGL_Version_);

    return m;
}
