/*
 * This is an example of how one could hold a templated
 * class with a polymorphic base polymorphically in python.
 *
 * While it is slightly more verbose, I prefer this to
 * the one in funkster3.cpp as this is more straight
 * forward to wrap using Boost.Python... or at least it
 * appears to be to a Boost.Python newbie like me!
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

static MyBase* makeBase(int id) {
    switch(static_cast<IDS>(id)) {
        case ZERO:
            return static_cast<MyBase*>(new MyClass<ZERO>());
        case ONE:
            return static_cast<MyBase*>(new MyClass<ONE>());
        case TWO:
            return static_cast<MyBase*>(new MyClass<TWO>());
        case THREE:
            return static_cast<MyBase*>(new MyClass<THREE>());
        default:
            // raise an error here.
            break;
    }
}

struct Wrapper {
    Wrapper(long id)
        : instance_(makeBase(id)) {
    }

    Wrapper(Wrapper const& other)
        : instance_(other.instance_->clone()) {
    }

    Wrapper& operator=(Wrapper const& rhs) {
        delete instance_;
        instance_ = rhs.instance_->clone();
    }

    ~Wrapper(void) {
        delete instance_;
    }

    long get(void) {
        return instance_->get();
    }

private:
    MyBase*
        instance_;
};  

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
 
    void destroy_funkster(PyObject* funkster) {
        delete static_cast<Wrapper*>(PyCapsule_GetPointer(funkster, "val"));
    }

    static PyObject* make_funkster(PyObject *self, PyObject *args) {
        PyObject* idp;
        PyArg_UnpackTuple(args, "funk", 1, 1, &idp);
        return PyCapsule_New(new Wrapper(PyInt_AsLong(idp)), "val", destroy_funkster);
    }

    static PyObject* get_funkster_val(PyObject *self, PyObject *args) {
        PyObject* pf = NULL;
        if(!PyArg_UnpackTuple(args, "funk", 1, 1, &pf)) return NULL;
        Wrapper* w = (Wrapper*)PyCapsule_GetPointer(pf, "val");
        return PyLong_FromLong(w->get());
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
