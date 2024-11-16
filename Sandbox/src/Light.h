#include <Tavern/Scene/Entity.h>
#include <glm/glm.hpp>

namespace Tavern
{
	class MeshComponent;
	class LightComponent;
}

class Light : public Tavern::Entity
{
public:
	Light(Tavern::Engine& engine);

	void Update() override;

private:
	Tavern::MeshComponent* m_Mesh;
	Tavern::LightComponent* m_Light;
	glm::vec3 m_StartPosition;
};
