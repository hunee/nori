/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once


/**
 * @brief 
 * 
 * @tparam T 
 * @return PyObject* 
 */
template <typename T>
inline PyObject* Py_new() 
{ 
    return PyCapsule_New((void *) new T, "", [](PyObject* p) 
        { 
            __function__
            delete static_cast<T*> (PyCapsule_GetPointer(p, "")); 
        }
    );
}

template <typename T>
inline PyObject* Py_new2(const std::string& name) 
{ 
    return PyCapsule_New((void *) new T(name), "", [](PyObject* p) 
        {
            __function__ 
            delete static_cast<T*> (PyCapsule_GetPointer(p, ""));
        }
    );
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param p 
 * @return PyObject* 
 */
inline PyObject* Py_ptr(void *p) 
{ 
    return PyCapsule_New(p, "", NULL);
}



/**
 * @brief 
 * 
 * @tparam T 
 * @param p 
 * @return T* 
 */
template <typename T>
inline T* Py_get(PyObject *p) 
{ 
    return static_cast<T*> (PyCapsule_GetPointer(p, ""));
}

//int PyCapsule_CheckExact(PyObject *p);



/*
auto pp = PyObject_New(CustomObject, &CustomType);
pp->first = NULL;
pp->last = NULL;
pp->number = 100;

return (PyObject*) pp;

*/


/**
 * @brief 
 * 
 */
#define Py_DICT_SETITEMSTRING(d, n, s) \
    { PyObject *v = PyUnicode_FromString(s); PyDict_SetItemString(d, n, v); Py_DECREF(v); }


extern void PyDict_SetVerstionString(PyObject * m, const char * version);