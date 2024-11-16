#include <Tavern/Scene/Entity.h>

namespace Tavern
{
	class MeshComponent;
}

class Backpack : public Tavern::Entity
{
public:
	Backpack(Tavern::Engine& engine);

private:
	Tavern::MeshComponent* m_Mesh;
};
