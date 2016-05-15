#include "stdafx.h"

#include "CppUnitTest.h"
#include "TestUtility.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArtifactTest
{		
	TEST_CLASS(ECSPerformanceTest)
	{
		Artifact::MessagingSystem m_MessagingSystem;
		Artifact::EntitySystem m_EntitySystem = (m_MessagingSystem);

	public:
		ECSPerformanceTest()
		{
			for(int i = 0; i < 1000000; i++)
			{
				auto entity = m_EntitySystem.createEntity();
				entity.addComponent<Artifact::SpriteRenderer>();
			}
		}

		TEST_METHOD(TestComponentByTypeFetch)
		{
			auto timeTaken = TestUtility::measureNS([this]
			{
				performComponentTypeFetch();
			});
			std::string output = "Fetch test time taken: " +
				std::to_string(timeTaken / 1e6) + " ms\n";
			Logger::WriteMessage(output.c_str());
			Assert::IsTrue(timeTaken <= 1e8);
		}

		TEST_METHOD(TestIteration)
		{
			auto timeTaken = TestUtility::measureNS([this]
			{
				performIteration();
			});
			timeTaken -= TestUtility::measureNS([this]
			{
				performComponentTypeFetch();
			});
			std::string output = "Iteration test time taken: " + 
				std::to_string(timeTaken / 1e6) + " ms\n";
			Logger::WriteMessage(output.c_str());
			Assert::IsTrue(timeTaken <= 1e6);
		}

		void performIteration()
		{
			for(auto component : m_EntitySystem.getComponentsOfType<Artifact::Transform>())
			{
				component->setPosition(glm::vec2(0.0f, 0.0f));
			}
		}

		void performComponentTypeFetch()
		{
			m_EntitySystem.getComponentsOfType<Artifact::Transform>();
		}
	};
}