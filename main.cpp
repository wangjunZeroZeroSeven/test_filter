#include <iostream>
#include <tuple>
//#include "example.h"
// #include "test_stl/variant.h"
// #include "test_example/throw.h"
// #include "test_stl/test_struct.h"
// #include "test_tools/string_formater"
// #include "test_stl/assert.h"
// #include "test_stl/visit_variant.h"
// #include "test_stl/bind.h"
// #include "test_example/method_pointer.h"
// #include "test_example/one_method_override_same_two.h"
// #include "test_example/test_spdlog.h"
// #include "test_example/test_destruct_order.h"
// #include "template/list.h"
// #include "template/transform.h"
// #include "test_basic/reference.h"
// #include "test_stl/unique_ptr.h"
// #include "test_stl/index_seq.h"
// #include "test_basic/counter_macro.h"
// #include "test_basic/rvalue.h"
// #include "test_basic/universal_reference.h"
// #include "test_example/struct_compare.h"
#include "test_basic/trivial.h"


// template<class...Elements>
// struct size : std::integral_constant<size_t, sizeof...(Elements)>
// {};

#include <tuple>

int main(int, char**) {
    std::cout << "begin " << std::endl;
    test_trivial();

    return 0;
}
