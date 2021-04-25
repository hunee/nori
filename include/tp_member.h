/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once


/**
 *
 */
template <typename V>
class ICLASS(tp_member) {
protected:
	void* target_;
	
public:
	virtual ~ICLASS(tp_member)()
	{
	}
	
	template <typename T>
	ICLASS(tp_member)(T* target)
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
class tp_member : public ICLASS(tp_member)<V> {
protected:
	void* member_;
	
public:
	template <typename T, typename M>
	tp_member(T* target, M member)
	: ICLASS(tp_member)<V>(target)
	{
		union {
			M m;
			unsigned char b[sizeof(M)];
		} mu;		
		mu.m = member;
		
		unsigned char* ptr = (unsigned char*) malloc(sizeof(M));
		
		for (size_t i=0; i<sizeof(M); ++i)
			ptr[i] = mu.b[i];
		
		member_ = ptr;
	}
	~tp_member()
	{
		if (member_)
		{
			free(member_);
			member_ = nullptr;
		}
	}
	
	
	void set(V value)
	{
		struct _T{};
		typedef V _T::*M;
		
		M* member_ptr = static_cast<M*> (member_);
		M member = *member_ptr;
		
		((_T*) ICLASS(tp_member)<V>::target_)->*member = value;
	}

	V get() const
	{
		struct _T{};
		typedef V _T::*M;
		
		M* member_ptr = static_cast<M*> (member_);
		M member = *member_ptr;
		
		return ((_T*) ICLASS(tp_member)<V>::target_)->*member;
	}
};



/**
 * function
 */
template <typename V>
class tp_getset : public ICLASS(tp_member)<V> {
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
	tp_getset(T* target, Getter getter, Setter setter)
	: ICLASS(tp_member)<V>(target)
	{
		set_getter<Getter>(getter);
		set_setter<Setter>(setter);
	}
	
	~tp_getset()
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
		
		(((_T*) ICLASS(tp_member)<V>::target_)->*method) (value);
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
		
		return (((_T*) ICLASS(tp_member)<V>::target_)->*method) ();
	}
};


/**
 *
 */
class ICLASS(tp_member_ptr) {
protected:
	void* tp_ptr_;
	
public:
	virtual ~ICLASS(tp_member_ptr)()
	{
		if (tp_ptr_)
		{
			ICLASS(tp_member)<int>* p = static_cast<ICLASS(tp_member)<int>*>(tp_ptr_);
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
		ICLASS(tp_member)<V>* p = static_cast<ICLASS(tp_member)<V>*>(tp_ptr_);
		p->set(value);
	}
	
	template <typename V>
	V get() const
	{
		ICLASS(tp_member)<V>* p = static_cast<ICLASS(tp_member)<V>*>(tp_ptr_);
		return p->get();
	}
};



/**
 *
 */
template <typename V>
class tp_member_ptr : public ICLASS(tp_member_ptr) {
public:
	template <typename T, typename M>
	tp_member_ptr(T* target, M member)
	{
		tp_ptr_ = new tp_member<V>(target, member);
	}
	
	template <typename T, typename Getter, typename Setter>
	tp_member_ptr(T* target, Getter getter, Setter setter)
	{
		tp_ptr_ = new tp_getset<V>(target, getter, setter);
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
