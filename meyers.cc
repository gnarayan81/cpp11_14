#include <iostream>
#include <typeinfo>
#include <vector>
#include <initializer_list>

// Initializer_list.
class wrapped_vector
{
	std::vector<int> m_intvec;
	
public:
	wrapped_vector()
	{
		
	}

	wrapped_vector(const std::initializer_list<int> & il) : m_intvec(il)
	{
		
	}
	
	int size() const
	{
		return m_intvec.size();
	}
};

// A trivial enum-class example.
enum class TheStrictlyTypedEnum
{
	E_TSTE_0,
	E_TSTE_1
};

enum class TheSecondStrictlyTypedEnum
{
	E_TSSTE_0,
	E_TSSTE_1
};

// Some l/rvalue references. 
// Not a reference.
wrapped_vector v;
// An lvalue reference, won't compile.
#if 0
wrapped_vector & lval_v = wrapped_vector();
#endif
// A const lvalue reference, will compile.
const wrapped_vector & clval_v = wrapped_vector();
// An rvalue reference to a temporary object, will compile.
wrapped_vector && rval_v = wrapped_vector();
// An rvalue reference to a object. Bjarne et al say it should compile
// but it doesn't, unless I use a move semantic
// cf: https://www.artima.com/cppsource/rvalue.html
// STRIKE THAT OUT.
// ...
// Note that Scott Meyers refers to this as a universal reference because
// a universal reference can be either an rvalue or an lvalue, depending 
// on whether the expression is an rvalue or an lvalue. This, however, does 
// not hold true for non-deduced, i.e., non-templated or non-auto'd types.
// The following code, for instance, would fail if instead of auto, I'd 
// used wrapper_vector.
auto&& crval_v = v; //std::move(v);

//----------------------------------------------------------------------
// Type deduction class.
struct s_td { // Do not make this a class template, unless the template 
			  // is necessary for something other than echoval(...)
	template <typename K>
	void echoval(K&& t) // Universal reference.
	{
		std::cout << "t = " << t << '\n';
	}
};

//----------------------------------------------------------------------
// Universal type deduction.

void universal_type_deduction(void)
{
	// Trivially, 
	int x = 42;
	int& l_rx = x; // fine
	int&& r_rx1 = 42; // fine
	//int&& r_rx2 = x; // I know it will fail compile here.
	auto&& r_rx3 = 42; // fine, rvalue
	auto&& r_rx4 = x; // fine, type-deduced! Universal.
	auto&& r_rx5 = l_rx; // fine, type-deduced! Universal.
	
	s_td().echoval(42); // Do not specialize!
	s_td().echoval(x); 
}

//----------------------------------------------------------------------
// Initializer list(s).
// As per Meyers.
void initializer_lists(void)
{
	// Consider initializing an int.
	auto x1 = 42; // fine 
	auto x2(42);  // fine
	auto x3 = {42}; // fine
	auto x4{42}; // fine
	
	// However, 
	std::cout << typeid(x1).name() << '\n';
	std::cout << typeid(x2).name() << '\n';
	std::cout << typeid(x3).name() << '\n';
	std::cout << typeid(x4).name() << '\n';
	
	// operations,
	x1 += 1; // fine
	x2 += 1; // fine
	// x3 += 1; // fails, mismatched type
	// x4 = x4 + 1; // fails in every which way.
}

//----------------------------------------------------------------------
// On type deduction, using typeids in a C++11 context.
// Much of is this following Scott Meyers's Effective Modern C++ (11, 14)
// I'm using lambdas here, for which the syntax template is, 
// [ capture-list ] ( params ) -> ret { body }
void type_deduction(void)
{
	/* Consider passing by reference. */
	{
		// 1. lvalue references
		auto x = 12;
		auto& rx = x;
		const auto& crx = x;
		// [=] captures all automatic variables in lambda context by value
		// [&] captures all automatic variables in lambda context by reference
		auto l_v = [=]() /* no ret */ { 
			std::cout << "[val]typeid of x = " << typeid(x).name() << std::endl;
			std::cout << "[val]typeid of rx = " << typeid(rx).name() << std::endl;
			std::cout << "[val]typeid of crx = " << typeid(crx).name() << std::endl;
		};
		
		auto l_r = [&]() /* no ret */ { 
			std::cout << "[ref]typeid of x = " << typeid(x).name() << std::endl;
			std::cout << "[ref]typeid of rx = " << typeid(rx).name() << std::endl;
			std::cout << "[ref]typeid of crx = " << typeid(crx).name() << std::endl;
		};	
		
		l_v();
		l_r();
		
		//##############################################################
		// 2. rvalue references
		
	}
}	

//----------------------------------------------------------------------
// My EP.
int main()
{
	auto auto_test = 1;
	auto auto_test_1 = auto_test;
	decltype(auto_test) decltype_test = 30;
	
	std::cout << typeid(auto_test).name() << std::endl;
	std::cout << auto_test_1 << std::endl;
	std::cout << decltype_test << std::endl;
	
	wrapped_vector vc = {4, 5, 3, 3};
	
	std::cout << "vc size is " << vc.size() << std::endl;
	
#if 0 // Enable this for a very verbose compile error.	
	if (TheStrictlyTypedEnum::E_TSTE_0 == TheSecondStrictlyTypedEnum::E_TSSTE_0)
		std::cout << "This won't even get here, will it ?" << std::endl;
#endif

	// Uniform initializers.
	std::vector<int> v_size8(8);
	std::vector<int> v_size_1_unifinit{8};
	std::cout << "size of v_size8 is " << v_size8.size() << std::endl;
	std::cout << "size of v_size_1_unifinit is " << v_size_1_unifinit.size() << std::endl;
	
	// Illustrating some fun C++11 iteration
	for (auto& x : v_size_1_unifinit)
		std::cout << x << std::endl;
	
	std::cout << std::endl;
	std::cout << std::endl;
	//	
	type_deduction();
	// 
	std::cout << std::endl;
	std::cout << std::endl;
	//
	universal_type_deduction();
	
	initializer_lists();
	
	return 0;
}

