#ifndef Inputs_HPP
#define Inputs_HPP

#include <glm/glm.hpp>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>

namespace ctx {

#define MOUSE_INPUT_SIZE 8
#define KEYS_INPUT_SIZE 512

class Inputs {
   private:
    Inputs();

   public:
    enum KEYBOARD { QWERTY, AZERTY };
    static KEYBOARD keyboard;

    static glm::vec2 mouse_position;
    static glm::vec2 mouse_velocity;
    static glm::vec2 mouse_acceleration;
    static double mouse_scroll;
    static glm::vec2 pressed_mouse_position[MOUSE_INPUT_SIZE];
    static glm::vec2 pressed_mouse_diff[MOUSE_INPUT_SIZE];

    static bool pressed_mouse[MOUSE_INPUT_SIZE];
    static bool current_mouse[MOUSE_INPUT_SIZE];
    static bool released_mouse[MOUSE_INPUT_SIZE];

    static bool pressed_keys[KEYS_INPUT_SIZE];
    static bool current_keys[KEYS_INPUT_SIZE];
    static bool released_keys[KEYS_INPUT_SIZE];

    static void ResetInputs();
    static void ResetKeyboardInputs();
    static void ResetMouseInputs();

    static void AssignKeyboard(KEYBOARD i_keyboard);

    static int ConvertKey(int key);
    static int ConvertKeyQuerty(int key);
    static int ConvertKeyAzerty(int key);

    static void HandleKeyboardInputs(int key, int action);
    static void HandleMouseInputs(int button, int action);
    static void HandleCursorPos(double xpos, double ypos);
    static void HandleMouseScroll(double xoffset, double yoffset);
    static void HandleMousePosition();

    static bool KeyPressed(int key);
    static bool KeyDown(int key);
    static bool KeyReleased(int key);

    static bool MousePressed(int key);
    static bool MouseDown(int key);
    static bool MouseReleased(int key);

    static bool KeyPressed(std::string key);
    static bool KeyDown(std::string key);
    static bool KeyReleased(std::string key);

    static bool MousePressed(std::string key);
    static bool MouseDown(std::string key);
    static bool MouseReleased(std::string key);

    static double MouseScroll();
    static glm::vec2 MousePosition();
    static glm::vec2 MouseVelocity();
    static glm::vec2 MouseAcceleration();
    static glm::vec2 PressedMousePosition(int button);
    static glm::vec2 PressedMouseDiff(int button);

    static std::unordered_map<std::string, std::string> QWERTY_TO_AZERTY;
};

}  // namespace ctx
#endif