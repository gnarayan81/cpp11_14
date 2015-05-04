#include <iostream>
#include <typeinfo>
#include <vector>
#include <initializer_list>

// Initializer_list.
class wrapped_vector
{
	std::vector<int> m_intvec;
	
public:
	wrapped_vector(const std::initializer_list<int> & il) : m_intvec(il)
	{
		
	}
	
	int size() const
	{
		return m_intvec.size();
	}
};


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
	
	return 0;
}

