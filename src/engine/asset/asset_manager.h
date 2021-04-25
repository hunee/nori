/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "unique_ptr.h"

/*
auto upw1(std::make_unique<T>()); // make 함수 사용 
std::unique_ptr<T> upw2(new T); // make 함수 비사용 
auto spw1(std::make_shared<T>()); // make 함수 사용 
std::shared_ptr<T> spw2(new T); // make 함수 비사용
std::move()
return std::dynamic_pointer_cast<T>());
*/

/**
 * @brief 
 * 
 */
class ICLASS(asset) {
public:
	virtual ~ICLASS(asset)() {}
};


/**
 * @brief 
 * 
 */
template <typename T>
class asset 
: public ICLASS(asset)
, public T {
};


/**
 * @brief
 * 
 */
class ICLASS(asset_ext) {
public:
	virtual ~ICLASS(asset_ext)() {}

public:
	// pure virtual function providing interface framework.
	virtual std::shared_ptr<ICLASS(asset)> import(const std::string& pathname) =0;
};


/**
 * @brief 
 * 
 */
///class ext {
///public:
///	std::shared_ptr<ICLASS(asset)> import(const std::string& pathname);
///};

template <typename ext>
class asset_ext
: public ICLASS(asset_ext)
, public ext {
public:
	std::shared_ptr<ICLASS(asset)> import(const std::string& pathname) override
	{
    return ext::import(pathname);
  }
};


/**
 * @brief 
 * 
 */
class asset_importer
//: public std::map<const std::string, std::unique_ptr<ICLASS(asset_ext)>>
: public std::map<const std::string, std::shared_ptr<ICLASS(asset_ext)>>
, public unique_ptr<asset_importer>
{
public:
	virtual ~asset_importer() { /*CLOGF();*/ }

	/**
	 * @brief 
	 * 
	 */
	void dump()
	{
		//CLOGF();

		for (auto&& kv : *this)
		{
      COUT << "ext: \"" << kv.first << "\", type: " << typeid_name(*kv.second) << ", use_count: " << kv.second.use_count() << ENDL;
		}
	}
};



#if defined (_LINUX)
#include <unistd.h>
#endif

#if defined (__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#endif

#include "os/osver.h"

/**
 * @brief 
 * 
 */
class asset_manager	
:	public std::map<const std::string, std::shared_ptr<ICLASS(asset)>>
, public unique_ptr<asset_manager>
{
public:
	virtual ~asset_manager() { /*CLOGF();*/ };

private:
	char path_[PATH_MAX];
	char data_path_[PATH_MAX];
	char persistent_data_path_[PATH_MAX];
	char temporary_cache_path_[PATH_MAX];

public:
	const char* path() { return path_; }
	const char* data_path() { return data_path_; }
	const char* persistent_data_path() { return persistent_data_path_; }
	const char* temporary_cache_path() { return temporary_cache_path_; }

public:
	
void init()
{
  //CLOGF();

    ///compiler
    COUT << "- cc: " << __CC__ << " (" << __CC_MAJOR__ << "." << __CC_MINOR__ << "." << __CC_PATCHLEVEL__ << ")" << ENDL;
    COUT << "- os: " << getosversion() << ENDL;


    /// 1
    char path[PATH_MAX];
        
#if defined (_WIN32)
    ::GetCurrentDirectory(PATH_MAX, path);
    //::GetModuleFileName(NULL, path, MAX_PATH);
    
    //    char* slash = strchrl(path, '\\');
    //    *slash = '\0';
    
#elif defined (__APPLE__)
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
    CFStringRef str = CFURLCopyFileSystemPath(resourcesURL, kCFURLPOSIXPathStyle);
    CFRelease(resourcesURL);
    
    CFStringGetCString(str, path, FILENAME_MAX, kCFStringEncodingASCII);
    CFRelease(str);
    
    ///printf("CPP>> %s\n", path);
#else
    getcwd(path, PATH_MAX);
    
#endif //_WIN32
    
    strcpy(path_, path);
    strcpy(data_path_, path);
    strcpy(persistent_data_path_, path);
    strcpy(temporary_cache_path_, path);

    
    /// 2
#if defined (_WIN32)
    strcat(path_, "\\");
    strcat(path_, "\\Resources\\");
    strcat(path_, "\\");
    
#elif defined (__APPLE__)
    
    // iphone
#if defined (__IPHONE_OS_VERSION_MAX_ALLOWED)
    strcat(path_, "/");
    strcat(path_, "/");
    
#if defined (TARGET_OS_IPHONE)
    strcat(persistent_data_path_, "/../Documents/");
    
#elif defined (TARGET_IPHONE_SIMULATOR)
    strcat(persistent_data_path_, "/");
#endif
    
    // mac
#elif defined (__MAC_OS_X_VERSION_MAX_ALLOWED)
    strcat(path_, "/Contents/MacOS/");
    strcat(data_path_, "/Contents/Resources/");
    strcat(persistent_data_path_, "/Contents/MacOS/");

    //strcat(path_, "/");
    //strcat(data_path_, "/Resources/");
    //strcat(_persistentDataPath, "/");

#endif
    
    strcat(temporary_cache_path_, "/Contents/MacOS/");
    ///strcat(temporary_cache_path_, "/Cache");
    
#else
    strcat(path_, "/");
    strcat(path_, "/Resources/");
    strcat(path_, "/");
#endif //_WIN32

  COUT << "- path: " << KYEL << KUNDL << path_ << ENDL;
  COUT << "- data_path: " << KYEL << KUNDL << data_path_ << ENDL;
  COUT << "- persistent_data_path: " << KYEL << KUNDL << persistent_data_path_ << ENDL;
  COUT << "- temporary_cache_path: " << KYEL << KUNDL << temporary_cache_path_ << ENDL;
}

/*
    int& operator[] (int index);
    const int& operator[] (int index) const;

		void operator[] (const std::string& index);

		(*list)[2] = 3; // get our IntList object, then call overloaded operator[]

		std::map<int, const std::string> m;
*/

/*
	std::shared_ptr<ICLASS(asset)>& operator[] (const std::string& name) // for non-const objects: can be used for assignment
	{
		//;

			return find(name);
	}
	const std::shared_ptr<ICLASS(asset)>& operator[] (const char* name) const // for const objects: can only be used for access
	{
		return _assets[name];
	}
*/


	/**
	 * @brief 
	 * 
	 * @param pathname 
	 * @return std::shared_ptr<ICLASS(asset)> 
	 */
	std::shared_ptr<ICLASS(asset)> import(const std::string& pathname)
	{
		//CLOGF();

		{
		auto it = find(pathname);
		if (it != end())
			return it->second;
		}

		/// 2.
		///std::filesystem::path path = pathname;
		///auto ext = path.extension();	// ".png"

		auto pext = pathname.substr(pathname.find_last_of(".") + 1);	// "ext: png"
		
		std::transform(pext.begin(), pext.end(), pext.begin(),
    [](unsigned char c){ return std::tolower(c); });

		//COUT << "ext: " << pext << ENDL;

		auto importer = asset_importer::get();
		auto it = importer->find(pext);
		if (it != importer->end())
		{
			try 
			{
				auto second = it->second->import(pathname);
				///COUT << KYEL << "typeid().name: " << typeid_name(*second) << ENDL;

				//std::map<int, int>::value_type(i, i);
				//std::make_pair(,);
				//std::pair<int, int>(i, i)

				//std::pair<std::map<char,int>::iterator,bool> ret;
				auto ret = insert({pathname, nullptr});
				///COUT << "std::pair<std::map<" << typeid_name(ret.first->first) << ", " << typeid_name(ret.first->second) << ">::iterator, " << typeid_name(ret.second) << ">" << ENDL;
				///COUT << "typeid: " << typeid_name(ret.first->second) << ENDL;

				if (ret.second == true)
				{
					ret.first->second = second;
				}

				return second;
			}
      catch (std::exception& e) {
        COUT << e.what() << ENDL;
			}		
		}

		return nullptr;
	}

	/**
	 * @brief 
	 * 
	 * @tparam T 
	 * @param pathname 
	 * @return std::shared_ptr<T> 
	 */
	template <typename T>
	std::shared_ptr<T> import(const std::string& pathname)
	{
		return std::dynamic_pointer_cast<T>(import(pathname));
	}

	/**
	 * @brief 
	 * 
	 */
	void dump()
	{
		//CLOGF();

		for (auto&& kv : *this)
		{
      COUT << "name: \"" << kv.first << "\", type: " << (kv.second ? typeid_name(*kv.second) : "nullptr");
			if (kv.second) std::cout << ", use_count: " << kv.second.use_count() << ENDL;
			else std::cout << ENDL;
		}

	}
};

inline const std::string asset_path(const std::string& name)
{
	return asset_manager::get()->data_path() + name;
}


