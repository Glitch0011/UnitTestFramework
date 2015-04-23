#include <UnitTest.h>

#include <thread>
#include <random>

int main()
{
	UnitTest::TestTrue([=]
	{
		return true;
	});

	UnitTest::TestEqual<int>([=]
	{
		return 1;
	}, 1);


	UnitTest::TestTimeLessThan([=]
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	}, std::chrono::seconds(1));

	UnitTest::TestWithin<double>([=]
	{
		auto device = std::default_random_engine();
		auto engine = std::uniform_real_distribution<double>(9.0, 10.0);

		return engine(device);
	}, 10.0, 1.0);

	UnitTest::Wait();
}