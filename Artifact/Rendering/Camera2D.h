#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include "../Core/Component.h"
#include "../Core/MessagingSystem.h"
#include "../Core/ComponentHandle.h"
#include "../Transform.h"

namespace Artifact
{
    class Camera2D;
	
	/// <summary>
	/// Sent when there was a change of camera 
	/// </summary>
	/// <seealso cref="Message" />
	class OnCameraChangedMessage : public Message
    {
    private:		
		/// <summary>The new camera that became active</summary>
		ComponentHandle<Camera2D> m_NewCamera;

    public:		
		/// <summary>Initializes a new instance of the <see cref="OnCameraChangedMessage"/> class.</summary>
		/// <param name="a_NewCamera">The new camera</param>
		OnCameraChangedMessage(ComponentHandle<Camera2D> a_NewCamera);
		
		/// <summary>Gets the newly active camera</summary>
		/// <returns>The newly active camera</returns>
		ComponentHandle<Camera2D> getNewCamera() const;
    };
	
	/// <summary>
	/// Represents a/the camera recording the world, from which's position and rotation 
	/// </summary>
	/// <seealso cref="Component" />
	class Camera2D : public Component
    {
    public:
		/// <summary>
		/// The amount pixels used to represent a meter in the game engine
		/// </summary>
        static const int PixelsPerMeter;
    private:		
		/// <summary>The transform fo the camera</summary>
		ComponentHandle<Transform> m_Transform;		
		/// <summary>The projection matrix used to project the vertices to the screen</summary>
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);		
		/// <summary>Whether the camera (view) matrix has been modified since the last frame</summary>
		mutable bool m_Dirty = true;		
		/// <summary>The view projection matrix, that is stored as a cache of the result</summary>
		mutable glm::mat4 m_ViewProjection = glm::mat4(1.0f);		
		/// <summary>The inverse of the view projection matrix, that is stored as a cache of the result</summary>
		mutable glm::mat4 m_InverseViewProjection = glm::mat4(1.0f);
        
    public:		
		/// <summary>Initializes a new instance of the <see cref="Camera2D"/> class.</summary>
		/// <param name="a_GameObject">The gameobject to which it iss attached</param>
		Camera2D(GameObject a_GameObject);
        		
		/// <summary>Gets the view projection matrix of the camera</summary>
		/// <returns>The view projection matrix </returns>
		const glm::mat4& getViewProjection() const;
		
		/// <summary>Gets the inverse view projection matrix of the camera</summary>
		/// <returns>The inverse of the view projection matrix</returns>
		const glm::mat4& getInverseViewProjection() const;
		
		/// <summary>Gets the projection matrix matrix of the camera</summary>
		/// <returns>The projection matrix</returns>
		const glm::mat4& getProjectionMatrix() const;
		
		/// <summary>Screens to world.</summary>
		/// <param name="a_ScreenPosition">The a_ screen position.</param>
		/// <returns></returns>
		glm::vec2 screenToWorld(glm::vec2 a_ScreenPosition) const;

    private:		
		/// <summary>(Re)constructs the view and projection matrices based on the current state of the camera</summary>
		void constructMatrix() const;
		
		/// <summary>(Re)constructs the projection matrix</summary>
		void constructProjectionMatrix();
    };
}