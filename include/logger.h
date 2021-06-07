/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once


/**
 * @brief 
 * 
 */
#if defined (_MSC_VER)
#define __PRETTY_FUNCTION__ __function__
#endif


/**
 * @brief 
 * 
 */
#define COUT std::cout << KMAG << ">> " << RST
#define LOG_cout COUT

#define ENDL RST << std::endl

#define COUT_LF ENDL << KMAG << ">> " << RST

#define COUT_ptr(p) KGRN << __typeid_name(*(p)) << "(" << p << ")" << RST << ": "
#define COUT_shared_ptr(p) KYEL << "std::shared_ptr<" << __typeid_name(*(p)) << "> " << #p << ".use_count: " << p.use_count() << RST

#define COUT_func KCYN << KUNDL << __FILE__ << ":" << __LINE__ << RST << ":" << KBLU << " - " << __PRETTY_FUNCTION__ << RST
#define COUT_method COUT_ptr(this) << KCYN << KUNDL << __FILE__ << ":" << __LINE__ << RST << ":" << KBLU << " - " << __PRETTY_FUNCTION__ << RST



/**
#include <iostream>
using namespace std;

class Point {
private:
	int x, y;
public:
	Point(int _x=0, int _y=0):x(_x), y(_y){}
	friend ostream& operator<<(ostream& os, const Point& p);
};

ostream& operator<<(ostream& os, const Point& p)
{
	os<<"["<<p.x<<", "<<p.y<<"]"<<endl;	
	return os;
}

int main(void)
{
	Point p(1, 3);
	cout<<p;

	return 0;
}
**/



/**
 * @brief 
 * 
 */

/*
try 
{
  //throw ...
  char e[255];
  sprintf(e, E_str());

  throw std::runtime_error(e);
} 
catch (std::exception& e) 
{
  std::cout << e.what();
}
*/



/**
 * @brief 
 * 
 */
#if defined (DEBUG)

#include <cstdarg>
#include <cstdio>

inline int __printf(const char * fmt, ...)
{
  std::va_list vl;
  va_start(vl, fmt);
  int ret = std::vfprintf(stdout, fmt, vl);
  va_end(vl);
  return ret;
}

#if defined (_MSC_VER)
  //
  #define LOG_printf(fmt, ...) __printf(">> %s%s%s:%d%s: - " fmt, KCYN, KUNDL, __FILE__, __LINE__, RST, ##__VA_ARGS__); __printf("%s", RST);
  #define CLOG_printf(fmt, ...) __printf(">> %s%s(%p)%s: %s%s%s:%d%s: - " fmt, KGRN, __typeid_name(*this), this, RST, KCYN, KUNDL, __FILE__, __LINE__, RST, ##__VA_ARGS__); __printf("%s", RST);

#elif defined (__GNUC__)
  //
  #define LOG_printf(fmt, args...) __printf(">> %s%s%s:%d%s: - " fmt, KCYN, KUNDL, __FILE__, __LINE__, RST, ##args); __printf("%s", RST);
  #define CLOG_printf(fmt, args...) __printf(">> %s%s(%p)%s: %s%s%s:%d%s: - " fmt, KGRN, __typeid_name(*this), this, RST, KCYN, KUNDL, __FILE__, __LINE__, RST, ##args); __printf("%s", RST);

  //#define E_str(fmt, args...) "%sException: %s%s%s:%d%s - %s%s%s" fmt, KRED, KCYN, KUNDL, __FILE__, __LINE__, RST, KBLU, __PRETTY_FUNCTION__, RST, ##args
  #define E_str(fmt, args...) "%sException: %s%s%s:%d%s - " fmt, KRED, KCYN, KUNDL, __FILE__, __LINE__, RST, ##args

#else ///???
#endif //_MSC_VER


/**
 * @brief 
 * 
 */
#define LOG_ptr(p) {if (p) { __printf(">> %s%s%s:%d%s: - %sptr<%s> %s%s\n", KCYN, KUNDL, __FILE__, __LINE__, RST, KYEL, __typeid_name(*(p)), #p, RST); }}
#define LOG_shared_ptr(p) {if (p) { __printf(">> %s%s%s:%d%s: - %sstd::shared_ptr<%s> %s.use_count: %d%s\n", KCYN, KUNDL, __FILE__, __LINE__, RST, KYEL, __typeid_name(*(p)), #p, p.use_count(), RST); }}

#define CLOG_ptr(p) {if (p) { __printf(">> %s%s(%p)%s: %s%s%s:%d%s: - %sptr<%s> %s%s\n", KGRN, __typeid_name(*this), this, RST, KCYN, KUNDL, __FILE__, __LINE__, RST, KYEL, __typeid_name(*(p)), #p, RST); }}
#define CLOG_shared_ptr(p) {if (p) { __printf(">> %s%s(%p)%s: %s%s%s:%d%s: - %sstd::shared_ptr<%s> %s.use_count: %d%s\n", KGRN, __typeid_name(*this), this, RST, KCYN, KUNDL, __FILE__, __LINE__, RST, KYEL, __typeid_name(*(p)), #p, p.use_count(), RST); }}

#define __function__ __printf(">> %s%s%s:%d%s: %s- %s%s\n", KCYN, KUNDL, __FILE__, __LINE__, RST, KBLU, __PRETTY_FUNCTION__, RST);
#define __method__ __printf(">> %s%s(%p)%s: %s%s%s:%d%s: %s- %s%s\n", KGRN, __typeid_name(*this), this, RST, KCYN, KUNDL, __FILE__, __LINE__, RST, KBLU, __PRETTY_FUNCTION__, RST);

#define __py_function__ __printf(">> %s%s%s:%d%s: %s- %s%s\n", KYEL, KUNDL, __FILE__, __LINE__, RST, KBLU, __PRETTY_FUNCTION__, RST);

#define __break__ __printf(">> %s%s%s:%d%s\n", KRED, KUNDL, __FILE__, __LINE__, RST);


#else
#if defined (_MSC_VER)
  //
  #define LOG_printf(fmt, ...)
  #define CLOG_printf(fmt, ...)

#elif defined (__GNUC__)
  //
  #define LOG_printf(fmt, args...)
  #define CLOG_printf(fmt, args...)

#else ///???
#endif //_MSC_VER


/**
 * @brief 
 * 
 */
#define LOG_ptr(p)
#define LOG_shared_ptr(p)

#define CLOG_ptr(p)
#define CLOG_shared_ptr(p)

#define __function__
#define __method__
#define __break__

#endif //_DEBUG

