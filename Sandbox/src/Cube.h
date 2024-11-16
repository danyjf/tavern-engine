#include <Tavern/Scene/Entity.h>

namespace Tavern
{
	class MeshComponent;
}

class Cube : public Tavern::Entity
{
public:
	Cube(Tavern::Engine& engine);

private:
	Tavern::MeshComponent* m_Mesh;
};
