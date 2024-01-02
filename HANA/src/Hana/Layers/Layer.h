#pragma once

#include <string>
#include <vector>

namespace Hana {

	class Layer
	{
	public:

		virtual ~Layer() = default;

		virtual void LoadResources() = 0;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnRender() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnImGuiRender() = 0; // render imgui elements
		
		// const std::string& GetName() const;
	private:
		std::string m_name;
		//std::vector<Renderable*> renderables;
	};

}

