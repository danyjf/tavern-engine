#include <Tavern/Scene/Entity.h>
#include <Tavern/Events/KeyEvent.h>
#include <Tavern/Events/MouseEvent.h>
#include <Tavern/Events/EventListener.h>
#include <glm/glm.hpp>

using namespace Tavern;

class Cube;

class Player : public ScriptComponent
{
public:
	Player(Engine& engine, Entity* owner);

	std::vector<Cube*> m_Cubes;

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
	EventListener<KeyPressedEvent> m_KeyPressedListener;
	EventListener<MouseMovedEvent> m_MouseMovedListener;
	EventListener<MouseScrolledEvent> m_MouseScrolledListener;
	EventListener<MouseButtonPressedEvent> m_MouseButtonPressedListener;
};
REGISTER_SCRIPT(Player);
