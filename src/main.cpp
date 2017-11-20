#include "runtime_options.h"
#include <build_options.h>

#include <iostream>

int main(int, char**) {
	runtime_options.a_launch_option = true;

	if (runtime_options.a_launch_option) {
		std::cout << "Do runtime things." << std::endl;
	}

	if constexpr (build_options.my_bool) {
		std::cout << "Bool is set." << std::endl;

		if constexpr (build_options.my_int == 42) {
			std::cout << "  Do something with int." << std::endl;
		}
	}

	if constexpr (build_options.cpp_version != CppVersion::cpp17) {
		std::cout << "Well... This wouldn't compile now would it."
				  << "Maybe this will become relevant in 20 years? ;)"
				  << std::endl;
	}

	return 0;
}
