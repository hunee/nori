/*
 * This is an example of how one could hold a templated
 * class polymorphically in python.
 *
 * THIS IS A VERY BAD IMPLEMENTATION THAT DOES NO ERROR
 * CHECKING AND WOULD CAUSE PYTHON TO CRASH IF A USER DID
 * SOME PRETTY BENIGN THINGS... YOU HAVE BEEN WARNED.
 */

#include <Python.h>

enum IDS { ZERO, ONE, TWO, THREE };

template<int ID>
struct MyClass {
    enum { value=ID };
    long get(void) const { return ID; }
};

struct Wrapper; // forward def
static void doDelete(Wrapper*); // forward def

struct Wrapper {
    Wrapper(int id, void* instance) : id(id), instance(instance) {}
    ~Wrapper(void) { doDelete(this); }
    long id;
    void* instance;
};

static void* makeWrapper(long id) {
    switch(static_cast<IDS>(id)) {
        case ZERO:
            return static_cast<void*>(new Wrapper(id, static_cast<void*>(new MyClass<ZERO>())));
        case ONE:
            return static_cast<void*>(new Wrapper(id, static_cast<void*>(new MyClass<ONE>())));
        case TWO:
            return static_cast<void*>(new Wrapper(id, static_cast<void*>(new MyClass<TWO>())));
        case THREE:
            return static_cast<void*>(new Wrapper(id, static_cast<void*>(new MyClass<THREE>())));
    }
};

static long doJobby(Wrapper* wrapper) {
    switch(static_cast<IDS>(wrapper->id)) {
        case ZERO:
            return static_cast<MyClass<ZERO>*>(wrapper->instance)->get();
        case ONE:
            return static_cast<MyClass<ONE>*>(wrapper->instance)->get();
        case TWO:
            return static_cast<MyClass<TWO>*>(wrapper->instance)->get();
        case THREE:
            return static_cast<MyClass<THREE>*>(wrapper->instance)->get();
        default:
            return -1;
    }
}

static void doDelete(Wrapper* wrapper) {
    switch(static_cast<IDS>(wrapper->id)) {
        case ZERO:
            delete static_cast<MyClass<ZERO>*>(wrapper->instance);
            break;
        case ONE:
            delete static_cast<MyClass<ONE>*>(wrapper->instance);
            break;
        case TWO:
            delete static_cast<MyClass<TWO>*>(wrapper->instance);
            break;
        case THREE:
            delete static_cast<MyClass<THREE>*>(wrapper->instance);
            break;
    }
}

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
 
    void destroy_funkster(PyObject* funkster) {
        doDelete((Wrapper*)PyCapsule_GetPointer(funkster, "val"));
    }

    static PyObject* make_funkster(PyObject *self, PyObject *args) {
        PyObject* idp;
        PyArg_UnpackTuple(args, "funk", 1, 1, &idp);
        return PyCapsule_New(makeWrapper(PyInt_AsLong(idp)), "val", destroy_funkster);
    }

    static PyObject* get_funkster_val(PyObject *self, PyObject *args) {
        PyObject* pf = NULL;
        if(!PyArg_UnpackTuple(args, "funk", 1, 1, &pf)) return NULL;
        Wrapper* w = (Wrapper*)PyCapsule_GetPointer(pf, "val");
        return PyLong_FromLong(doJobby(w));
    }

    static PyMethodDef FunksterMethods[] = {
        {"make_funkster", make_funkster, METH_VARARGS, "Make a Funkster."},
        {"get_funkster_val", get_funkster_val, METH_VARARGS, "Get val from Funkster"},
        {NULL, NULL, 0, NULL} /* Sentinel */
    };
 
    PyMODINIT_FUNC initfunkster(void) {
        PyObject *m;
        m = Py_InitModule("funkster", FunksterMethods);
        if (m == NULL) return;
    }
#ifdef __cplusplus
} // end extern "C"
#endif // __cplusplus
