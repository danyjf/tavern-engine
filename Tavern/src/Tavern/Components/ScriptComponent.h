#pragma once

#include "Tavern/Core/Core.h"
#include "Tavern/Components/Component.h"

namespace Tavern
{
	class TAVERN_API ScriptComponent : public Component
	{
	public:
		ScriptComponent(Engine& engine, Entity* owner);
		virtual ~ScriptComponent();

		ScriptComponent(const ScriptComponent& other) = delete;
		ScriptComponent& operator=(const ScriptComponent& other) = delete;
		ScriptComponent(ScriptComponent&& other) noexcept = delete;
		ScriptComponent& operator=(ScriptComponent&& other) noexcept = delete;

		nlohmann::json ToJson() override;
		void FromJson(const nlohmann::json& data) override;

		virtual void Update() = 0;

		const std::string& GetTypeName() const;
		void SetTypeName(const std::string& className);

	private:
		std::string m_TypeName = "";
	};
}