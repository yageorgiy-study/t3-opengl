#include "window.h"
#include "scene.h"
#include "logger.h"

int main()
{

	// Сначала создаем окно, чтобы у нас был OpenGL-контекст
	Window window;
	window.setSize(640, 480);
	window.setTitle("OpenGL application");

	if(window.init() != 0)
		return 1;

	// Добавляем модели для загрузки перед отображением сцены
	window.assetManager.addModel("l", "land", "land.obj");
	window.assetManager.addModel("m1", "mushroom", "mushroom.obj");
	window.assetManager.addModel("tree", "christmas-tree", "christmas-tree.obj");
	// window.assetManager.addModel("b", "butterfly", "butterfly.obj");


	// Добавляем текстуры для загрузки перед отображением сцены
	window.assetManager.addTexture("land", "land/land.png");
	window.assetManager.addTexture("m1", "mushroom/mushroom.png");
	window.assetManager.addTexture("m2", "mushroom-1/mushroom1.png");
	window.assetManager.addTexture("m3", "mushroom-2/mushroom2.png");
	window.assetManager.addTexture("tree", "christmas-tree/christmas-tree.png");
	// window.assetManager.addTexture("b", "butterfly/butterfly.png");


	// Инициализируем сцену
	Scene scene;

	// Располагаем объекты на сцене
	SceneObject l;
	// l.material.texture = Texture("land/land.png");
	l.material.requiredTextureName = "land";
	l.requireModel("l");
	l.position = glm::vec3(5, 5, 0);
	scene.addSceneObject(l);

	SceneObject m1;
	// m1.material.texture = Texture("mushroom/mushroom.png");
	m1.material.requiredTextureName = "m1";
	m1.requireModel("m1");
	m1.position = glm::vec3(5, 7.2, 0);
	m1.scale = glm::vec3(0.1f, 0.1f, 0.1f);
	m1.simpleAnimation = true;
	scene.addSceneObject(m1);

	SceneObject m2;
	// m2.material.texture = Texture("mushroom-1/mushroom1.png");
	m2.material.requiredTextureName = "m2";
	m2.requireModel("m1");
	m2.position = glm::vec3(5 + 0.5, 7.2, 0 + 0.5);
	m2.scale = glm::vec3(0.1f, 0.1f, 0.1f);
	m2.simpleAnimation = true;
	scene.addSceneObject(m2);

	SceneObject m3;
	// m3.material.texture = Texture("mushroom-2/mushroom2.png");
	m3.material.requiredTextureName = "m3";
	m3.requireModel("m1");
	m3.position = glm::vec3(5, 7.2, 0 - 0.5);
	m3.scale = glm::vec3(0.15f, 0.15f, 0.15f);
	m3.simpleAnimation = true;
	scene.addSceneObject(m3);

	int r = 8;
	float x0 = 5;
	float y0 = 0.5f;
	float z = 5.2f;
	for(int t = 0; t <= 90; t += 5){

		float x1 = x0 + r * cos(t);
		float y1 = y0 + r * sin(t);

		SceneObject tree;
		// tree.material.texture = Texture("christmas-tree/christmas-tree.png");
		tree.material.requiredTextureName = "tree";
		tree.requireModel("tree");
		tree.position = glm::vec3(x1, z, y1);
		tree.scale = glm::vec3(0.4f, 0.4f, 0.4f);
		scene.addSceneObject(tree);
	}


	// SceneObject tree;
	// tree.material.texture = Texture("christmas-tree/christmas-tree.png");
	// tree.requireModel("tree");
	// tree.position = glm::vec3(5, 7.2, 0 - 0.5);
	// tree.scale = glm::vec3(0.4f, 0.4f, 0.4f);

	// SceneObject b;
	// b.material.requiredTextureName = "b";
	// b.requireModel("b");
	// b.position = glm::vec3(10, 10, 0);
	// b.scale = glm::vec3(0.15f, 0.15f, 0.15f);
	// scene.addSceneObject(b);


	// Устанавливаем текущую сцену
	window.setScene(scene);
	window.requestPrepareCurrentScene();

	// Отрисовываем загрузку, затем сцену
	window.render();

	return 0;
}
