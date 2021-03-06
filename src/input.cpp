#include "input.hpp"
#include "utils.hpp"

InputHandler::InputHandler(GLFWwindow* newWindow) { setWindow(newWindow); }
void InputHandler::setWindow(GLFWwindow* newWindow) {currentWindow = newWindow;}

bool InputHandler::keyPressed(int key, GLFWwindow* window) 
{
    return (glfwGetKey(window, key) == GLFW_PRESS);
}

void InputHandler::processInput()
{
    std::vector<int> keysDown; // keep this vector here or it will break

    // process on down callbacks
    for (auto& element : keyDownCallbacks) {
        bool downLastFrame = util::vectorSearch(element.first, lastFrameKeysDown) != -1;
        bool downThisFrame = keyPressed(element.first, currentWindow);

        if (downThisFrame && !downLastFrame) {
            element.second();
            keysDown.push_back(element.first);
        }
    }

    // process while down callbacks
    for (auto& element : keyWhileDownCallbacks) {
        bool downThisFrame = keyPressed(element.first, currentWindow);

        if (downThisFrame) {
            element.second();
            keysDown.push_back(element.first);
        }
    }

    // process on up callbacks
    for (auto& element : keyUpCallbacks) {
        bool downLastFrame = util::vectorSearch(element.first, lastFrameKeysDown) != -1;
        bool downThisFrame = keyPressed(element.first, currentWindow);

        if (!downThisFrame && downLastFrame) {
            element.second();
        }
    }

    // add this frame's keys that were down
    lastFrameKeysDown = keysDown;
}

void InputHandler::registerCallback(int key, std::function<void()> func, InputActionCallbackList* list)
{
    std::pair<int, std::function<void()>> pair(key, func);
    list->push_back(pair);
}