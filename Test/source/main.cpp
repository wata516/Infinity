#include <gtest/gtest.h>
#include <conio.h>

GTEST_API_ int main(int argc, char **argv) {
	std::cout << "Running main() from gtest_main.cc\n";

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	_getch();
}
