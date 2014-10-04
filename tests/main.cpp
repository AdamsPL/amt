#include <QCoreApplication>
#include <gtest/gtest.h>

using namespace ::testing;

int main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
