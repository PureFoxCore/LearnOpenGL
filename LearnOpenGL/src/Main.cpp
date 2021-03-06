#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

float firstTriangleVertices[] = {
	-0.9f, -0.4f, 0.0f,	 	// first bottom left
	-0.1f, -0.4f, 0.0f,	 	// first bottom right
	-0.5f,  0.4f, 0.0f,	 	// first top center
};

float secondTriangleVertices[] = {
	0.1, -0.4f, 0.0f,  		// second bottom left
	0.9, -0.4f, 0.0f,  		// second bottom right
	0.5,  0.4f,	0.0f, 	 	// second top center
};

const char *vertexShaderSource = R"glsl(
#version 330 core

layout (location = 0) in vec3 position;

void main()
{
	gl_Position = vec4(position, 1.0);
}
)glsl";

const char *fragmentShaderSource1 = R"glsl(
#version 330 core

out vec4 color;

void main()
{
	color = vec4(1.0f, 0.3f, 0.2f, 1.0f);
}
)glsl";

const char *fragmentShaderSource2 = R"glsl(
#version 330 core

out vec4 color;

void main()
{
	color = vec4(1.0f, 1.0f, 0.2f, 1.0f);
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
	const unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	const unsigned int shaderProgram1 = glCreateProgram();
	
	const unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	const unsigned int shaderProgram2 = glCreateProgram();

	int success;
	char shaderLog[512];

	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, nullptr);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, nullptr);

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, shaderLog);
		fprintf(stderr, "GL Vertex shader compile error %i:%s\n", success, shaderLog);
	}

	glCompileShader(fragmentShader1);
	glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader1, 512, nullptr, shaderLog);
		fprintf(stderr, "GL Fragment shader compile error %i:%s\n", success, shaderLog);
	}

	glCompileShader(fragmentShader2);
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader2, 512, nullptr, shaderLog);
		fprintf(stderr, "GL Fragment shader compile error %i:%s\n", success, shaderLog);
	}

	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);

	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);

	glLinkProgram(shaderProgram1);
	glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram1, 512, nullptr, shaderLog);
		fprintf(stderr, "GL shader link error %i:%s\n", success, shaderLog);
	}

	glLinkProgram(shaderProgram2);
	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram1, 512, nullptr, shaderLog);
		fprintf(stderr, "GL shader link error %i:%s\n", success, shaderLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);
	glDeleteShader(fragmentShader2);

	glUseProgram(shaderProgram1);

	unsigned int VBO1, VAO1;
	unsigned int VBO2, VAO2;
	glGenBuffers(1, &VBO1);
	glGenVertexArrays(1, &VAO1);

	glGenBuffers(1, &VBO2);
	glGenVertexArrays(1, &VAO2);

	glBindVertexArray(VAO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangleVertices), firstTriangleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void *) nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangleVertices), secondTriangleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void *) nullptr);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
