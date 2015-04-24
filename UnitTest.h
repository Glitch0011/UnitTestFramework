#include <functional>
#include <chrono>
#include <cassert>
#include <iostream>

#include <HighAccuracyWindowsStopwatch/Stopwatch.h>

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

private:
	template<class T> static bool GreaterThan(std::function<T(void)> function, T compare)
	{
		return function() > compare;
	}

public:
	template<class T> static void TestGreaterThan(std::function<T(void)> function, T compare)
	{
		assert(GreaterThan(function, compare));
	}

	template<class T> static void TestLessThan(std::function<T(void)> function, T compare)
	{
		assert(!GreaterThan(function, compare));
	}

	static std::chrono::microseconds TestTime(std::function<void(void)> function)
	{
		Stopwatch stopwatch;

		auto start = system_clock::now();

		function();

		return std::chrono::microseconds((long long)(stopwatch.GetTime() * 1000000));
	}

	template<class T> static void TestTimeLessThan(std::function<void(void)> function, T time)
	{
		auto timePassed = TestTime(function);

		if (timePassed < time)
			assert(true);
		else
			assert(false);
	}

	template<class T> static void TestTimeMoreThan(std::function<void(void)> function, T time)
	{
		auto timePassed = TestTime(function);

		if (timePassed > time)
			assert(true);
		else
			assert(false);
	}

	template<class T> static void TestWithin(std::function<T(void)> function, T origin, T allowedOffset)
	{
		auto result = function();

		result = abs(origin - result);

		if (result < allowedOffset)
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