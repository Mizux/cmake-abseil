#include <iostream>
#include "absl/strings/substitute.h"

int main(int argc, char** argv) {
	std::cout << "hello" << std::endl;
  for (int i = 0; i < argc; ++i) {
    std::cout << absl::Substitute("Arg $0: $1\n", i, argv[i]);
  }	return 0;
}

