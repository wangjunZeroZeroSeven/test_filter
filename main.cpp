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
// #include "test_basic/trivial.h"
// #include "test_basic/forward_failure.h"
// #include "test_basic/function_ptr.h"
// #include "test_basic/struct_bits.h"
// #include  "test_stl/async.h"
// #include "test_basic/test_destructor.h"
// #include "test_basic/uncaught_exception.h"
// #include "test_basic/delete.h"
#include "test_basic/ref_qualifiter.h"

int main(int, char**) {
    std::cout << "begin " << std::endl;
    // test_destructor2();
    // test_uncaught_exception();
    // Color::imcomplete;
    // Color::indeterminate;
    // test_is_lucky();
    test_ref_qualifier();

    return 0;
}
