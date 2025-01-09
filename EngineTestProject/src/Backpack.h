#include <Tavern/Scene/Entity.h>

using namespace Tavern;

class Backpack : public Entity
{
public:
	Backpack(Engine& engine);

private:
	MeshComponent* m_Mesh;
};
REGISTER_ENTITY(Backpack);
