#include "Renderable.h"

void Renderable::DrawBackground() // glm::vec3 color
{
	float x, y, width, height;
	x = -1.0f;
	y = -1.0f;
	width = 2.0f;
	height = 2.0f;

	GLfloat vertices[] =
	{
		//  X          Y            Z
			x,         y,           0.0f,    // 1
			x,         y + height,  0.0f,    // 2
			x + width, y + height,  0.0f,    // 3
			x + width, y,           0.0f     // 4
	};


	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};

	Shader shaderProgram("A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/background.vert", "A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/background.frag"); //  create shader with vertexShader and fragmentShader
	VAO VAO1;										// create vertex array
	VAO1.Bind();									// bind vertex array 

	VBO VBO1(vertices, sizeof(vertices));			// create vertex buffer
	EBO EBO1(indices, sizeof(indices));			    // create index buffer

	//VBO1.Bind();
	//EBO1.Bind();
	//	link VBO to VAO
	//	1 VBO, 2 GLuint layout, 3 GLuint numComponents, 4 GLenum type, 5 GLsizeiptr stride, 6 void* offset
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);							// link position vertices

	shaderProgram.Activate();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// Unbind to prevent modifying
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	shaderProgram.Delete();
}

void Renderable::DrawQuad2D(float x, float y, float width, float height) {

	GLfloat vertices[] =
	{
		//  X          Y            Z
			x,         y,           0.0f,    // 1
			x,         y + height,  0.0f,    // 2
			x + width, y + height,  0.0f,    // 3
			x + width, y,           0.0f     // 4
	};


	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};

	Shader shaderProgram("A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/default.vert", "A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/default.frag"); //  create shader with vertexShader and fragmentShader
	VAO VAO1;										// create vertex array
	VAO1.Bind();									// bind vertex array 

	VBO VBO1(vertices, sizeof(vertices));			// create vertex buffer
	EBO EBO1(indices, sizeof(indices));			    // create index buffer

	//VBO1.Bind();
	//EBO1.Bind();
	//	link VBO to VAO
	//	1 VBO, 2 GLuint layout, 3 GLuint numComponents, 4 GLenum type, 5 GLsizeiptr stride, 6 void* offset
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);							// link position vertices
	
	shaderProgram.Activate();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// Unbind to prevent modifying
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	
	shaderProgram.Delete();

    
};

void Renderable::DrawImGui(int player1Score, int player2Score) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::GetIO().FontGlobalScale = 2.0f;
	ImGui::GetStyle().AntiAliasedLines = true;
	ImGui::GetStyle().AntiAliasedFill = true;

	// Display scores in the middle
	ImVec2 middlePos = ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.05f);
	ImGui::SetNextWindowPos(middlePos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));

	// Set the width of the window to be the window width
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 100), ImGuiCond_Always);


	// Create a window to display scores
	ImGui::Begin("Scores", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground);

	// Display Player 1's score on the left
	std::string player1Text = "Player 1: " + std::to_string(player1Score);
	ImVec2 player1TextSize = ImGui::CalcTextSize(player1Text.c_str());
	ImGui::SetCursorPos(ImVec2(middlePos.x - player1TextSize.x - ImGui::GetWindowSize().x * 0.35f, 70));
	ImGui::Text("Player 1: %d", player1Score);

	// Display Player 2's score on the right
	ImGui::SetCursorPos(ImVec2(middlePos.x + ImGui::GetWindowSize().x * 0.35f, 70));
	ImGui::Text("Player 2: %d", player2Score);

	ImGui::End();

	// Render ImGui
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
