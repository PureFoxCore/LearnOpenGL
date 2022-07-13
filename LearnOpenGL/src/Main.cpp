#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

float triangleVertices[] = 
{
	-0.8f, -0.3f, 0.0f,	// first bottom left
	-0.2f, -0.3f, 0.0f,	// first bottom right
	-0.5f,  0.3f, 0.0f,	// first top center
	
	 0.2, -0.3f, 0.0f,	// second bottom left
 	 0.8, -0.3f, 0.0f,	// second bottom right
	 0.5,  0.3f, 0.0f,	// second top center
};

const char *vertexShaderSource = R"glsl(
#version 330 core

layout (location = 0) in vec3 position;

void main()
{
	gl_Position = vec4(position, 1.0);
}
)glsl";

const char *fragmentShaderSource = R"glsl(
#version 330 core

out vec4 color;

void main()
{
	color = vec4(1.0f, 0.3f, 0.2f, 1.0f);
}
)glsl";

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);
		
		if (key == GLFW_KEY_L)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		if (key == GLFW_KEY_F)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

int main()
{
	glfwSetErrorCallback([](int errorCode, const char *description) { fprintf(stderr, "GLFW Error %i: %s\n", errorCode, description); });

	if (glfwInit() == 0)
	{
		fprintf(stderr, "%s\n", "Failed to initialize glfw!");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == 0)
	{
		fprintf(stderr, "%s\n", "Failed to create window!");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		fprintf(stderr, "%s\n", "Failed to initialize glad!");
		glfwTerminate();
		return 1;
	}

	printf("GL version: %s\n", glGetString(GL_VERSION));
	printf("GL vendor: %s\n", glGetString(GL_VENDOR));

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });
	glfwSetKeyCallback(window, keyCallback);

	const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const unsigned int shaderProgram = glCreateProgram();

	int success;
	char shaderLog[512];

	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, shaderLog);
		fprintf(stderr, "GL Vertex shader compile error %i:%s\n", success, shaderLog);
	}

	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, shaderLog);
		fprintf(stderr, "GL Fragment shader compile error %i:%s\n", success, shaderLog);
	}

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, nullptr, shaderLog);
		fprintf(stderr, "GL shader link error %i:%s\n", success, shaderLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);

	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
