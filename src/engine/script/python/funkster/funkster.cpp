#include <Python.h>

struct MyClass {
    int val;
    MyClass(void) : val(42) {}
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

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

    static PyMethodDef FunksterMethods[] = {
        {"make_funkster", make_funkster, METH_NOARGS, "Make a Funkster."},
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
