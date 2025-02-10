#include <Tavern/Scene/Entity.h>
#include <Tavern/Events/KeyEvent.h>
#include <Tavern/Events/MouseEvent.h>
#include <glm/glm.hpp>

using namespace Tavern;

class Cube;

class Player : public ScriptComponent
{
public:
	Player(Engine& engine, Entity* owner);
	~Player();

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
	unsigned long m_KeyPressedListenerID;
	unsigned long m_MouseMovedListenerID;
	unsigned long m_MouseScrolledListenerID;
	unsigned long m_MouseButtonPressedListenerID;
};
REGISTER_SCRIPT(Player);
