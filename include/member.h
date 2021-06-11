/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once


/**
 *
 */
template <typename V>
class member_ {
protected:
	void* target_;
	
public:
	virtual ~member_()
	{
	}
	
	template <typename T>
	member_(T* target)
	: target_(target)
	{
	}	
		
	virtual void set(V value) = 0;
	virtual V get() const = 0;
};



/**
 * member
 */
template <typename V>
class member : public member_<V> {
protected:
	void* ptr_;
	
public:
	template <typename T, typename M>
	member(T* target, M member)
	: member_<V>(target)
	{
		union {
			M m;
			unsigned char b[sizeof(M)];
		} mu;		
		mu.m = member;
		
		unsigned char* ptr = (unsigned char*) malloc(sizeof(M));
		
		for (size_t i=0; i<sizeof(M); ++i)
			ptr[i] = mu.b[i];
		
		ptr_ = ptr;
	}
	~member()
	{
		if (ptr_)
		{
			free(ptr_);
			ptr_ = nullptr;
		}
	}
	
	
	void set(V value)
	{
		struct _T{};
		typedef V _T::*M;
		
		M* mptr = static_cast<M*> (ptr_);
		M member = *mptr;
		
		((_T*) member_<V>::target_)->*member = value;
	}

	V get() const
	{
		struct _T{};
		typedef V _T::*M;
		
		M* mptr = static_cast<M*> (ptr_);
		M member = *mptr;
		
		return ((_T*) member_<V>::target_)->*member;
	}
};



/**
 * function
 */
template <typename V>
class getset : public member_<V> {
private:
	void* getter_;
	void* setter_;

private:
	template <typename M>
	void set_getter(M getter)
	{
		union {
			M m;
			unsigned char b[sizeof(M)];
		} mu;
		mu.m = getter;
		
		unsigned char* ptr = (unsigned char*) malloc(sizeof(M));
		
		for (size_t i=0; i<sizeof(M); ++i)
			ptr[i] = mu.b[i];
		
		getter_ = ptr;
	}

	template <typename M>
	void set_setter(M setter)
	{
		union {
			M m;
			unsigned char b[sizeof(M)];
		} mu;		
		mu.m = setter;
		
		unsigned char* ptr = (unsigned char*) malloc(sizeof(M));
		
		for (size_t i=0; i<sizeof(M); ++i)
			ptr[i] = mu.b[i];
		
		setter_ = ptr;
	}

public:
	template <typename T, typename Getter, typename Setter>
	getset(T* target, Getter getter, Setter setter)
	: member_<V>(target)
	{
		set_getter<Getter>(getter);
		set_setter<Setter>(setter);
	}
	
	~getset()
	{
		if(getter_)
		{
			free(getter_);
			getter_ = nullptr;
		}

		if(setter_)
		{
			free(setter_);
			setter_ = nullptr;
		}
	}
	
	
	/**
	 * set
	 */
	void set(V value)
	{
		struct _T{};
		typedef void (_T::*M)(V);
		
		M* method_ptr = static_cast<M*> (setter_);
		M method = *method_ptr;
		
		(((_T*) member_<V>::target_)->*method) (value);
	}
	
	
	/**
	 * get
	 */
	V get() const
	{
		struct _T{};
		typedef V (_T::*M)();
		
		M* method_ptr = static_cast<M*> (getter_);
		M method = *method_ptr;
		
		return (((_T*) member_<V>::target_)->*method) ();
	}
};


/**
 *
 */
class member_ptr_ {
protected:
	void* tp_ptr_;
	
public:
	virtual ~member_ptr_()
	{
		if (tp_ptr_)
		{
			member_<int>* p = static_cast<member_<int>*>(tp_ptr_);
			delete p;
			
			tp_ptr_ = nullptr;
		}
	}
		
	/**
	 *
	 */
	template <typename V>
	void set(V value)
	{
		member_<V>* p = static_cast<member_<V>*>(tp_ptr_);
		p->set(value);
	}
	
	template <typename V>
	V get() const
	{
		member_<V>* p = static_cast<member_<V>*>(tp_ptr_);
		return p->get();
	}
};



/**
 *
 */
template <typename V>
class member_ptr : public member_ptr_ {
public:
	template <typename T, typename M>
	member_ptr(T* target, M member)
	{
		tp_ptr_ = new ::member<V>(target, member);
	}
	
	template <typename T, typename Getter, typename Setter>
	member_ptr(T* target, Getter getter, Setter setter)
	{
		tp_ptr_ = new getset<V>(target, getter, setter);
	}

///
	void set_(V value)
	{
		set<V>(value);
	}
	
	V get_() const
	{
		return get<V>();
	}
};
