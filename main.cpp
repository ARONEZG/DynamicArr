#include <iostream>

#include "array.h"
#include "tests.h"
int main() {
    try {
        test_default_constructor();
        test_size_constructor();
        test_copy_constructor();
        test_move_constructor();
        test_resize();
        test_pushBack();
        test_operator_access();
        test_out_of_bounds();
        test_with_strings();
        test_negative_index();

        std::cout << "\nAll tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}