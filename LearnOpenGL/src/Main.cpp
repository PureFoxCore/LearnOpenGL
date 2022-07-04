#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, true);
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

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}