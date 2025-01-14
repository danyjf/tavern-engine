#include <Tavern/Scene/Entity.h>
#include <Tavern/Events/EventListener.h>
#include <Tavern/Events/KeyEvent.h>
#include <Tavern/Events/MouseEvent.h>
#include <glm/glm.hpp>

using namespace Tavern;

class Cube;

class Player : public Entity
{
public:
	std::vector<Cube*> m_Cubes;

	Player(Engine& engine);
	~Player();

	void Update() override;

	void OnKeyPressed(const std::shared_ptr<KeyPressedEvent>& event);
	void OnMouseMoved(const std::shared_ptr<MouseMovedEvent>& event);
	void OnMouseScrolled(const std::shared_ptr<MouseScrolledEvent>& event);
	void OnMouseButtonPressed(const std::shared_ptr<MouseButtonPressedEvent>& event);

private:
	CameraComponent* m_Camera;
	float m_Speed;
	glm::vec2 m_LastMousePosition;
	float m_CameraSensitivity;
	float m_Zoom;
	EventListener<KeyPressedEvent> m_KeyPressed;
	EventListener<MouseMovedEvent> m_MouseMoved;
	EventListener<MouseScrolledEvent> m_MouseScrolled;
	EventListener<MouseButtonPressedEvent> m_MouseButtonPressed;
};
REGISTER_ENTITY(Player);
