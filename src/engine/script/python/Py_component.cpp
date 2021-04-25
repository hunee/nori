//
//  PY_component.cpp
//  noriApp
//
//  Created by jang jeonghun on 21/11/2017.
//  Copyright © 2017 hunee. All rights reserved.
//

#include "stdafx.h"

#include "structmember.h"

#include "Py_ext.h"

typedef struct {
    PyObject_HEAD
    PyObject *first; /* first name */
    PyObject *last;  /* last name */
    int number;
} CustomObject;

static int
Custom_traverse(CustomObject *self, visitproc visit, void *arg)
{
    LOGF();

    Py_VISIT(self->first);
    Py_VISIT(self->last);
    return 0;
}

static int
Custom_clear(CustomObject *self)
{
    LOGF();

    //if (self->first)
    Py_CLEAR(self->first);

    //if (self->last)
    Py_CLEAR(self->last);
    return 0;
}

static void
Custom_dealloc(CustomObject *self)
{
    LOGF();

    PyObject_GC_UnTrack(self);
    Custom_clear(self);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

class AAA {
public: 
    AAA() { std::cout << "AAA" << std::endl;}
    virtual ~AAA() { std::cout << "~AAA" << std::endl;}

    void print()
    {
        std::cout << "fdjsagfjhsgdfhgsdaj" << std::endl;
    }
};

/*
    void destroy_funkster(PyObject* funkster) {
        delete (MyClass*)PyCapsule_GetPointer(funkster, "val");
    }

    static PyObject* get_funkster_val(PyObject *self, PyObject *args) {
        PyObject* pf = NULL;
        if(!PyArg_UnpackTuple(args, "funk", 1, 1, &pf)) return NULL;
        MyClass* f = (MyClass*)PyCapsule_GetPointer(pf, "val");
        return PyLong_FromLong(f->val);
    }

    static PyObject* make_funkster(PyObject *self, PyObject *args) {
        return PyCapsule_New((void*)new MyClass(), "val", destroy_funkster);
    }


    int PyCapsule_CheckExact(PyObject *p);
*/

static PyObject *
Custom_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    LOGF();

    CustomObject *self;
    self = (CustomObject *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->first = PyUnicode_FromString("");
        if (self->first == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->last = PyUnicode_FromString("");
        if (self->last == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->number = 0;
    }
    
    return (PyObject *) self;
}

static int
Custom_init(CustomObject *self, PyObject *args, PyObject *kwds)
{
    LOGF();

    static const char *kwlist[] = {"first", "last", "number", NULL};
    PyObject *first = NULL, *last = NULL, *tmp;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|UUi", (char **) kwlist,
                                     &first, &last,
                                     &self->number))
        return -1;

///COUT << "111" << ENDL;

    if (first) {
        tmp = self->first;
        Py_INCREF(first);
        self->first = first;
        Py_DECREF(tmp);
    }
    if (last) {
        tmp = self->last;
        Py_INCREF(last);
        self->last = last;
        Py_DECREF(tmp);
    }
    return 0;
}

static PyMemberDef Custom_members[] = {
    {"number", T_INT, offsetof(CustomObject, number), 0,
     "custom number"},
    {NULL}  /* Sentinel */
};

static PyObject *
Custom_getfirst(CustomObject *self, void *closure)
{
    Py_INCREF(self->first);
    return self->first;
}

static int
Custom_setfirst(CustomObject *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the first attribute");
        return -1;
    }
    if (!PyUnicode_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The first attribute value must be a string");
        return -1;
    }
    Py_INCREF(value);
    Py_CLEAR(self->first);
    self->first = value;
    return 0;
}

static PyObject *
Custom_getlast(CustomObject *self, void *closure)
{
    Py_INCREF(self->last);
    return self->last;
}

static int
Custom_setlast(CustomObject *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
        return -1;
    }
    if (!PyUnicode_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The last attribute value must be a string");
        return -1;
    }
    Py_INCREF(value);
    Py_CLEAR(self->last);
    self->last = value;
    return 0;
}

static PyObject *
Custom_name(CustomObject *self, PyObject *Py_UNUSED(ignored));

static PyGetSetDef Custom_getsetters[] = {
    {"first", (getter) Custom_getfirst, (setter) Custom_setfirst,
     "first name", NULL},
    {"last", (getter) Custom_getlast, (setter) Custom_setlast,
     "last name", NULL},
    {NULL}  /* Sentinel */
};

static PyMethodDef Custom_methods[] = {
    {"name", (PyCFunction) Custom_name, METH_NOARGS,
     "Return the name, combining the first and last name"
    },
    {NULL}  /* Sentinel */
};

//static
 PyTypeObject CustomType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "custom4.Custom",
    .tp_doc = "Custom objects",
    .tp_basicsize = sizeof(CustomObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC,
    .tp_new = Custom_new,
    .tp_init = (initproc) Custom_init,
    .tp_dealloc = (destructor) Custom_dealloc,
    .tp_traverse = (traverseproc) Custom_traverse,
    .tp_clear = (inquiry) Custom_clear,
    .tp_members = Custom_members,
    .tp_methods = Custom_methods,
    .tp_getset = Custom_getsetters,
};

static PyObject *
Custom_name(CustomObject *self, PyObject *Py_UNUSED(ignored))
{
    LOGF();

    return PyUnicode_FromFormat("%S %S", self->first, self->last);
/*
auto pp = PyObject_New(CustomObject, &CustomType);
//pp->first = NULL;
//pp->last = NULL;
pp->number = 100;

return (PyObject*) pp;
*/
}


static PyObject *
keywdarg_parrot(PyObject *self, PyObject *args, PyObject *keywds)
{
    //LOGF();

    int voltage;
    const char *state = "a stiff";
    const char *action = "voom";
    const char *type = "Norwegian Blue";

    PyObject *obj = nullptr;
    static const char *kwlist[] = {"voltage", "state", "action", "type", "object", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i|sssO!", (char **) kwlist,
                                    &voltage, &state, &action, &type, &PyDict_Type, &obj))
                                     //&voltage, &state, &action, &type, &PyTuple_Type, &obj))
                                     //&voltage, &state, &action, &type, &PyList_Type, &obj))
        return NULL;

int w;

/*
PyObject *pTuple;
PyObject* pItem;
if (!PyArg_ParseTuple(args, "O!", &PyTuple_Type, &pTuple)) {
    PyErr_SetString(PyExc_TypeError, "parameter must be a tuple.");
    return NULL;
}

Py_ssize_t n;
int i;
n = PyTuple_Size(obj);
COUT << n << ENDL;

for (i=0; i<n; i++) {
    pItem = PyTuple_GetItem(obj, i);
    if(!PyLong_Check(pItem)) {
        PyErr_SetString(PyExc_TypeError, "list items must be integers.");
        return NULL;
    }

    w = PyLong_AsLong(pItem);
    COUT << w << ENDL;
}*/

/*
PyObject *pList;
PyObject *pItem;

if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &pList)) {
    PyErr_SetString(PyExc_TypeError, "parameter must be a list.");
    return NULL;
}

Py_ssize_t n;
int i;
n = PyList_Size(pList);
for (i=0; i<n; i++) {
    pItem = PyList_GetItem(pList, i);
    if(!PyInt_Check(pItem)) {
        PyErr_SetString(PyExc_TypeError, "list items must be integers.");
        return NULL;
    }
} 
*/       

/*
PyObject *obj;

if (!PyArg_ParseTuple(args, "O", &obj)) {
  // error
}

PyObject *iter = PyObject_GetIter(obj);
if (!iter) {
  // error not iterator
}

while (true) {
  PyObject *next = PyIter_Next(iter);
  if (!next) {
    // nothing left in the iterator
    break;
  }

  if (!PyFloat_Check(next)) {
    // error, we were expecting a floating point value
  }

  double foo = PyFloat_AsDouble(next);
  // do something with foo
}*/

/*
    PyObject *iter = PyObject_GetIter(obj);
    if (!iter) {
        // error not iterator
    }

    while (true) {
        PyObject *next = PyIter_Next(iter);
        if (!next) {
            // nothing left in the iterator
            break;
        }

        if (!PyFloat_Check(next)) {
            // error, we were expecting a floating point value
        }

        double ww = PyFloat_AsDouble(next);
        // do something with foo
COUT << ww << ENDL;

        //w = PyLong_AsLong(next);
        //COUT << w << ENDL;
    }
*/

/*
 unsigned int k1 = 42;
   PyObject *py_k1 = PyLong_FromUnsignedLong(k1);
   PyObject *py_v1 = PyDict_GetItem(large_dict, py_k1);
   unsigned int v1 = PyLong_AsUnsignedLong(py_v1);
*/

/*
PyObject *key, *value;
Py_ssize_t pos = 0;

while (PyDict_Next(self->dict, &pos, &key, &value)) {
    long i = PyLong_AsLong(value);
    if (i == -1 && PyErr_Occurred()) {
        return -1;
    }
    PyObject *o = PyLong_FromLong(i + 1);
    if (o == NULL)
        return -1;
    if (PyDict_SetItem(self->dict, key, o) < 0) {
        Py_DECREF(o);
        return -1;
    }
    Py_DECREF(o);
}
*/

if (obj != nullptr && PyDict_Check(obj))
{
    LOGF();

    PyObject *key, *value;
    Py_ssize_t pos = 0;

    while (PyDict_Next(obj, &pos, &key, &value)) {
        long i = PyLong_AsLong(value);
        if (i == -1 && PyErr_Occurred()) {
            //return -1;
        }

    //    Py_ssize_t len = PyUnicode_GET_LENGTH(key);

        switch (PyUnicode_KIND(key))
        {
        case PyUnicode_1BYTE_KIND:
            COUT << "pos: " << pos << " k: " << i << " v:1b " << PyUnicode_1BYTE_DATA(key) << ENDL;
            break;

        case PyUnicode_2BYTE_KIND:
            COUT << "pos: " << pos << " k: "  << i << " v:2b " << PyUnicode_2BYTE_DATA(key) << ENDL;
            break;
        case PyUnicode_4BYTE_KIND:
            COUT << "pos: " << pos << " k: "  << i << " v:4b " << PyUnicode_4BYTE_DATA(key) << ENDL;
            break;
        }
    }
}

   // printf("-- This parrot wouldn't ##%s## if you put ##%i## Volts through it.\n",
     //      action, voltage);
    //printf("-- Lovely plumage, the ##%s## -- It's ##%s##!\n", type, state);

    Py_RETURN_NONE;
}

static PyMethodDef keywdarg_methods[] = {
    /* The cast of the function is necessary since PyCFunction values
     * only take two PyObject* parameters, and keywdarg_parrot() takes
     * three.
     */
    {"parrot", (PyCFunction)(void(*)(void))keywdarg_parrot, METH_VARARGS | METH_KEYWORDS,
     "Print a lovely skit to standard output."},
    {NULL, NULL, 0, NULL}   /* sentinel */
};

static PyModuleDef custommodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "component",
    .m_doc = "Example module that creates an extension type.",
    .m_size = -1,
    keywdarg_methods
};

PyMODINIT_FUNC
PyInit_component(void)
{
    PyObject *m;
    if (PyType_Ready(&CustomType) < 0)
        return NULL;

    m = PyModule_Create(&custommodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&CustomType);
    if (PyModule_AddObject(m, "new", (PyObject *) &CustomType) < 0) {
        Py_DECREF(&CustomType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}