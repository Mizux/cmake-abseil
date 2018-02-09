#include <foo/Foo.hpp>

#include <absl/base/config.h>
#include <iostream>

namespace foo {
  void helloWorld() {
		std::cout << "foo::hello()";
  }

void Foo::operator()() const {
	std::cout << "foo::Foo()()";
}
}

