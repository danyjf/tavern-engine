#include <Tavern/Scene/Entity.h>
#include <Tavern/Components/ScriptComponent.h>

using namespace Tavern;

class Backpack : public ScriptComponent
{
public:
	Backpack(Engine& engine, Entity* owner);

	void Update() override;

private:
	MeshComponent* m_Mesh;
};
REGISTER_SCRIPT(Backpack);
