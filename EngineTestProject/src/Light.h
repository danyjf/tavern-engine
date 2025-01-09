#include <Tavern/Scene/Entity.h>
#include <glm/glm.hpp>

using namespace Tavern;

class Light : public Entity
{
public:
	Light(Engine& engine);

	void Update() override;

private:
	MeshComponent* m_Mesh;
	LightComponent* m_Light;
	glm::vec3 m_StartPosition;
};
REGISTER_ENTITY(Light);
