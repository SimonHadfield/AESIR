#pragma once

#include <string>
#include <vector>

namespace Hana {

	class Layer
	{
	public:

		// Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnRender() = 0;
		virtual void OnUpdate() = 0;

		// virtual void InsertRenderable();
		// virtual void RemoveRenderable();
		// virtual void ImGuiRender(); // render imgui elements
		
		// const std::string& GetName() const;
	private:
		std::string m_name;
		//std::vector<Renderable*> renderables;
	};

}

