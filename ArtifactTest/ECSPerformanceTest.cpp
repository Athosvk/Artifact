#include "stdafx.h"

#include "CppUnitTest.h"
#include "TestUtility.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArtifactTest
{		
	TEST_CLASS(ECSPerformanceTest)
	{
		Artifact::MessagingSystem m_MessagingSystem;
		Artifact::EntitySystem m_EntitySystem = Artifact::EntitySystem(m_MessagingSystem);

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
			std::string output = "Add component test time taken: " + std::to_string(timeTaken / 1e6) + " ms";
			//Logger::WriteMessage(output.c_str());
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
			auto spriteRenderers = m_EntitySystem.getComponentsOfType<Artifact::SpriteRenderer>();
			auto timeTaken = TestUtility::measureNS([spriteRenderers]
			{
				for(auto component : spriteRenderers)
				{
					component->Width = 100.0f;
					component->Height *= 1.0001f;
					component->Color = Artifact::Color::White;
					component->UVRectangle = component->UVRectangle;
					component->Depth = 1.0f;
					component->Pivot = glm::vec2(0.0f, 0.0f);
				}
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
			auto spriteRenderers = m_EntitySystem.getComponentsOfType<Artifact::SpriteRenderer>();
			auto sources = m_EntitySystem.getComponentsOfType<Artifact::AudioSource>();
			auto text = m_EntitySystem.getComponentsOfType<Artifact::TextComponent>();
			auto timeTaken = TestUtility::measureNS([spriteRenderers, sources, text]
			{
				for(auto component : spriteRenderers)
				{
					component->Height *= 1.0001f;
					component->Color = Artifact::Color::Black;
					component->Depth++;
				}
				for(auto component : sources)
				{
					component->Sound = nullptr;
					component->Volume++;
				}
				for(auto component : text)
				{
					component->Depth = 1.0f;
					component->Color.r *= 1.11f;
					component->Color.g += 1.0f;
				}
			});
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