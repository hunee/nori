1. C++ Call Python Function Directly


#include <stdio.h>
#include "Python.h"

int main(void) {
    printf("Hello C++\n");

    Py_Initialize();

    if (Py_IsInitialized()) {
        PyRun_SimpleString("print \'Hello Python\'\n");
        Py_Finalize();
    }else
        printf("Python Not Intialized \n");
    return 0;
}

sudo gcc -o main main.cpp
sudo gcc -o main main.cpp `python-config --includes` `python-config --libs`
$ ./main



2. C++ Call Python Module (argument and Return)
scripts/__init__.py (empty)
scripts/my_def.py

def PrintMyDef():
    print "Hello, MyDef!"
    
def Multiply(x, y):
    return x * y

main2.cpp

#include <Python.h>

void PrintMyDef()
{
  PyObject* mydef = PyImport_ImportModule("scripts.my_def");

  if(mydef) {
    PyObject* printHello = PyObject_GetAttrString(mydef, "PrintMyDef");

    if(printHello) {
      PyObject *r = PyObject_CallFunction(printHello, NULL);

      if (r == Py_None) {
        printf("None is returned.\n");
        Py_XDECREF(r);
      }

      Py_XDECREF(printHello);
    }
    Py_XDECREF(mydef);
  }
}

int Multiply(int x, int y)
{
  PyObject* mydef = PyImport_ImportModule("scripts.my_def");
  int result;

  if(mydef) {
    PyObject* multiply = PyObject_GetAttrString(mydef, "Multiply");

    if(multiply) {
      PyObject *r = PyObject_CallFunction(multiply, "ii", x, y);

      if(r) {
        result = (int)PyInt_AS_LONG(r);
        Py_XDECREF(r);
      }
      Py_XDECREF(multiply);
    }
    Py_XDECREF(mydef);
  }

  return result;
}

void SysPath()
{
  printf("sys.path:");
  PyRun_SimpleString("import sys\nprint sys.path\nprint\n");
}

int main(int argc, char** argv)
{
  Py_SetProgramName(argv[0]);
  Py_Initialize();
  printf("GetProgramName: %s\n\n", Py_GetProgramName());

  if (Py_IsInitialized()) {
    PySys_SetArgv(argc, argv); //error not declared function
    printf("GetPath: %s\n\n", Py_GetPath());
    SysPath();
    PrintMyDef(); // Calling python functions
    printf("%d * %d = %d\n", 10, 15, Multiply(10, 15));
    Py_Finalize();
  }
  return 0;
}

//sudo gcc -o main2 main2.cpp `python-config --includes` `python-config --libs`



3. Python class variable(No C++)
 
import numpy

class MyClass:
    
    model=0
    
    def __init__(self):            
        self.model=numpy.random.rand(2,2)*100
        print "MyClass instantiated"
        print self.model        
    def __del__(self):
        print "MyClass deleted"
    def Sum(self):          
        return numpy.sum(self.model)
    def Avr(self, count):      
        return numpy.sum(self.model)/count
        

instance = MyClass()
print('instance',instance)
print('Sum',instance.Sum())
print('Avr',instance.Avr(2))
del instance
print('program end')

Run

MyClass instantiated
[[ 88.53158827  95.15454941]
 [ 29.93810867  85.32930458]]
('instance', <__main__.MyClass instance at 0x7f21a225d5a8>)
('Sum', 298.95355092849843)
('Avr', 149.47677546424922)
MyClass deleted
program end

 
4. C++ call Python class Module
#include <Python.h>

void myClass() {
    PyObject* mydef = PyImport_ImportModule("scripts.my_def");
    int result;

    if (mydef) {
        PyObject* myClass = PyObject_GetAttrString(mydef, "MyClass");

        if (myClass) {
            /* instance = MyClass() */
            PyObject *instance = PyObject_CallObject(myClass, NULL);

            if (instance) {
                PyObject *returnSum = PyObject_CallMethod(instance, "Sum",
                        NULL);
                if (returnSum) {
                    double result = PyFloat_AS_DOUBLE(returnSum); //find using Search . Type this "PyFloat_"
                    Py_XDECREF (returnSum);
                    printf("sum = %f\n", result);
                }else printf("No Sum Method\n");

                PyObject *returnAvr = PyObject_CallMethod(instance, "Avr","i", 4);
                if (returnAvr) {
                    double result = PyFloat_AS_DOUBLE(returnAvr); //find using Search . Type this "PyFloat_"
                    Py_XDECREF (returnAvr);
                    printf("Avr = %f\n", result);
                }else printf("No Avr Method\n");
            }
        }
    }
}

int main(int argc, char** argv) {
    Py_SetProgramName(argv[0]);
    Py_Initialize();
    printf("GetProgramName: %s\n\n", Py_GetProgramName());

    if (Py_IsInitialized()) {
        PySys_SetArgv(argc, argv);
        printf("GetPath: %s\n\n", Py_GetPath());
        myClass();
        Py_Finalize();
    }
    return 0;
}

$ sudo gcc -o main3 main3.cpp `python-config --includes` `python-config --libs`
 ./man3

Result 

MyClass instantiated
[[ 36.21097826  45.38968704]
 [ 37.77375183  78.62713139]]
sum = 198.001549
Avr = 49.500387
 

 

5. C++ send array to Python, Receive Array From Python
import numpy
import ctypes

class PatchNetwork:
    
    model=0
    
    def __init__(self):            
        self.model=numpy.random.rand(2,2)*255
        print "PatchNetwork instantiated"
        print self.model        
    def __del__(self):
        print "PatchNetwork deleted"
    def Sum(self):          
        return numpy.sum(self.model)
    def Avr(self, count):      
        return numpy.sum(self.model)/count
    def Predict(self, markingPatch):
        print("Predict arg", markingPatch)     
        data = numpy.asarray( markingPatch)
        print("as array", data)
        return data

#include <Python.h>
#include <stdio.h>

typedef unsigned char uchar;

int patchSize = 4;
uchar *targetPatch;


void myClass() {
    PyObject* mydef = PyImport_ImportModule("scripts.my_net");
    int result;

    if (mydef) {
        PyObject* myClass = PyObject_GetAttrString(mydef, "PatchNetwork");

        if (myClass) {
            /* instance = MyClass() */
            PyObject *instance = PyObject_CallObject(myClass, NULL);

            if (instance) {
                PyObject *returnSum = PyObject_CallMethod(instance, "Sum",
                        NULL);
                if (returnSum) {
                    double result = PyFloat_AS_DOUBLE(returnSum); //find using Search . Type this "PyFloat_"
                    Py_XDECREF(returnSum);
                    printf("sum = %f\n", result);
                } else
                    printf("No Sum Method\n");

                // string(s) , integer(i) , float(f)
                // https://docs.python.org/2/c-api/arg.html#c.Py_BuildValue
                PyObject *returnAvr = PyObject_CallMethod(instance, "Avr", "i",
                        4);
                if (returnAvr) {
                    double result = PyFloat_AS_DOUBLE(returnAvr); //find using Search . Type this "PyFloat_"
                    Py_XDECREF(returnAvr);
                    printf("Avr = %f\n", result);
                } else
                    printf("No Avr Method\n");

                printf("\n\n");

                targetPatch = (uchar*) malloc(patchSize * sizeof(uchar));
                for (int i = 0; i < patchSize; i++)
                    targetPatch[i] = i + 10;

                PyObject *nParam = PyTuple_New(patchSize);
                for (long i = 0; i < patchSize; i++) {
                    PyObject *item = PyInt_FromLong(targetPatch[i]);
                    PyTuple_SetItem(nParam, i, item);
                }

                PyObject *returnPredict = PyObject_CallMethod(instance,
                        "Predict", "(O)", nParam);
                if (returnPredict) {

                    int* result = reinterpret_cast<int*>(returnPredict); //find using Search . Type this "PyFloat_"
                    int m_numCols = PyObject_Length(returnPredict);
                    printf("size %d\n", m_numCols);
                    for (int j=0; j<m_numCols; j++) {
                        PyObject *piItem = PySequence_GetItem(returnPredict, j);

                        int isInt=PyInt_Check(piItem);
                        int isIntExact=PyInt_CheckExact(piItem);
                        printf("isInt %d isIntExact %d\n",isInt,isIntExact);

                        double value = PyInt_AsSsize_t(piItem);
                        printf("Predict [%d] %f \n", j, value);
                    }
                    Py_XDECREF(returnPredict);
                } else
                    printf("No Predict Method\n");
            }
        }
    }
}

int main(int argc, char** argv) {
    Py_SetProgramName(argv[0]);
    Py_Initialize();
    printf("GetProgramName: %s\n\n", Py_GetProgramName());

    if (Py_IsInitialized()) {
        PySys_SetArgv(argc, argv);
        printf("GetPath: %s\n\n", Py_GetPath());
        myClass();
        Py_Finalize();
    }
    return 0;
}

//sudo gcc -o main4 main4.cpp `python-config --includes` `python-config --libs`


PyObject* (*fpFunc)(PyObject*,PyObject*) = someFunction;
PyMethodDef methd = {"methd",fpFunc,METH_VARARGS,"A new function"};
PyObject* name = PyString_FromString(methd.ml_name);
PyObject* pyfoo = PyCFunction_NewEx(&methd,NULL,name);
Py_DECREF(name);

