#include "Renderable.h"



Renderable::Renderable(Shader& shaderProgram_)
{
	this->shaderProgram_ = shaderProgram_;
	this->initRenderData();
}

void Renderable::initRenderData()
{
	// configure VAO/VBO
	unsigned int VBO;
	float vertices[] = {
		// pos          // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Renderable::DrawTextureQuad2D(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
	// prepare transformations
	this->shaderProgram_.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shaderProgram_.SetMatrix4("model", model);
	this->shaderProgram_.SetVector3f("Color", color);
	
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();
	
	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Renderable::DrawBackground() // glm::vec3 color
{
	glm::vec2 position;
	glm::vec2 size;
	size.x = 2.0f;
	size.y = 2.0f;
	position.x = -1.0f;
	position.y = -1.0f;
	float width, height;

	width = 1.0f;
	height = 1.0f;

	this->shaderProgram_.Use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final //translation happens; reversed order)
	//
	//model = glm::translate(model, glm::vec3(-0.0f, -0.0f, 0.0f)); // move origin of rotation to center of quad
	//model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
	//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back
	//
	model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale
	//
	this->shaderProgram_.SetMatrix4("model", model);

	// render textured quad
	//this->shader.SetVector3f("spriteColor", color);

	//glActiveTexture(GL_TEXTURE0);
	//texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


/*
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
	//VAO1.Unbind();
	//VBO1.Unbind();
	//EBO1.Unbind();
	
	shaderProgram.Delete();

    
};

void Renderable::DrawTextureQuad2D(float x, float y, float width, float height, const char* ImgPath) {

	GLfloat vertices[] =
	{

		//  COORDINATES						 // TEXTURE COORDINATES
		//  X          Y            Z
			x,         y,           0.1f,	 0.0f, 0.0f,
			x,         y + height,  0.1f,	 0.0f, 1.0f,
			x + width, y + height,  0.1f,	 1.0f, 1.0f,
			x + width, y,           0.1f,	 1.0f, 0.0f
	};

	Shader shaderProgram("A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/texture.vert", "A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/texture.frag"); //  create shader with vertexShader and fragmentShader
	VAO VAO1;										// create vertex array
	VAO1.Bind();									// bind vertex array 

	VBO VBO1(vertices, sizeof(vertices));			// create vertex buffer
	EBO EBO1(quad_indices, sizeof(quad_indices));			    // create index buffer

	//VBO1.Bind();
	//EBO1.Bind();
	//	link VBO to VAO
	//	1 VBO, 2 GLuint layout, 3 GLuint numComponents, 4 GLenum type, 5 GLsizeiptr stride, 6 void* offset
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);							// link position vertices
	VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(GL_FLOAT)));							// link texture vertices

	Texture tex0(ImgPath, GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	tex0.Bind();
	tex0.texUnit(shaderProgram, "tex0", 0);
	
	// model, view, projection
	//glm::mat4 model = glm::mat4(1.0f);			// init identity matrices
	//glm::mat4 view = glm::mat4(1.0f);			// ''
	orthographic = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 1.0f);

	// get uniform locations 
	orthoLoc = glGetUniformLocation(shaderProgram.ID, "orthographic");

	// 1 - uni location, 2 - no. of matrices, 3 - transpose, 4 - ptr
	glUniformMatrix4fv(orthoLoc, 1, GL_FALSE, glm::value_ptr(orthographic));	// assign uniform

	shaderProgram.Activate();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// Unbind to prevent modifying
	//VAO1.Unbind();
	//VBO1.Unbind();
	//EBO1.Unbind();
	//tex0.Unbind();

	shaderProgram.Delete();


}

void Renderable::DrawTextureQuad2D(float x, float y, float width, float height, const char* ImgPath, float scale_x, float scale_y) {

	GLfloat vertices[] =
	{

		//  COORDINATES								// TEXTURE COORDINATES
		//  X          Y            Z
			x,         y,           0.1f,			0.0f,				0.0f,
			x,         y + height,  0.1f,			0.0f,				1.0f * scale_y,
			x + width, y + height,  0.1f,			1.0f * scale_x,		1.0f * scale_y,
			x + width, y,           0.1f,			1.0f * scale_x,		0.0f
	};

	Shader shaderProgram("A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/texture.vert", "A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/texture.frag"); //  create shader with vertexShader and fragmentShader
	VAO VAO1;										// create vertex array
	VAO1.Bind();									// bind vertex array 

	VBO VBO1(vertices, sizeof(vertices));			// create vertex buffer
	EBO EBO1(quad_indices, sizeof(quad_indices));			    // create index buffer

	//VBO1.Bind();
	//EBO1.Bind();
	//	link VBO to VAO
	//	1 VBO, 2 GLuint layout, 3 GLuint numComponents, 4 GLenum type, 5 GLsizeiptr stride, 6 void* offset
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);							// link position vertices
	VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(GL_FLOAT)));							// link texture vertices

	Texture tex0(ImgPath, GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	tex0.Bind();
	tex0.texUnit(shaderProgram, "tex0", 0);

	// model, view, projection
	//glm::mat4 model = glm::mat4(1.0f);			// init identity matrices
	//glm::mat4 view = glm::mat4(1.0f);			// ''
	orthographic = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 1.0f);

	// get uniform locations 
	orthoLoc = glGetUniformLocation(shaderProgram.ID, "orthographic");

	// 1 - uni location, 2 - no. of matrices, 3 - transpose, 4 - ptr
	glUniformMatrix4fv(orthoLoc, 1, GL_FALSE, glm::value_ptr(orthographic));	// assign uniform

	shaderProgram.Activate();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// Unbind to prevent modifying
	//VAO1.Unbind();
	//VBO1.Unbind();
	//EBO1.Unbind();
	//tex0.Unbind();

	shaderProgram.Delete();


}

void Renderable::DrawImGui(int player1Score, int player2Score) {
	
	ImGui::GetIO().FontGlobalScale = 2.0f;
	ImGui::GetStyle().AntiAliasedLines = true;
	ImGui::GetStyle().AntiAliasedFill = true;
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


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

void Renderable::DrawImGuiText(const std::string& Text, unsigned int x, unsigned int y, float fontSize, unsigned int Alignment) {

	ImGui::GetIO().FontGlobalScale = fontSize;
	ImGui::GetStyle().AntiAliasedLines = true;
	ImGui::GetStyle().AntiAliasedFill = true;
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//
	
	// Display scores in the middle
	//ImVec2 Pos = ImVec2(x, y);
	//ImGui::SetNextWindowPos(Pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));

	ImVec2 Pos = ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.05f);
	
	// Alignment - 0 (x, y values), 1 (Left aligned, y), 2 (center aligned, y), 3 (Right aligned, y), 4 (Full Centered)
	if (Alignment == 0) {
		Pos = ImVec2(x, y);
	}
	if (Alignment == 2)
		Pos = ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, y);
	if (Alignment == 4)
		Pos = ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);

	ImGui::SetNextWindowPos(Pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	
	// Set the width of the window to be the window width
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 100), ImGuiCond_Always);
	
	
	// Create a window to display scores
	ImGui::Begin("Text", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground);
	
	// Display Player 1's score on the left
	ImVec2 player1TextSize = ImGui::CalcTextSize(Text.c_str());
	ImGui::SetCursorPos(ImVec2(Pos.x - player1TextSize.x/2, 70));
	ImGui::Text(Text.c_str());

	ImGui::End();

	//// Render ImGui
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderable::DrawCuboid(glm::vec3 pos, glm::vec3 dimensions) {
	GLfloat vertices[] =
	{
		//  COORDINATES	x,y,z													// TEXTURE COORDINATES

		pos.x,					pos.y,					pos.z,						0.0f, 0.0f,
		pos.x + dimensions.x,	pos.y,					pos.z,						1.0f, 0.0f,
		pos.x + dimensions.x,	pos.y + dimensions.y,	pos.z,						1.0f, 1.0f,
		pos.x + dimensions.x,	pos.y + dimensions.y,	pos.z,						1.0f, 1.0f,
		pos.x,					pos.y + dimensions.y,	pos.z,						0.0f, 1.0f,
		pos.x,					pos.y,					pos.z,						0.0f, 0.0f,

		pos.x,					pos.y,					pos.z + dimensions.z,		0.0f, 0.0f,
		pos.x + dimensions.x,	pos.y,					pos.z + dimensions.z,		1.0f, 0.0f,
		pos.x + dimensions.x,	pos.y + dimensions.y,	pos.z + dimensions.z,		1.0f, 1.0f,
		pos.x + dimensions.x,	pos.y + dimensions.y,	pos.z + dimensions.z,		1.0f, 1.0f,
		pos.x,					pos.y + dimensions.y,	pos.z + dimensions.z,		0.0f, 1.0f,
		pos.x,					pos.y,					pos.z + dimensions.z,		0.0f, 0.0f,

		pos.x,					pos.y + dimensions.y,	pos.z + dimensions.z,		1.0f, 0.0f,
		pos.x,					pos.y + dimensions.y,	pos.z,						1.0f, 1.0f,
		pos.x,					pos.y,					pos.z,						0.0f, 1.0f,
		pos.x,					pos.y,					pos.z,						0.0f, 1.0f,
		pos.x,					pos.y,					pos.z + dimensions.z,		0.0f, 0.0f,
		pos.x,					pos.y + dimensions.y,	pos.z + dimensions.z,		1.0f, 0.0f,

		pos.x + dimensions.x,	pos.y + dimensions.y,	pos.z + dimensions.z,		1.0f, 0.0f,
		pos.x + dimensions.x,	pos.y + dimensions.y,	pos.z,						1.0f, 1.0f,
		pos.x + dimensions.x,	pos.y,					pos.z,						0.0f, 1.0f,
		pos.x + dimensions.x,	pos.y,					pos.z,						0.0f, 1.0f,
		pos.x + dimensions.x,	pos.y,					pos.z + dimensions.z,		0.0f, 0.0f,
		pos.x + dimensions.x,	pos.y + dimensions.y,	pos.z + dimensions.z,		1.0f, 0.0f,

		pos.x,					pos.y,					pos.z,						0.0f, 1.0f,
		pos.x + dimensions.x,	pos.y,					pos.y,						1.0f, 1.0f,
		pos.x + dimensions.x,	pos.y,					pos.z + dimensions.z,		1.0f, 0.0f,
		pos.x + dimensions.x,	pos.y,					pos.z + dimensions.z,		1.0f, 0.0f,
		pos.x,					pos.y,					pos.z + dimensions.z,		0.0f, 0.0f,
		pos.x,					pos.y,					pos.z,						0.0f, 1.0f,

		pos.x,					pos.y + dimensions.y,	pos.z,						0.0f, 1.0f,
		pos.x + dimensions.x,	pos.y + dimensions.y,	pos.z,						1.0f, 1.0f,
		pos.x + dimensions.x,	pos.y + dimensions.y,	pos.z + dimensions.z,		1.0f, 0.0f,
		pos.x + dimensions.x,	pos.y + dimensions.y,	pos.z + dimensions.z,		1.0f, 0.0f,
		pos.x,					pos.y + dimensions.y,	pos.z + dimensions.z,		0.0f, 0.0f,
		pos.x,					pos.y + dimensions.y,	pos.z,						0.0f, 1.0f

	};
}

void Renderable::Draw3DScene() {

	
}

*/