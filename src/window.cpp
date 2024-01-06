#include "window.h"
#include "logger.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <future>

Window::Window()
{

}


Window::~Window()
{
    glfwTerminate();
    Logger::message("Done window clear");
}

int Window::init()
{
    if (!glfwInit()) {
		Logger::error("Cannot init GLFW!");
		return 1;
	}

    window = glfwCreateWindow(
		this->width,
		this->height,
		this->title.c_str(),
		NULL,
		NULL
	);

	if (window == NULL) {
		Logger::error("Cannot create GLFW window!");
		return 2;
	}


	auto resized_callback = [](GLFWwindow* w, int width, int height)
    {
        static_cast<Window*>(glfwGetWindowUserPointer(w))->resized(width, height);
    };

	auto key_pressed_callback = [](GLFWwindow* w, int key, int scancode, int action, int mods)
    {
        static_cast<Window*>(glfwGetWindowUserPointer(w))->keyPresed(key, scancode, action, mods);
    };

	auto mouse_button_callback = [](GLFWwindow* w, int button, int action, int mods)
    {
        static_cast<Window*>(glfwGetWindowUserPointer(w))->buttonClicked(button, action, mods);
    };

	auto scroll_callback = [](GLFWwindow* w, double xoffset, double yoffset)
	{
		static_cast<Window*>(glfwGetWindowUserPointer(w))->buttonScrolled(xoffset, yoffset);
	};

	auto mouse_callback = [](GLFWwindow* w, double xposIn, double yposIn)
	{
		static_cast<Window*>(glfwGetWindowUserPointer(w))->mouseMoved(xposIn, yposIn);
	};

	glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewExperimental = GL_TRUE;
	glfwSetWindowSizeCallback(window, resized_callback);
	glfwSetKeyCallback(window, key_pressed_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glewInit();

	Logger::message("Context created.");

	return 0;
}


/* Listeners */

void Window::keyPresed(int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS) return;

	auto p = currentScene.cameraPosition;
	const float delta = 0.25f * 3;


	// Вверх/вниз
	if (key == GLFW_KEY_UP || key == GLFW_KEY_W) {
		// currentScene.cameraPosition = glm::vec3(p.x, p.y, p.z - delta);
		currentScene.cameraPosition += delta * currentScene.cameraFront;
	}
	else if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S) {
		// currentScene.cameraPosition = glm::vec3(p.x, p.y, p.z + delta);
		currentScene.cameraPosition -= delta * currentScene.cameraFront;
	}

	// Влево/вправо
	else if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
		// currentScene.cameraPosition = glm::vec3(p.x - delta, p.y, p.z);
		currentScene.cameraPosition -= glm::normalize(glm::cross(currentScene.cameraFront, currentScene.cameraUp)) * delta;
	}
	else if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) {
		// currentScene.cameraPosition = glm::vec3(p.x + delta, p.y, p.z);
		currentScene.cameraPosition += glm::normalize(glm::cross(currentScene.cameraFront, currentScene.cameraUp)) * delta;
	}

	// Вперед/назад
	else if (key == GLFW_KEY_SPACE) {
		currentScene.cameraPosition = glm::vec3(p.x, p.y + delta, p.z);
	}
	else if (key == GLFW_KEY_RIGHT_SHIFT || key == GLFW_KEY_LEFT_SHIFT) {
		currentScene.cameraPosition = glm::vec3(p.x, p.y - delta, p.z);
	}
}

void Window::buttonClicked(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
		if(action == GLFW_PRESS){
			cameraMovable = !cameraMovable;
			if(!cameraMovable)
				cameraFirstMouse = true;
		}
    }
}

void Window::buttonScrolled(double xoffset, double yoffset)
{
	cameraFov -= (float)yoffset;
	if (cameraFov < 0.04f)
		cameraFov = 0.04f;
	if (cameraFov > 90.0f)
		cameraFov = 90.0f;
}

void Window::mouseMoved(double xposIn, double yposIn)
{
	if(!cameraMovable) return;

	if (cameraFirstMouse)
	{
		cameraCursorLastX = xposIn;
		cameraCursorLastY = yposIn;
		cameraFirstMouse = false;
	}

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	float xoffset = xpos - cameraCursorLastX;
	float yoffset = cameraCursorLastY - ypos;
	cameraCursorLastX = xpos;
	cameraCursorLastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	cameraYaw += xoffset;
	cameraPitch += yoffset;

	if (cameraPitch > 89.0f)
		cameraPitch = 89.0f;
	if (cameraPitch < -89.0f)
		cameraPitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
	front.y = sin(glm::radians(cameraPitch));
	front.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
	this->currentScene.cameraFront = front; //glm::normalize(front);
}




void Window::resized(int width, int height)
{
	this->width = width;
	this->height = height;
}

/* Setters */

void Window::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

void Window::setTitle(std::string title)
{
    this->title = title;
}

void Window::setScene(Scene scene)
{
	this->currentScene = scene;
}


/* Extra methods */

void Window::enableExtentions()
{
	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);
	// glFrontFace(GL_CCW);
	// glCullFace(GL_BACK);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// glLineWidth(3);
	// glEnable(GL_LINE_SMOOTH);
}

void Window::requestPrepareCurrentScene()
{
	this->preparingAssets = true;
	this->preparingAssetsFailed = false;
	this->loadingProgress = 0.0f;

	assetsFuture = std::async(std::launch::async, &Window::prepareAssetsForCurrentScene, this);
}

void Window::prepareAssetsForCurrentScene()
{
	Logger::message("Preparing making assets...");

	this->preparingAssets = true;
	this->preparingAssetsFailed = false;
	this->loadingProgress = 0.0f;

	Logger::message("Scanning assets...");


	std::vector<SceneObject>& objs = this->currentScene.sceneObjects;
	int total = 0;

	// Подсчет общего количества объектов для компиляции и загрузки
	for(SceneObject& obj : objs) {

		if(obj.hasModelRequired())
			total++;

		if(obj.material.hasRequiredTextureName())
			total++;

		if(obj.material.hasRequiredSpecularMapTextureName())
			total++;
	}

	// Скайбокс
	total++;

	Logger::message("Total assets: " + std::to_string(total));
	Logger::message("Making assets...");

	// Импорт моделей для объектов (в дальнейшем необходимо скомпилировать программы)
	int i = 1;
	for(SceneObject& obj : objs) {

		if(obj.hasModelRequired()) {
			Model& model = assetManager.getModel(obj.getModelName());
			model.importModel();
			i++;
		}

		this->loadingProgress = (float)i / total;


		// Загрузка материала

		if(obj.material.hasRequiredTextureName()){
			Texture& t = assetManager.getTexture(obj.material.requiredTextureName);
			t.import();
			TextureStatus status = t.getStatus();
			if(status.failed){
				this->preparingAssetsFailed = true;

				Logger::error("requiredTextureName loading error. "
				"Details: " + status.errorText);

				return;
			}
			i++;
		}

		this->loadingProgress = (float)i / total;

		if(obj.material.hasRequiredSpecularMapTextureName()){
			Texture& t = assetManager.getTexture(obj.material.requiredSpecularMapTextureName);
			t.import();
			TextureStatus status = t.getStatus();
			if(status.failed){
				this->preparingAssetsFailed = true;

				Logger::error("requiredSpecularMapTextureName loading error. "
				"Details: " + status.errorText);

				return;
			}
			i++;
		}

		this->loadingProgress = (float)i / total;

	}

	// Скайбокс
	CubeMap& cubeMap = currentScene.cubeMap;
	cubeMap.importTextures();
	TextureStatus status = cubeMap.getTextureStatus();
	if(status.failed){
		this->preparingAssetsFailed = true;

		Logger::error("CubeMap importing error. "
		"Details: " + status.errorText);

		return;
	}
	i++;
	this->loadingProgress = (float)i / total;

	// Готово
	this->loadingProgress = 0.0f;
	this->preparingAssets = false;

	Logger::message("Assets prepared.");
}

void Window::compileShaderProgrammes()
{
	// Компилируем только один раз и в том же потоке, где и OpenGL приложение
	if(!this->switchingToSceneForFirstTime) return;
	this->switchingToSceneForFirstTime = false;

	std::vector<SceneObject>& objs = this->currentScene.sceneObjects;

	Logger::message("Compiling shaders and linking textures...");

	// Компиляция и загрузка текстур объектов сцены
	for(SceneObject& obj : objs) {

		if(obj.hasModelRequired()){
			// Model& model = assetManager.getModel(obj.getModelName());
			Model& model = assetManager.models[obj.getModelName()];
			obj.applyModel(model);
			// std::cout << "asdsdaasd: " << model.getModelPath() << "\n";
		}

		for(Program& program : obj.programmes){
			program.compile();

			// std::cout << "ASOKODKOASDKO: " << obj.asd << " " << obj.test1 << " - " << program.getId() << "\n";

			CompileStatus status = program.getCompileStatus();
			if(status.failed){
				this->preparingAssetsFailed = true;
				Logger::error("Program error. "
				"Details: " + status.errorText);

				return;
			}
		}

		// Все связанные текстуры с объектом (лишнее)

		/*
		for(Texture& texture : obj.textures){
			texture.load();
			TextureStatus status = texture.getStatus();
			if(status.failed){
				this->preparingAssetsFailed = true;

				Logger::error("Texture loading error. "
				"Details: " + status.errorText);

				return;
			}
			done++;
			this->loadingProgress = (float)done / total;
		}
		*/

		// TODO: убрать дублирование кода (?)

		std::string textName;

		// Текстура материала
		textName = obj.material.requiredTextureName;
		Texture& materialTexture = assetManager.getTexture(textName); // obj.material.texture;
		// TextureStatus status = materialTexture.getStatus();
		// if(status.failed){
		// 	this->preparingAssetsFailed = true;
  //
		// 	Logger::error("MaterialTexture loading error. "
		// 	"Details: " + status.errorText);
  //
		// 	return;
		// }
		materialTexture.load();
		obj.material.texture = materialTexture;

		// Текстура карты отражений
		textName = obj.material.requiredSpecularMapTextureName;
		Texture& materialSpecTexture = assetManager.getTexture(textName); // obj.material.specularMapTexture;
		// status = materialSpecTexture.getStatus();
		// if(status.failed){
		// 	this->preparingAssetsFailed = true;
  //
		// 	Logger::error("MaterialSpecTexture loading error. "
		// 	"Details: " + status.errorText);
  //
		// 	return;
		// }
		materialSpecTexture.load();
		obj.material.specularMapTexture = materialSpecTexture;

	}

	// Загрузка скайбокса
	CubeMap& cubeMap = currentScene.cubeMap;
	cubeMap.load();
	CompileStatus status = cubeMap.getCompileStatus();
	if(status.failed){
		this->preparingAssetsFailed = true;

		Logger::error("CubeMap loading error. "
		"Details: " + status.errorText);

		return;
	}


	this->preparingAssetsFailed = false;
	this->loadingProgress = 0.0f;
	this->preparingAssets = false;

	Logger::message("Shaders compiled.");
}



/* Render loop */

void Window::render()
{
	this->enableExtentions();

	while (!glfwWindowShouldClose(window)) {
		glViewport(0, 0, this->width, this->height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(!this->preparingAssets && !this->preparingAssetsFailed) {
			this->compileShaderProgrammes();
			currentScene.render(this->cameraFov);
		} else {
			this->preparingAssetsRender();
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

}


void Window::preparingAssetsRender()
{
	float l = this->loadingProgress;



	// Если ошибка, то квадрат красный
	if(this->preparingAssetsFailed) {
		glClearColor(0.2f, 0, 0, 1.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
	} else {
		glClearColor(0, 0, 0, 1.0f);
		glColor3f(1.0f, 1.0f, 0.0f);
	}

	if(l < 0.05) l = 0.05;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Рисуем квадрат загрузки
	glBegin(GL_QUADS);
		glVertex2f(-l, l);
		glVertex2f(-l, -l);
		glVertex2f(l, -l);
		glVertex2f(l, l);
	glEnd();

}



