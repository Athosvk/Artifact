#pragma once
#include <functional>

namespace ArtifactTest
{
	class TestUtility
	{
	public:
		TestUtility() = delete;

		static long long measureNS(std::function<void()> a_ToMeasure);
	};
}