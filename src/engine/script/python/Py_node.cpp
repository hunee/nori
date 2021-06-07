/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#include "core/node.h"

#include "Py_node.h"
#include "Py_ext.h"

#include "structmember.h"

class python_node {
public:
	virtual ~python_node() { /*__FUNC_YEL__*/ }

    PyObject* module_ = nullptr;

public:    
    void _began() {}
    void _end() {}

public:
    void _tick(double dt)
	{
	}

	void _draw() 
    {
        return;

        ///__method__

        PyObject *pFunc, *pValue, *presult;

        pFunc = PyObject_GetAttrString(module_, "draw");
        if (PyCallable_Check(pFunc))
        {
            pValue=NULL;//Py_BuildValue("(z)", "ls -l");
            //PyErr_Print();
            //printf("Application.ActiveTexture!\n");
            presult=PyObject_CallObject(pFunc,pValue);
            //PyErr_Print();
        } else
        {
            PyErr_Print();
        }
        //Py_DECREF(pValue);
    
        // Clean up
        Py_DECREF(module_);
    }
};


static int
Py_node_traverse(Py_node_object *self, visitproc visit, void *arg)
{
    //__function__

    Py_VISIT(self->node_ptr);
    Py_VISIT(self->owner);
    Py_VISIT(self->name);

    return 0;
}

static int
Py_node_clear(Py_node_object *self)
{
    //__function__

    Py_CLEAR(self->node_ptr);
    Py_CLEAR(self->owner);
    Py_CLEAR(self->name);
    return 0;
}

static void
Py_node_dealloc(Py_node_object *self)
{
    //__function__

    PyObject_GC_UnTrack(self);
    Py_node_clear(self);

    /* Clear weakrefs first before calling any destructors */
    if (self->weakreflist != NULL)
        PyObject_ClearWeakRefs((PyObject *) self);
    
    /* ... remainder of destruction code omitted for brevity ... */
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *
Py_node_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    //__function__

    Py_node_object *self;
    self = (Py_node_object *) type->tp_alloc(type, 0);
    if (self != nullptr) 
    {
        self->node_ptr = Py_new<GL::node<python_node>>();
        if (self->node_ptr == nullptr) {
            Py_DECREF(self);
            return nullptr;
        }

        auto node_ptr = Py_get<GL::node<python_node>>(self->node_ptr);
        node_ptr->module_ = (PyObject*) self;

        self->name = PyUnicode_FromString("");
        if (self->name == nullptr) {
            Py_DECREF(self);
            return nullptr;
        }

        self->number = 0;
    }
    return (PyObject *) self;
}

static int
Py_node_init(Py_node_object *self, PyObject *args, PyObject *kwds)
{
//    __function__

/*{
    auto node_ptr = Py_get<GL::dummy_node>(self->node_ptr);
    COUT << "- name: " << node_ptr->name_ << ", type: " << (node_ptr ? __typeid_name(*node_ptr):"nullptr") << ", ref_count: " << Py_REFCNT(self) << ENDL;
}*/

    static const char *kwlist[] = {"name", "parent", NULL};
    const char* name = nullptr;

    PyObject *object = NULL, *tmp;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|sO!", (char **) kwlist,
                                     &name, &Py_node_type, &object))
        return -1;
    
    if (name) {
        auto node_ptr = Py_get<GL::node<python_node>>(self->node_ptr);
        node_ptr->name_ = name;

        COUT << "name: " << node_ptr->name_ << ENDL;
    }

    if (object) {
{        
        auto no = (Py_node_object*) object;
        auto node_ptr = Py_get<GL::dummy_node>(no->node_ptr);
        COUT << "object name: " << node_ptr->name_ << ", ref_count: " << Py_REFCNT(object) << ENDL;
}

        self->owner = PyWeakref_NewRef(object, NULL);
    }

    return 0;
}

static PyMemberDef Py_node_members[] = {
    {"number", T_INT, offsetof(Py_node_object, number), 0,
     "custom number"},
    {NULL}  /* Sentinel */
};

static PyObject *
Py_node_getowner(Py_node_object *self, void *closure)
{
//    __function__
/*{
    auto node_ptr = Py_get<GL::dummy_node>(self->node_ptr);
    COUT << "- name: " << node_ptr->name_ << ", type: " << (node_ptr ? __typeid_name(*node_ptr):"nullptr") << ", ref_count: " << Py_REFCNT(self) << ENDL;
}*/

    auto owner = PyWeakref_GetObject(self->owner);
    Py_INCREF(owner);

    //COUT << "parent weakref Py_REFCNT: " << Py_REFCNT(parent) << ENDL;

/*{
    auto no = (Py_node_object*) parent;
    auto node_ptr = Py_get<GL::dummy_node>(no->node_ptr);
    COUT << "parent name: " << node_ptr->name_ << ENDL;
}*/

    return owner;
}

static int
Py_node_setowner(Py_node_object *self, PyObject *value, void *closure)
{
    ///__function__

    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the first attribute");
        return -1;
    }

    Py_CLEAR(self->owner);

    self->owner = PyWeakref_NewRef(value, NULL);

    return 0;
}

static PyObject *
Py_node_getname(Py_node_object *self, void *closure)
{
    __function__

    Py_INCREF(self->name);
    return self->name;
}

static int
Py_node_setname(Py_node_object *self, PyObject *value, void *closure)
{
    __function__

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
    Py_CLEAR(self->name);
    self->name = value;
    return 0;
}

static PyGetSetDef Py_node_getsetters[] = {
    {"owner", (getter) Py_node_getowner, (setter) Py_node_setowner,
     "first name", NULL},
    {"name", (getter) Py_node_getname, (setter) Py_node_setname,
     "last name", NULL},
    {NULL}  /* Sentinel */
};

static PyObject *
Py_node_draw(Py_node_object *self, PyObject *Py_UNUSED(ignored))
{
    //__function__
    //COUT << "- Py_REFCNT: " << Py_REFCNT(self) << ENDL;

/*{
    auto node_ptr = Py_get<GL::dummy_node>(self->node_ptr);
    COUT << "- name: " << node_ptr->name_ << " type: " << (node_ptr ? __typeid_name(*node_ptr):"nullptr") << ENDL;
}*/
/*
    if (self->parent) 
    {
        auto parent = PyWeakref_GetObject(self->parent);
        if (parent != Py_None)
        {
            auto no = (Py_node_object*) parent;
            auto node_ptr = Py_get<GL::dummy_node>(no->node_ptr);
            COUT << "parent name: " << node_ptr->name_ << ", ref_count: " << Py_REFCNT(parent) << ENDL;
        }
    }
*/
    Py_RETURN_NONE;
}

static PyObject *
Py_node_dump(Py_node_object *self, PyObject *Py_UNUSED(ignored))
{
   __function__
{
    auto node_ptr = Py_get<GL::dummy_node>(self->node_ptr);
    COUT << "- name: " << node_ptr->name_ << ", type: " << (node_ptr ? __typeid_name(*node_ptr):"nullptr") << ", ref_count: " << Py_REFCNT(self) << ENDL;

    node_ptr->dump();    
}

    Py_RETURN_NONE;
}

void Py_node_add_object(PyObject *self, PyObject *object)
{
    //__function__

    ///
    auto node = reinterpret_cast<Py_node_object*> (object);
    auto node_ptr = Py_get<GL::dummy_node>(node->node_ptr);
    //COUT << "object name: " << node_ptr->name_ << "type: " << (node_ptr ? __typeid_name(*node_ptr):"nullptr") << ENDL;

    ///
    auto self_node = reinterpret_cast<Py_node_object*> (self);
    auto self_node_ptr = Py_get<GL::node_>(self_node->node_ptr);

    ///
    auto shared_ptr = std::make_shared<GL::node_>();
    shared_ptr.reset(node_ptr);

    self_node_ptr->add(node_ptr->name_, shared_ptr);

    PyCapsule_SetDestructor(node->node_ptr, [](PyObject* p) {});
}

static PyObject *
Py_node_add(PyObject *self, PyObject *args, PyObject *keywds)
{
/*    __function__
{
    auto so = reinterpret_cast<Py_node_object*> (self);
    auto node_ptr = Py_get<GL::dummy_node>(so->node_ptr);
    COUT << "- name: " << node_ptr->name_ << ", type: " << (node_ptr ? __typeid_name(*node_ptr):"nullptr") << ", ref_count: " << Py_REFCNT(self) << ENDL;
}*/

    static const char *kwlist[] = {"node", NULL};

    PyObject *object = NULL, *tmp;
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O!", (char **) kwlist, 
        &Py_node_type, &object))
    {
        PyErr_SetString(PyExc_TypeError, "parameter must be a node.");
        return NULL;
    }

    if (object) 
    {
        //COUT << "node - Py_REFCNT: " << Py_REFCNT(object) << ENDL;

        Py_node_add_object(self, object);

        //Py_INCREF(object);
        //Py_CLEAR(self_node->root);
        //self_node->root = object;
    }

    Py_RETURN_NONE;
}

void Py_node_erase_object(PyObject *self, PyObject *object)
{
    //__function__

    ///
    auto node = reinterpret_cast<Py_node_object*> (object);
    auto node_ptr = Py_get<GL::dummy_node>(node->node_ptr);
    //COUT << "object name: " << node_ptr->name_ << " type: " << (node_ptr ? __typeid_name(node_ptr):"nullptr") << ENDL;

    ///
    auto self_node = reinterpret_cast<Py_node_object*> (self);
    auto self_node_ptr = Py_get<GL::node_>(self_node->node_ptr);

    self_node_ptr->erase(node_ptr->name_);
}


static PyObject *
Py_node_erase(PyObject *self, PyObject *args, PyObject *keywds)
{
/*    __function__

{
    auto so = reinterpret_cast<Py_node_object*> (self);
    auto node_ptr = Py_get<GL::dummy_node>(so->node_ptr);
    COUT << "- name: " << node_ptr->name_ << ", type: " << (node_ptr ? __typeid_name(*node_ptr):"nullptr") << ", ref_count: " << Py_REFCNT(self) << ENDL;
}*/

    static const char *kwlist[] = {"node", NULL};

    PyObject *object = NULL, *tmp;
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O!", (char **) kwlist, 
        &Py_node_type, &object))
    {
        PyErr_SetString(PyExc_TypeError, "parameter must be a node.");
        return NULL;
    }

    if (object) 
    {
        //COUT << "node - Py_REFCNT: " << Py_REFCNT(object) << ENDL;

        Py_node_erase_object(self, object);

        //Py_INCREF(object);
        //Py_CLEAR(self_node->root);
        //self_node->root = object;
    }

    Py_RETURN_NONE;
}

static PyMethodDef Py_node_methods[] = {
    {"draw", (PyCFunction) Py_node_draw, METH_NOARGS,
     "Return the name, combining the first and last name"
    },
    {"dump", (PyCFunction) Py_node_dump, METH_NOARGS,
     "Return the name, combining the first and last name"
    },
    {"add", (PyCFunction) Py_node_add, METH_VARARGS | METH_KEYWORDS,
     "Return the name, combining the first and last name"
    },
    {"erase", (PyCFunction) Py_node_erase, METH_VARARGS | METH_KEYWORDS,
     "Return the name, combining the first and last name"
    },
    {NULL}  /* Sentinel */
};

PyTypeObject Py_node_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "custom4.Custom",
    .tp_doc = "Custom objects",
    .tp_basicsize = sizeof(Py_node_object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC,
    .tp_new = Py_node_new,
    .tp_init = (initproc) Py_node_init,
    .tp_dealloc = (destructor) Py_node_dealloc,
    .tp_traverse = (traverseproc) Py_node_traverse,
    .tp_clear = (inquiry) Py_node_clear,
    .tp_members = Py_node_members,
    .tp_methods = Py_node_methods,
    .tp_getset = Py_node_getsetters,
    .tp_weaklistoffset = offsetof(Py_node_object, weakreflist),
};


static PyObject *
keywdarg_parrot(PyObject *self, PyObject *args, PyObject *keywds)
{
    __function__

    int voltage;
    const char *state = "a stiff";
    const char *action = "voom";
    const char *type = "Norwegian Blue";

    static const char *kwlist[] = {"voltage", "state", "action", "type", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i|sss", (char **) kwlist,
                                     &voltage, &state, &action, &type))
        return NULL;

    printf("-- This parrot wouldn't %s if you put %i Volts through it.\n",
           action, voltage);
    printf("-- Lovely plumage, the %s -- It's %s!\n", type, state);

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

static PyModuleDef Py_node_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "component",
    .m_doc = "Example module that creates an extension type.",
    .m_size = -1,
    keywdarg_methods
};

PyMODINIT_FUNC
PyInit_node(void)
{
    PyObject *m;
    if (PyType_Ready(&Py_node_type) < 0)
        return NULL;

    m = PyModule_Create(&Py_node_module);
    if (m == NULL)
        return NULL;

    Py_INCREF(&Py_node_type);
    if (PyModule_AddObject(m, "node", (PyObject *) &Py_node_type) < 0) {
        Py_DECREF(&Py_node_type);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}