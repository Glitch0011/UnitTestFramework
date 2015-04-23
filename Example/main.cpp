#include <UnitTest.h>

#include <thread>

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


	UnitTest::Wait();
}