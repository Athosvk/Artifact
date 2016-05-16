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
			for(int i = 0; i < 200000; i++)
			{
				auto entity = m_EntitySystem.createEntity();
				entity.addComponent<Artifact::SpriteRenderer>();
				entity.addComponent<Artifact::AudioSource>();
				entity.addComponent<Artifact::TextComponent>();
			}
		}
		
		/// <summary>
		/// Tests the performance of creating an entity, so that multiple entities can be added in a single frame
		/// without too big of a performance impact
		/// </summary>
		TEST_METHOD(TestCreation)
		{
			Artifact::EntitySystem entitySystem = (m_MessagingSystem);
			long long timeTaken = 0;
			auto entity = entitySystem.createEntity();
			timeTaken += TestUtility::measureNS([&entitySystem, &entity]()
			{
				entitySystem.addComponent<Artifact::AudioSource>(entity);
				entitySystem.addComponent<Artifact::SpriteRenderer>(entity);
				entitySystem.addComponent<Artifact::TextComponent>(entity);
				entitySystem.addComponent<Artifact::RigidBody2D>(entity);
				entitySystem.addComponent<Artifact::BoxCollider2D>(entity);
			});
			timeTaken -= TestUtility::measureNS([&entitySystem]()
			{
				entitySystem.createEntity();
			});
			std::string output = "Add component test time taken: " + std::to_string(timeTaken / 1e6) + " ms";
			Logger::WriteMessage(output.c_str());
			Assert::IsTrue(timeTaken <= 5e4);
		}
		
		/// <summary>
		/// Tests the performance of fetching the vecotr of components of a single type,
		/// so stray component fetches and the fetches themselves do not bottleneck iteration
		/// </summary>
		TEST_METHOD(TestComponentByTypeFetch)
		{
			auto timeTaken = TestUtility::measureNS([this]
			{
				performComponentTypeFetch();
			});
			Assert::IsTrue(timeTaken <= 1e3);
		}
		
		/// <summary>
		/// Tests the performance of iterating over a single component type, to make sure a reasonable amount of components 
		/// (200000) of a single type does not bottleneck a game 
		/// </summary>
		TEST_METHOD(TestIterationSingleType)
		{
			auto timeTaken = TestUtility::measureNS([this]
			{
				for(auto component : m_EntitySystem.getComponentsOfType<Artifact::SpriteRenderer>())
				{
					component->Color = Artifact::Color::White;
					component->Width = 100.0f;
					component->Height *= 1.0001f;
				}
			});
			timeTaken -= TestUtility::measureNS([this]
			{
				performComponentTypeFetch();
			});
			std::string output = "Single type iteration test time taken: " +
				std::to_string(timeTaken / 1e6) + " ms";
			Logger::WriteMessage(output.c_str());
			Assert::IsTrue(timeTaken <= 2e6);
		}
		
		/// <summary>
		/// Tests the performance of iterating over a single component type, to make sure a reasonable amount of components 
		/// (200000) of multiple types is not noticeably slower than of single component type
		/// </summary>
		TEST_METHOD(TestIterationMultiType)
		{
			auto timeTaken = TestUtility::measureNS([this]
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
			});
			timeTaken -= TestUtility::measureNS([this]
			{
				performComponentTypeFetch();
			}) * 3;
			std::string output = "Multitype test time taken: " + 
				std::to_string(timeTaken / 1e6) + " ms";
			Logger::WriteMessage(output.c_str());
			Assert::IsTrue(timeTaken <= 6e6);
		}
		
		/// <summary>
		/// Performs a simple component fetch for benchmarking purposes
		/// </summary>
		void performComponentTypeFetch()
		{
			m_EntitySystem.getComponentsOfType<Artifact::Transform>();
		}
	};
}