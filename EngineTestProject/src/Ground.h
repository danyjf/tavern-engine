#include <Tavern/Core/Engine.h>
#include <Tavern/Core/Core.h>
#include <Tavern/Scene/Entity.h>
#include <Tavern/Components/ScriptComponent.h>

using namespace Tavern;

class Ground : public ScriptComponent
{
public:
	Ground(Engine& engine, Entity* owner);

	void Update() override;

private:
	MeshComponent* m_Mesh;
};
REGISTER_SCRIPT(Ground);