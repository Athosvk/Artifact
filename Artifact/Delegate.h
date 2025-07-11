#pragma once
#include <vector>
#include <functional>

namespace Artifact
{
	/// <summary>
	/// Represents a collection of function objects that can be called at once
	/// </summary>
	template<typename TFunctionType>
    class Delegate
    {
    private:		
		/// <summary>The subscribed listeners for this delegate</summary>
		std::vector<std::function<TFunctionType>> m_Subscribers;

    public:
		/// <summary>Invokes the function call operator</summary>
		/// <param name="...a_Arguments">The arguments to the function call</param>
		template<typename ...TArguments>
        void operator()(TArguments&&... a_Arguments)
        {
            for(auto& subscriber : m_Subscribers)
            {
                subscriber(std::forward<TArguments>(a_Arguments)...);
            }
        }
		
		/// <summary>Adds a function object to the collection of function objects</summary>
		/// <param name="a_Function">The function to add</param>
		/// <returns>The resulting delegate</returns>
		Delegate& operator+=(std::function<TFunctionType> a_Function)
        {
            m_Subscribers.push_back(a_Function);
            return *this;
        }
    };
}
