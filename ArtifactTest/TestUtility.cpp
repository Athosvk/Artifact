#include "stdafx.h"

#include "TestUtility.h"
#include "StopWatch.h"

namespace ArtifactTest
{
	long long TestUtility::measureNS(std::function<void()> a_ToMeasure)
	{
		StopWatch stopWatch = StopWatch::startNew();
		a_ToMeasure();
		stopWatch.end();
		return stopWatch.toNanoseconds();
	}
}
