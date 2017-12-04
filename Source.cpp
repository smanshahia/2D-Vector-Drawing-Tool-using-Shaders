#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "RectShape.h"
#include "LineShape.h"
#include "CircleShape.h"
#include "PolygonShape.h"
#include <list>
#include <typeinfo.h>
#include <glm\glm.hpp>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

enum SelectedShape
{
	LINE = 0,
	RECTANGLE,
	CIRCLE,
	POLYGON,
	TOGGLE_POLY_ADDITIONS,
	TOGGLE_EDIT_MODE,
	CLEAR_SCREEN,
	MENU_EXIT

};

int selected = RECTANGLE;
bool AddingVertices = false;
bool EditMode = false;
int num = -1;
float mouseX, mouseY = 0;

BaseShape *drawing;
list<BaseShape *> shapelist;

void display()
{

	for (list<BaseShape *>::iterator i = shapelist.begin(); i != shapelist.end(); i++)
	{
		(*i)->drawShape(EditMode);
	}

}

static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
{
	mouseX = (xpos - (SCR_WIDTH/2)) / (SCR_WIDTH /2);
	mouseY = ((SCR_HEIGHT / 2) - ypos) / (SCR_HEIGHT / 2);
}

void cursorEnterCallback(GLFWwindow *window, int entered)
{
	if (entered)
	{
		std::cout << "Entered Window" << std::endl;
	}
	else
	{
		std::cout << "Left window" << std::endl;
	}
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{

		if (EditMode && action == GLFW_PRESS)
		{

			for (list<BaseShape *>::iterator i = shapelist.begin(); i != shapelist.end(); i++)
			{
				if ((*i)->getHotspots(Point2(mouseX, mouseY)) != -1)
				{
					num = (*i)->getHotspots(Point2(mouseX, mouseY));
					drawing = *i;
					break;
				}
			}
		}
		if (action == GLFW_RELEASE && num != -1)
		{
			cout << num << " " << typeid(*drawing).name();
			if (typeid(*drawing) == typeid(LineShape))
			{
				dynamic_cast<LineShape *>(drawing)->setHotspot(Point2(mouseX, mouseY), num);
				num = -1;
			}
			if (typeid(*drawing) == typeid(RectShape))
			{
				dynamic_cast<RectShape *>(drawing)->setHotspot(Point2(mouseX, mouseY), num);
				num = -1;
			}
			if (typeid(*drawing) == typeid(CircleShape))
			{
				dynamic_cast<CircleShape *>(drawing)->setHotspot(Point2(mouseX, mouseY), num);
				num = -1;
			}
			if (typeid(*drawing) == typeid(PolygonShape))
			{
				dynamic_cast<PolygonShape *>(drawing)->setHotspot(Point2(mouseX, mouseY), num);
				num = -1;
			}
		}

		switch (selected)
		{
		case(LINE):
			if (!EditMode)
			{
				if (action == GLFW_PRESS)
				{
					drawing = new LineShape(Point2(mouseX, mouseY), Point2(mouseX, mouseY));
				}
				if (action == GLFW_RELEASE)
				{
					dynamic_cast<LineShape *>(drawing)->setHotspot(Point2(mouseX, mouseY), 1);
					shapelist.push_front(drawing);
				}
			}
			break;
		case(RECTANGLE):

			if (!EditMode)
			{
				if (action == GLFW_PRESS)
				{
					drawing = new RectShape(Point2(mouseX, mouseY), Point2(mouseX, mouseY));
				}
				if (action == GLFW_RELEASE)
				{
					dynamic_cast<RectShape *>(drawing)->setHotspot(Point2(mouseX, mouseY), 1);
					shapelist.push_front(drawing);
				}
			}
			break;
		case(CIRCLE): std::cout << "in circle" << endl;
			if (!EditMode)
			{
				if (action == GLFW_PRESS)
				{
					drawing = new CircleShape(Point2(mouseX, mouseY), Point2(mouseX, mouseY), 30);
				}
				if (action == GLFW_RELEASE)
				{
					dynamic_cast<CircleShape *>(drawing)->setHotspot(Point2(mouseX, mouseY), 1);
					shapelist.push_front(drawing);
				}
			}
			break;
		case(POLYGON):
			if (!EditMode)
			{
				if (action == GLFW_PRESS)
				{
					if (!AddingVertices) // if not continue then create new poly
					{
						drawing = new PolygonShape();
						AddingVertices = true;
						shapelist.push_front(drawing);
					}
					dynamic_cast<PolygonShape *>(drawing)->addHotspot(Point2(mouseX, mouseY));
				}
			}
			break;
		}
	}
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		switch (key)
		{
		case GLFW_KEY_L:
			selected = LINE;
			break;
		case GLFW_KEY_R:
			selected = RECTANGLE;
			break;
		case GLFW_KEY_C:
			selected = CIRCLE;
			break;
		case GLFW_KEY_P:
			selected = POLYGON;
			break;
		case GLFW_KEY_A:
			AddingVertices = !AddingVertices;
			break;
		case GLFW_KEY_E:
			EditMode = !EditMode;
			break;
		case GLFW_KEY_X:
			shapelist.clear();
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			break;
		}
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	if (drawing != nullptr && selected == CIRCLE)
	{
		if (yoffset > 0)
		{
			dynamic_cast<CircleShape *>(drawing)->offsetSegment(1);


		}
		else
		{
			dynamic_cast<CircleShape *>(drawing)->offsetSegment(-1);

		}
	}
}

int main()
{


	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("basic.vs", "basic.fs"); // you can name your shader files however you like

	glfwSetKeyCallback(window, keyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

	glfwSetScrollCallback(window, scrollCallback);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----

		// render
		// ------
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the triangle
		ourShader.use();
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		display();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}