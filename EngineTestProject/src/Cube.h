#include <Tavern/Scene/Entity.h>

using namespace Tavern;

class Cube : public Entity
{
public:
	Cube(Engine& engine);

private:
	MeshComponent* m_Mesh;
};
REGISTER_ENTITY(Cube);
