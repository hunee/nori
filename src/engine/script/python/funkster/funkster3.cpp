/*
 * This is an example of how one could hold a templated
 * class with a polymorphic base polymorphically in python.
 *
 * THIS IS A VERY BAD IMPLEMENTATION THAT DOES NO ERROR
 * CHECKING AND WOULD CAUSE PYTHON TO CRASH IF A USER DID
 * SOME PRETTY BENIGN THINGS... YOU HAVE BEEN WARNED.
 */

#include <Python.h>

enum IDS { ZERO, ONE, TWO, THREE };

struct MyBase {
    virtual ~MyBase(void) {}
    virtual long get(void) const = 0;
    virtual MyBase* clone(void) const = 0;
};

template<int ID>
struct MyClass : MyBase {
    enum { value=ID };
    MyClass(void) {}
    virtual long get(void) const { return ID; }
    virtual MyClass* clone(void) const { return new MyClass(); }
private:
    MyClass(MyClass const& other);
    MyClass& operator=(MyClass const& rhs);
};

static void* makeBase(int id) {
    // note that we could have put the global scope static functions into
    // instance methods that looked similar to this in funkster2.cpp.
    switch(static_cast<IDS>(id)) {
        case ZERO:
            return static_cast<void*>(new MyClass<ZERO>());
        case ONE:
            return static_cast<void*>(new MyClass<ONE>());
        case TWO:
            return static_cast<void*>(new MyClass<TWO>());
        case THREE:
            return static_cast<void*>(new MyClass<THREE>());
        default:
            // raise an error here.
            break;
    }
}

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
 
    void destroy_funkster(PyObject* funkster) {
        delete static_cast<MyBase*>(PyCapsule_GetPointer(funkster, "val"));
    }

    static PyObject* make_funkster(PyObject *self, PyObject *args) {
        PyObject* idp;
        PyArg_UnpackTuple(args, "funk", 1, 1, &idp);
        return PyCapsule_New(makeBase(PyInt_AsLong(idp)), "val", destroy_funkster);
    }

    static PyObject* get_funkster_val(PyObject *self, PyObject *args) {
        PyObject* pf = NULL;
        if(!PyArg_UnpackTuple(args, "funk", 1, 1, &pf)) return NULL;
        MyBase* b = (MyBase*)PyCapsule_GetPointer(pf, "val");
        return PyLong_FromLong(b->get());
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
