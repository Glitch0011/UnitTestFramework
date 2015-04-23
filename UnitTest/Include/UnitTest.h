#include <functional>
#include <chrono>
#include <cassert>
#include <iostream>

using namespace std::chrono;

class UnitTest
{
public:
	static void TestTrue(std::function<bool(void)> function)
	{
		if (function())
			assert(true);
		else
			assert(false);
	}

	static void TestTime(std::function<void(void)> function, std::chrono::seconds time)
	{
		auto start = system_clock::now();

		function();

		auto timePassed = duration_cast<seconds>(system_clock::now() - start);

		if (timePassed < time)
			assert(true);
		else
			assert(false);
	}

	template<class T> static void TestEqual(std::function<T(void)> function, T value)
	{
		assert(value == function());
	}

	static void Wait()
	{
		int i;
		std::cin >> i;
	}
};