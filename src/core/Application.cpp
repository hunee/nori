/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#include "asset/asset_manager.h"

#include "renderer/texture.h"
#include "renderer/shader.h"

#include "renderer/camera.h"

#include "Application.h"

#include "asset/ext/png.h"
#include "asset/ext/targa.h"

#include "asset/ext/stb.h"

#include "asset/ext/bmf.h"
#include "asset/ext/ftf.h"

#include "asset/ext/xml.h"
#include "asset/ext/xml_shader_parser.h"

#include "asset/ext/fbx.h"

#include "asset/ext/lua.h"

#include "editor/frame_view.h"

///
#include "script/python/Py_Application.h"
#include "script/python/Py_GL.h"
#include "script/python/Py_component.h"
#include "script/python/Py_node.h"

////
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


// GLFW/deps
//#include "linmath.h"

//namespace GL {

/**
 * @brief 
 * 
 */
Application* theApp = Application::get();


int Application::init_lua()
{
   return 0;
}

/**
 * initPython
 * 
 */
#include "structmember.h"

int Application::init_python()
{
    COUT << "- python version: " << PY_MAJOR_VERSION << "." << PY_MINOR_VERSION << "." << PY_MICRO_VERSION << ENDL;
    
    /*
    //main(int argc, char *argv[])
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }*/

    // Set PYTHONPATH TO working directory
    setenv("PYTHONPATH", ".", 1);
    
    const char* python_path = getenv("PYTHONPATH");
    
    //std::cout << KRED << "->> type_info: name: " << this->name() << " id: " << this->id() << pythonPath << RST << std::endl;
    COUT << KGRN << "- PYTHONPATH: " << python_path << ENDL;

    /* Add a built-in module, before Py_Initialize */

    ///
    if (PyImport_AppendInittab("component", PyInit_component) == -1) {
        fprintf(stderr, "Error: could not extend in-built modules table\n");
        exit(1);
    }

    ///
    if (PyImport_AppendInittab("node", PyInit_node) == -1) {
        fprintf(stderr, "Error: could not extend in-built modules table\n");
        exit(1);
    }

    ///
    if (PyImport_AppendInittab("GL", PyInit_GL) == -1) {
        fprintf(stderr, "Error: could not extend in-built modules table\n");
        exit(1);
    }

    if (PyImport_AppendInittab("Application", PyInit_Application) == -1) {
        fprintf(stderr, "Error: could not extend in-built modules table\n");
        exit(1);
    }

    /* Pass argv[0] to the Python interpreter */
    ///Py_SetProgramName(program);
    //PyMem_RawFree(program);

    /* Initialize the Python interpreter.  Required.
       If this step fails, it will be a fatal error. */
    Py_Initialize();

    return 1;
}

class Py_node {
public:
    void draw() {}
};

void Py_node(const char* name)
{
    __function__

    PyObject* module = PyImport_ImportModule(name);
    
    PyObject* clazz = PyObject_GetAttrString(module, name);

    //tp_new, tp_alloc
    PyObject* pValue=Py_BuildValue("(s)", "name");
    PyObject *instance = PyObject_CallObject(clazz, pValue);
    PyErr_Print();

    //draw
    if (instance) {
        PyObject *returnSum = PyObject_CallMethod(instance, "draw", NULL);
    }
}


/**
 * @brief 
 * 
 * @return int 
 */
int Application::run_script()
{
    //__method__

#if 1
    ///Py_node("frame_rect");
    ///return 1;
        
    /* Optionally import the module; alternatively,
       import can be deferred until the embedded script
       imports it. */
    auto module = PyImport_ImportModule("bootstrap");
    if (!module) {
        PyErr_Print();
        fprintf(stderr, "Error: could not import module 'bootstrap'\n");
    }
COUT << "--------------------------" << ENDL;
/*
    const char * filename = "bootstrap.py";
    
    char pathname[PATH_MAX];
    sprintf(pathname, "%s/%s", _dataPath, filename);
    
    COUT << "pathname: " << pathname << ENDL;

    ///
    FILE* fp = _Py_fopen(pathname, "r");
    if (fp)
    {
        PyRun_SimpleFile(fp, pathname);
    
    
        ///
        ///PyApplication_runLoop(123);
    }*/
#else
    /// 1
    {
        // evaluate some code
        PyRun_SimpleString("import sys\n");
        
        //ignore line wrap on following line
        PyRun_SimpleString("sys.stdout.write('Hello from an embedded Python Script\\n')\n");
    }

    /// 2
    {
        // Build the name object
        PyObject *pName, *pModule, *pFunc, *pValue, *presult;
        pName = PyUnicode_FromString("Application");
        
        // Load the module object
        pModule = PyImport_Import(pName);
        
        pFunc = PyObject_GetAttrString(pModule, "ActiveTexture");
        if (PyCallable_Check(pFunc))
        {
            pValue=Py_BuildValue("(z)", "ls -l");
            PyErr_Print();
            printf("Application.ActiveTexture!\n");
            presult=PyObject_CallObject(pFunc,pValue);
            PyErr_Print();
        } else
        {
            PyErr_Print();
        }
    }
    //printf("Result is %d\n",PyInt_AsLong(presult));
    //    Py_DECREF(pValue);
    
    // Clean up
    //    Py_DECREF(pModule);
    //    Py_DECREF(pName);
    
    /// 3
    {
        PyRun_SimpleString("import Application\n");
        //PyRun_SimpleString("status = gl.ActiveTexture(\"ls -l\")");
        PyRun_SimpleString("def runLoop(n):\n\tprint('PYTHON> def runLoop()', n)\n");
        PyRun_SimpleString("status = Application.set_runLoop(runLoop)");
        PyRun_SimpleString("status = runLoop(456)");
        PyRun_SimpleString("status = Application.runLoop(789)");
        PyRun_SimpleString("path = Application.path");
        PyRun_SimpleString("print('path: ', path)\n");
        
        PyRun_SimpleString("path = Application.dataPath");
        PyRun_SimpleString("print('dataPath: ', path)\n");

        PyRun_SimpleString("path = Application.persistentDataPath");
        PyRun_SimpleString("print('persistentDataPath: ', path)\n");

        PyRun_SimpleString("version = Application.version");
        PyRun_SimpleString("print('version: ', version)\n");
    }

    PyApplication_runLoop(123);
    
#define PP_CHECK 1
#if !defined(PP_CHECK)
    /// 4
    {
        int arg;
        PyObject *arglist;
        PyObject *result;
        arg = 123;
        
        /* Time to call the callback */
        arglist = Py_BuildValue("(i)", arg);
        result = PyObject_CallObject(PY_gl_runLoop, arglist);
        Py_DECREF(arglist);
    }
    
    ///
    {
        
        // Build the name object
        PY_object pName, pFunc, pValue, presult;
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

    /*
    PyObject* pModule =PyImport_ImportModule("python");
           PyObject* pDict = PyModule_GetDict(pModule);
           PyObject* pClassHelloPython = PyDict_GetItemString(pDict, "Person");
           PyObject* pInstanceHelloPython = PyInstance_New(pClassHelloPython, NULL, NULL);

           PyObject_CallMethod(pInstanceHelloPython, "sayHi", NULL);
           worldObjectPtr->greet();
           PyObject_CallMethod(pInstanceHelloPython, "greetReset", "O", worldObjectPtr);
           worldObjectPtr->greet();
       }
    */
#endif

#endif

  return 1;
}


/**
 * @brief 
 * 
 * @return int 
 */
int Application::init_GL()
{
//
  check_GLextensions();


///
  glClearColor(0.2f, 0.2f, 0.4f, 1.0f);

  return 1;

}

int Application::init_asset_manager()
{
 //   CLOG();
    auto importer = asset_importer::get();

    {
#ifdef USE_STB        
    auto stb = std::make_shared<asset_ext<ext::stb>>();
    (*importer)["jpg"] = stb;

    (*importer)["bmp"] = stb;
    (*importer)["psd"] = stb;

    (*importer)["gif"] = stb;
    (*importer)["hdr"] = stb;
    (*importer)["pic"] = stb;
    (*importer)["pnm"] = stb;

    (*importer)["png"] = stb;
    (*importer)["tga"] = stb;

#else
    (*importer)["png"] = std::make_shared<asset_ext<ext::png>>();
    (*importer)["tga"] = std::make_shared<asset_ext<ext::targa>>();
#endif

    (*importer)["ttf"] = std::make_shared<asset_ext<ext::ftf>>();
    (*importer)["bmf"] = std::make_shared<asset_ext<ext::bmf>>();

#ifdef USE_FBXSDK
    (*importer)["fbx"] = std::make_shared<asset_ext<ext::fbx>>();
#endif

    }

    /////
    auto xml = std::make_shared<asset_ext<ext::xml>>();
    (*xml)["shader"] = std::make_unique<ext::xml_parser<ext::xml_shader_parser>>();
    //(*importer).dump();

    (*importer)["xml"] = xml;
    (*importer)["lua"] = std::make_shared<asset_ext<ext::lua_shader>>();

///    importer->dump();

    ///
    asset_manager::get()->init();

    return 1;
}


/**
 * @brief 
 * 
 * @return int 
 */


int Application::init()
{
///  __method__

  init_GL();

  init_asset_manager();

  //root_ = std::make_unique<GL::node<GL::dummy> >("dummy");
//root_ = std::make_shared<GL::dummy_node>("dummy");
root_ = std::make_shared<GL::node<GL::object> >("root");

{
    ///std::shared_ptr<GL::component<GL::camera>> cc_;	
    auto cc_ = std::make_shared<GL::component<GL::camera> >("cc");
    cc_->ortho();

    auto p = std::dynamic_pointer_cast<GL::object>(root_);
    p->add("cc", cc_);
}

auto fi = std::make_shared<GL::node<GL::frame_view> >("frame_view", root_)->add();
fi->_began();

  init_python();
  init_lua();

//

  run_script();

//__method__
asset_manager::get()->dump();

//root_->dump();

  return 1;
}


/**
 * @brief 
 * 
 * @return BOOL 
 */
int Application::runLoop()
{
    //__method__

	/**
	 * fps
	 */
/*    
	double time, dt;
	static double last_frametime, last_animtime;
	
	static bool first_call = true;
	if (first_call)
	{
		last_frametime = last_animtime = glfwGetTime();
		first_call = false;
	}
	
	time = glfwGetTime();
	if (time > (last_frametime + 1.0))
	{
		frame_rate_ = frame_count_;
		frame_count_ = 0;
		
		last_frametime = time;
	}
	
	dt = time - last_animtime;
	if (dt > 0.1f) dt = 0.1f;

	last_animtime = time;

    frame_count_ ++;
*/
    double time = glfwGetTime();
    static double last_time = time;

	double dt = time - last_time;
	if (dt > 0.1f) dt = 0.1f;

    last_time = time;


    /////
    root_->_tick(dt);
    
    GL::picker::get()->flush();
    
    root_->_draw();

///
    PyApplication_runLoop(dt);
  
    return true;
}

//};//GL