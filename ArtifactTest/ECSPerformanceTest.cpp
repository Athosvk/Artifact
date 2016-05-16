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
			for(int i = 0; i < 100000; i++)
			{
				auto entity = m_EntitySystem.createEntity();
				entity.addComponent<Artifact::SpriteRenderer>();
				entity.addComponent<Artifact::AudioSource>();
				entity.addComponent<Artifact::TextComponent>();
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
			Assert::IsTrue(timeTaken <= 1e3);
		}

		TEST_METHOD(TestIterationSingleType)
		{
			auto timeTaken = TestUtility::measureNS([this]
			{
				performIteration();
			});
			timeTaken -= TestUtility::measureNS([this]
			{
				performComponentTypeFetch();
			}) * 3;
			std::string output = "Iteration test time taken: " + 
				std::to_string(timeTaken / 1e6) + " ms\n";
			Logger::WriteMessage(output.c_str());
			Assert::IsTrue(timeTaken <= 1.5e7);
		}

		void performIteration()
		{
			for(auto component : m_EntitySystem.getComponentsOfType<Artifact::SpriteRenderer>())
			{
				component->Color = Artifact::Color::Black;
				component->Depth++;
				component->Height *= 1.0001f;
			}
			for(auto component : m_EntitySystem.getComponentsOfType<Artifact::AudioSource>())
			{
				component->Volume++;
				component->Sound = nullptr;
			}
			for(auto component : m_EntitySystem.getComponentsOfType<Artifact::TextComponent>())
			{
				component->Color.r *= 1.11f;
				component->Color.g += 1.0f;
				component->Depth = 1.0f;
			}
		}

		void performComponentTypeFetch()
		{
			m_EntitySystem.getComponentsOfType<Artifact::Transform>();
		}
	};
}