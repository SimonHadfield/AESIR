#pragma once

#include <string>
#include <vector>

namespace Hana {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnRender();

		// virtual void OnUpdate(TimeElapsed); // update logic

		// virtual void InsertRenderable();
		// virtual void RemoveRenderable();
		// virtual void ImGuiRender(); // render imgui elements
		
		const std::string& GetName() const;
	private:
		std::string name;
		//std::vector<Renderable*> renderables;
	};

}

