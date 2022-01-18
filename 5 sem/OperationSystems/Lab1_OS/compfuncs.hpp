#ifndef _OS_LAB1_COMPFUNCS_H
#define _OS_LAB1_COMPFUNCS_H

#include <variant>
#include <iostream>

namespace os::lab1::compfuncs {

    struct hard_fail {};
    struct soft_fail {};

    template<typename T>
    using comp_result = std::variant<hard_fail, soft_fail, T>;

    enum op_group { AND, OR, INT_SUM, DOUBLE_SUM, INT_MULT, DOUBLE_MULT };

    template<typename T> 
    struct op_group_type_traits {
	typedef T value_type;
	typedef comp_result<T> result_type;
    };

    static 
    std::ostream& operator<<(std::ostream& os, const hard_fail) {
	os << "hard fail";
	return os;
    }

    static
    std::ostream& operator<<(std::ostream& os, const soft_fail) {
	os << "soft fail";
	return os;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const comp_result<T> &res) {
	switch (res.index()) {
	case 0:
		return os << hard_fail();
	case 1:
		return os << soft_fail();
	case 2:
		return os << "val(" << std::get<2>(res) << ")";
	}
	return os;
    }

    template<op_group O>
    struct op_group_traits;

    template<> 
    struct op_group_traits<INT_SUM> : op_group_type_traits<int> {};

    template<> 
    struct op_group_traits<INT_MULT> : op_group_type_traits<int> {};

    template<> 
    struct op_group_traits<DOUBLE_SUM> : op_group_type_traits<double> {};

    template<> 
    struct op_group_traits<DOUBLE_MULT> : op_group_type_traits<double> {};

    template<> 
    struct op_group_traits<AND> : op_group_type_traits<bool> {};

    template<> 
    struct op_group_traits<OR> : op_group_type_traits<bool> {};
	
    //extern
    template<op_group O> typename op_group_traits<O>::result_type probe_f(int ); 

    //extern
    template<op_group O> typename op_group_traits<O>::result_type probe_g(int );

}

#endif // _OS_LAB1_COMPFUNCS_H
