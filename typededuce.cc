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
// but it doesn't.
// cf: https://www.artima.com/cppsource/rvalue.html
#if 0
wrapped_vector && crval_v = v;
#endif

// TODO: An illustration of move semantics using rvalues.
// Move semantics are used to avoid unnecessary copying. 

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
	
	return 0;
}

