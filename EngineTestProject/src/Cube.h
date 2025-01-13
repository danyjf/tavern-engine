#include <Tavern/Components/ScriptComponent.h>

using namespace Tavern;

class Cube : public ScriptComponent
{
public:
	Cube(Engine& engine, Entity* owner);

	void Update() override;

private:
	MeshComponent* m_Mesh;
};
REGISTER_SCRIPT(Cube);
