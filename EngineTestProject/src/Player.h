#include <Tavern/Scene/Entity.h>
#include <Tavern/Events/EventListener.h>
#include <Tavern/Events/KeyEvent.h>
#include <Tavern/Events/MouseEvent.h>
#include <glm/glm.hpp>

namespace Tavern
{
	class CameraComponent;
}

class Cube;

class Player : public Tavern::Entity
{
public:
	std::vector<Cube*> m_Cubes;

	Player(Tavern::Engine& engine);
	~Player();

	void Update() override;

	void OnKeyPressed(const std::shared_ptr<Tavern::KeyPressedEvent>& event);
	void OnMouseMoved(const std::shared_ptr<Tavern::MouseMovedEvent>& event);
	void OnMouseScrolled(const std::shared_ptr<Tavern::MouseScrolledEvent>& event);
	void OnMouseButtonPressed(const std::shared_ptr<Tavern::MouseButtonPressedEvent>& event);

private:
	Tavern::CameraComponent* m_Camera;
	float m_Speed;
	glm::vec2 m_LastMousePosition;
	float m_CameraSensitivity;
	float m_Zoom;
	Tavern::EventListener<Tavern::KeyPressedEvent> m_KeyPressed;
	Tavern::EventListener<Tavern::MouseMovedEvent> m_MouseMoved;
	Tavern::EventListener<Tavern::MouseScrolledEvent> m_MouseScrolled;
	Tavern::EventListener<Tavern::MouseButtonPressedEvent> m_MouseButtonPressed;
};
