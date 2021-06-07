/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"


#include "Py_Application.h"

#include "Py_ext.h"
#include "Py_node.h"

#include "core/Application.h"
#include "asset/asset_manager.h"

/**
 * @brief 
 * 
 */
static PyObject * PyApplication_error_;


/**
 * @brief 
 * 
 * @param self 
 * @param args 
 * @return PyObject* 
 */
static PyObject *
PyApplication_dataPath(PyObject *self, PyObject *args)
{
    __function__

    auto amgr = asset_manager::get();    
    return PyUnicode_FromString(amgr->data_path());
}


/**
 * @brief 
 * 
 * @param self 
 * @param args 
 * @return PyObject* 
 */
static PyObject *
PyApplication_dummy_runLoop(PyObject *self, PyObject *args)
{
 //   __function__
    
    int command;
    int sts = 1;
    
    if (!PyArg_ParseTuple(args, "i", &command))
        return NULL;
    
    //printf("i = %d\n", command);
    
    return PyLong_FromLong(sts);
}


/**
 * @brief 
 * 
 */
static PyObject * PyApplication_runLoop_ = NULL;


/**
 * @brief 
 * 
 * @param self 
 * @param args 
 * @return PyObject* 
 */
static PyObject *
PyApplication_set_runLoop(PyObject *self, PyObject *args)
{
    ///__py_function__
    
    PyObject *result = NULL;
    PyObject *temp;
    
    if (PyArg_ParseTuple(args, "O:runLoop", &temp))
    {
        if (!PyCallable_Check(temp))
        {
            PyErr_SetString(PyExc_TypeError, "parameter must be callable");
            return NULL;
        }
        Py_XINCREF(temp);         /* Add a reference to new callback */
        
        Py_XDECREF(PyApplication_runLoop_);  /* Dispose of previous callback */
        PyApplication_runLoop_ = temp;       /* Remember new callback */
        
        /* Boilerplate to return "None" */
        Py_INCREF(Py_None);
        result = Py_None;
    }
    return result;
}


/**
 * @brief 
 * 
 * @param self 
 * @param args 
 * @return PyObject* 
 */
static PyObject *
PyApplication_runLoop(PyObject *self, PyObject *args)
{
    __py_function__
    
    return PyObject_CallObject(PyApplication_runLoop_, args);
}


/**
 * @brief 
 * 
 */
static PyMethodDef PyApplication_methods[] =
{
    {   "dataPath",
        (PyCFunction) PyApplication_dataPath,
        METH_NOARGS,
        "Execute a shell command."
    },
    {   "set_runLoop",
        (PyCFunction) PyApplication_set_runLoop,
        METH_VARARGS,
        "Execute a shell command."
    },
    {   "runLoop",
        (PyCFunction) PyApplication_runLoop,
        METH_VARARGS,
        "Execute a shell command."
    },
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


/**
 * @brief 
 * 
 */
static struct PyModuleDef PyApplication_module =
{
    PyModuleDef_HEAD_INIT,
    "Application",   /* name of module */
    "Example module that creates an extension type.", /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
               or -1 if the module keeps state in global variables. */
    PyApplication_methods
};


/**
 * @brief 
 * 
 * @param arg 
 * @return int 
 */
int PyApplication_runLoop(int arg)
{
    PyObject *arglist;
    PyObject *result;
    
    /* Time to call the callback */
    arglist = Py_BuildValue("(i)", arg);
    result = PyObject_CallObject(PyApplication_runLoop_, arglist/*NULL*/);
    Py_DECREF(arglist);

    return 1;
}


/**
 * @brief 
 * 
 * @param method 
 * @return int 
 */
static int PyApplication_set_runLoop(PyCFunction method)
{
    //__function__
    
    static PyMethodDef runLoop_method = {
        "runLoop",
        (PyCFunction) method,
        METH_VARARGS,
        "A new function"
    };
    
    PyObject* name = PyUnicode_FromString(runLoop_method.ml_name);
    PyObject* temp = PyCFunction_NewEx(&runLoop_method, NULL, name);

    Py_DECREF(name);

    ///
    if (!PyCallable_Check(temp)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be callable");
        return 0;
    }
    
    Py_XINCREF(temp);         /* Add a reference to new callback */
    
    Py_XDECREF(PyApplication_runLoop_);  /* Dispose of previous callback */
    PyApplication_runLoop_ = temp;       /* Remember new callback */
    
    return 1;
}



static const char* PyAppication_Version_ = "0.0.1";

/**
 * @brief 
 * 
 * @return PyMODINIT_FUNC 
 */
PyMODINIT_FUNC 
PyInit_Application(void)
{
///    __function__
        
    ///
    PyObject *m;
    m = PyModule_Create(&PyApplication_module);
    if (m == NULL)
        return NULL;
    

    /* For exception curses.error */
    PyApplication_error_ = PyErr_NewException("Application.error", NULL, NULL);
    Py_INCREF(PyApplication_error_);

    ///PyDict_SetItemString(d, "error", PyApplication_error);
    
    if (PyModule_AddObject(m, "error", PyApplication_error_) < 0) 
    {
        Py_XDECREF(PyApplication_error_);
        Py_CLEAR(PyApplication_error_);

        Py_DECREF(m);
        return NULL;
    }


    ///
    PyDict_SetVerstionString(m, PyAppication_Version_);

    ///
    PyObject *d;
    d = PyModule_GetDict(m);

    auto amgr = asset_manager::get();    

    /* Make the path available */
    Py_DICT_SETITEMSTRING(d, "path", amgr->path());
    Py_DICT_SETITEMSTRING(d, "dataPath", amgr->data_path());
    Py_DICT_SETITEMSTRING(d, "persistentDataPath", amgr->persistent_data_path());
    Py_DICT_SETITEMSTRING(d, "temporaryCachePath", amgr->temporary_cache_path());


    // theApp->root_
    {
        // Load the module object
        //PyObject *name = PyUnicode_FromString("node");
        //PyImport_Import(name);

        //PyObject *v = Py_node_type.tp_new(&Py_node_type, NULL, NULL);

        ///PyObject *args = Py_BuildValue("ssi", "name", "root", 100);
        ///PyObject *kwargs = nullptr;//PyBuildValue("{s:O}", "name", root);        
        ///Py_node_type.tp_init((PyObject *) v, args, kwargs);

// c++ -> python
        auto v = PyObject_New(Py_node_object, &Py_node_type);

        auto p = theApp->root_.get();
        v->node_ptr = Py_ptr(p);
        v->owner = nullptr;
        v->name = PyUnicode_FromString("root_");
        v->number = 100;

        PyDict_SetItemString(d, "root", (PyObject *) v);
        Py_DECREF(v);

        ///COUT << "name: \"" << theApp->root_ << "\", type: " << __typeid_name(*theApp->root_) << ", use_count: " << theApp->root_.use_count() << ENDL;
    }

    ///
    PyApplication_set_runLoop(PyApplication_dummy_runLoop);
        
    return m;
}

