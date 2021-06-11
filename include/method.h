/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once


/**
 *
 */
template <typename V>
class tp_method {
protected:
	void* target_;
	void* method_;
	
public:
	tp_method()
	: target_(nullptr)
	, method_(nullptr)
	{
	}
	
	template <typename T, typename M>
	tp_method(T* target, M method)
	: target_(target)
	, method_(nullptr)
	{
		union {
			M m;
			unsigned char b[sizeof(M)];
		} _mu;
		
		_mu.m = method;
		
		unsigned char* ptr = (unsigned char*) malloc(sizeof(M));
		
		for (size_t i=0; i<sizeof(M); ++i)
			ptr[i] = _mu.b[i];
		
		method_ = ptr;
	}
	
	virtual ~tp_method()
	{
		//__FUNC_YEL__

		target_ = nullptr;

		if (method_) { 
			free(method_); 
			method_ = nullptr;
		};
	}
		
	/**
	 *
	 */
	V operator () ()
	{
		struct _T{};
		typedef V (_T::*M)();
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) ();
	}

	V operator () () const
	{
		struct _T{};
		typedef V (_T::*M)() const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) ();
	}

	
	/**
	 *
	 */
	template <typename A1>
	V operator () (A1 a1)
	{
		struct _T{};
		typedef V (_T::*M)(A1);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1);
	}

	template <typename A1>
	V operator () (A1 a1) const
	{
		struct _T{};
		typedef V (_T::*M)(A1) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1);
	}
	
	/**
	 *
	 */
	template <typename A1, typename A2>
	V operator () (A1 a1, A2 a2)
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2);
	}
	
	template <typename A1, typename A2>
	V operator () (A1 a1, A2 a2) const
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2);
	}

	
	/**
	 *
	 */
	template <typename A1, typename A2, typename A3>
	V operator () (A1 a1, A2 a2, A3 a3)
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3);
	}
	
	template <typename A1, typename A2, typename A3>
	V operator () (A1 a1, A2 a2, A3 a3) const
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3);
	}

	/**
	 *
	 */
	template <typename A1, typename A2, typename A3, typename A4>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4)
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4);
	}
	
	template <typename A1, typename A2, typename A3, typename A4>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4) const
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4);
	}

	/**
	 *
	 */
	template <typename A1, typename A2, typename A3, typename A4, typename A5>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5);
	}
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5);
	}

	/**
	 *
	 */
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6);
	}
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6);
	}

	/**
	 *
	 */
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7);
	}
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7);
	}

	/**
	 *
	 */
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8);
	}
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8);
	}

	/**
	 *
	 */
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8, a9);
	}
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8, a9);
	}

	/**
	 *
	 */
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10)
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
	}
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
	}

	/**
	 *
	 */
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11)
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
	}
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
	}

	/**
	 *
	 */
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12)
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
	}
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) const
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
	}

	/**
	 *
	 */
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13)
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
	}
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13) const
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
	}

	/**
	 *
	 */
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14)
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14);
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
	}
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
	V operator () (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14) const
	{
		struct _T{};
		typedef V (_T::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14) const;
		
		M* method_ptr = static_cast<M*> (method_);
		M method = *method_ptr;
		
		return (((_T*) target_)->*method) (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
	}


/*
*/

	V r() { return this->operator () (); }
	V r() const { return this->operator () (); }

	template <typename A1>
	V r(A1 a1) { return this->operator () <A1> (a1); }

	template <typename A1>
	V r(A1 a1) const { return this->operator () <A1> (a1); }
	
	template <typename A1, typename A2>
	V r(A1 a1, A2 a2) { return this->operator () <A1,A2> (a1,a2); }
	
	template <typename A1, typename A2>
	V r(A1 a1, A2 a2) const { return this->operator () <A1,A2> (a1,a2); }

	template <typename A1, typename A2, typename A3>
	V r(A1 a1, A2 a2, A3 a3) { return this->operator () <A1,A2,A3> (a1,a2,a3); }
	
	template <typename A1, typename A2, typename A3>
	V r(A1 a1, A2 a2, A3 a3) const { return this->operator () <A1,A2,A3> (a1,a2,a3); }

	template <typename A1, typename A2, typename A3, typename A4>
	V r(A1 a1, A2 a2, A3 a3, A4 a4) { return this->operator () <A1,A2,A3,A4> (a1,a2,a3,a4); }
	
	template <typename A1, typename A2, typename A3, typename A4>
	V r(A1 a1, A2 a2, A3 a3, A4 a4) const { return this->operator () <A1,A2,A3,A4> (a1,a2,a3,a4); }

	template <typename A1, typename A2, typename A3, typename A4, typename A5>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) { return this->operator () <A1,A2,A3,A4,A5> (a1,a2,a3,a4,a5); }
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const { return this->operator () <A1,A2,A3,A4,A5> (a1),a2,a3,a4,a5; }

	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) { return this->operator () <A1,A2,A3,A4,A5,A6> (a1,a2,a3,a4,a5,a6); }
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const { return this->operator () <A1,A2,A3,A4,A5,A6> (a1,a2,a3,a4,a5,a6); }

	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) { return this->operator () <A1,A2,A3,A4,A5,A6,A7> (a1,a2,a3,a4,a5,a6,a7); }
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return this->operator () <A1,A2,A3,A4,A5,A6,A7> (a1,a2,a3,a4,a5,a6,a7); }

	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8> (a1,a2,a3,a4,a5,a6,a7,a8); }
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8> (a1,a2,a3,a4,a5,a6,a7,a8); }

	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8,A9> (a1,a2,a3,a4,a5,a6,a7,a8,a9); }
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8,A9> (a1,a2,a3,a4,a5,a6,a7,a8,a9); }

	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8,A9,A10> (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10); }
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8,A9,A10> (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10); }

	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11> (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11); }
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11> (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11); }

	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12> (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12); }
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) const { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12> (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12); }

	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13) { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13> (a1,a2,a3,a4,a5,a6,a7,a8,a9,10,a11,a12,a13); }
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13) const { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13> (a1,a2,a3,a4,a5,a6,a7,a8,a9,10,a11,a12,a13); }

	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14) { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> (a1,a2,a3,a4,a5,a6,a7,a8,a9,10,a11,a12,a13,a14); }
	
	template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
	V r(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14) const { return this->operator () <A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> (a1,a2,a3,a4,a5,a6,a7,a8,a9,10,a11,a12,a13,a14); }

};

