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

	static void TestFalse(std::function<bool(void)> function)
	{
		TestTrue([=]
		{
			return !function();
		});
	}

	static std::chrono::seconds TestTime(std::function<void(void)> function)
	{
		auto start = system_clock::now();

		function();

		return duration_cast<seconds>(system_clock::now() - start);
	}

	static void TestTimeLessThan(std::function<void(void)> function, std::chrono::seconds time)
	{
		auto timePassed = TestTime(function);

		if (timePassed < time)
			assert(true);
		else
			assert(false);
	}

	static void TestTimeMoreThan(std::function<void(void)> function, std::chrono::seconds time)
	{
		auto timePassed = TestTime(function);

		if (timePassed > time)
			assert(true);
		else
			assert(false);
	}

	template<class T> static void TestEqual(std::function<T(void)> function, T value)
	{
		assert(value == function());
	}

	template<class T> static void TestNotEqual(std::function<T(void)> function, T value)
	{
		assert(value != function());
	}

	static void Wait()
	{
		int i;
		std::cin >> i;
	}
};