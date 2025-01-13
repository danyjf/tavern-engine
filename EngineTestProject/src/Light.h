#include <Tavern/Scene/Entity.h>
#include <Tavern/Components/ScriptComponent.h>
#include <glm/glm.hpp>

using namespace Tavern;

class Light : public ScriptComponent
{
public:
	Light(Engine& engine, Entity* owner);

	void Update() override;

private:
	MeshComponent* m_Mesh;
	LightComponent* m_Light;
	glm::vec3 m_StartPosition;
};
REGISTER_SCRIPT(Light);
