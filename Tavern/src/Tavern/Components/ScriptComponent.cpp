#include <nlohmann/json.hpp>

#include "Tavern/Components/ScriptComponent.h"
#include "Tavern/Core/Engine.h"

namespace Tavern
{
	ScriptComponent::ScriptComponent(Engine& engine, Entity* owner)
		: Component(engine, owner)
	{
		GetEngine().GetScene().AddScriptComponent(this);
	}

	ScriptComponent::~ScriptComponent()
	{
		GetEngine().GetScene().RemoveScriptComponent(this);
	}

	nlohmann::ordered_json ScriptComponent::ToJson()
	{
		nlohmann::ordered_json json;
		json["script"]["typeName"] = m_TypeName;
		return json;
	}

	void ScriptComponent::FromJson(const nlohmann::ordered_json& data)
	{
	}

	const std::string& ScriptComponent::GetTypeName() const
	{
		return m_TypeName;
	}

	void ScriptComponent::SetTypeName(const std::string& typeName)
	{
		m_TypeName = typeName;
	}
}