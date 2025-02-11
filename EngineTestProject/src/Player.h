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

	void OnKeyPressed(const std::shared_ptr<Event>& event);
	void OnMouseMoved(const std::shared_ptr<Event>& event);
	void OnMouseScrolled(const std::shared_ptr<Event>& event);
	void OnMouseButtonPressed(const std::shared_ptr<Event>& event);

private:
	CameraComponent* m_Camera;
	float m_Speed;
	glm::vec2 m_LastMousePosition;
	float m_CameraSensitivity;
	float m_Zoom;
	EventListener m_KeyPressedListener;
	EventListener m_MouseMovedListener;
	EventListener m_MouseScrolledListener;
	EventListener m_MouseButtonPressedListener;
};
REGISTER_SCRIPT(Player);
