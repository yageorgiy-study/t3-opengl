#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <future>
#include "scene.h"
#include "./assets/assetmanager.h"
#include "assets/cubemap.h"

class Window
{

public:

    Window();
    ~Window();

    int init();
    void enableExtentions();
    void render();

    void resized(int width, int height);
    void keyPresed(int key, int scancode, int action, int mods);
    void mouseMoved(double xposIn, double yposIn);
    void buttonClicked(int button, int action, int mods);
    void buttonScrolled(double xoffset, double yoffset);

    Scene getScene();

    void setSize(int width, int height);
    void setTitle(std::string title);
    void setScene(Scene scene);
    void requestPrepareCurrentScene();

    AssetManager assetManager;


private:
    void prepareAssetsForCurrentScene();
    void compileShaderProgrammes();
    void preparingAssetsRender();

    int width = 640;
    int height = 480;
    std::string title = "application";

    GLFWwindow* window;
    Scene currentScene;


    std::future<void> assetsFuture;
    bool  preparingAssets = false;
    float loadingProgress = 0.0f;
    bool  preparingAssetsFailed = false;
    bool  switchingToSceneForFirstTime = true;

    /* Camera angle and moving (for global scenes) */
    bool cameraFirstMouse = true;
    bool cameraMovable = false;
    float cameraCursorLastX =  640.0f / 2.0;
    float cameraCursorLastY =  480.0f / 2.0;

    // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float cameraYaw   = -90.0f;
    float cameraPitch =  0.0f;
    float cameraFov   =  45.0f;

};

#endif // WINDOW_H
