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

    static glm::vec2 m_mouse_position;
    static glm::vec2 m_mouse_velocity;
    static glm::vec2 m_mouse_acceleration;

    static double m_mouse_scroll;
    static glm::vec2 m_pressed_mouse_position[MOUSE_INPUT_SIZE];
    static glm::vec2 m_pressed_mouse_diff[MOUSE_INPUT_SIZE];

    static bool m_pressed_mouse[MOUSE_INPUT_SIZE];
    static bool m_current_mouse[MOUSE_INPUT_SIZE];
    static bool m_released_mouse[MOUSE_INPUT_SIZE];

    static bool m_pressed_keys[KEYS_INPUT_SIZE];
    static bool m_current_keys[KEYS_INPUT_SIZE];
    static bool m_released_keys[KEYS_INPUT_SIZE];

   public:
    enum KEYBOARD { QWERTY, AZERTY };
    static KEYBOARD keyboard;

    static void reset_inputs();
    static void reset_keyboard_inputs();
    static void reset_mouse_inputs();

    static void assign_keyboard(KEYBOARD i_keyboard);

    static int convert_key(int key);
    static int convert_key_querty(int key);
    static int convert_key_azerty(int key);

    static void handle_keyboard_inputs(int key, int action);
    static void handle_mouse_inputs(int button, int action);
    static void handle_cursor_pos(double xpos, double ypos);
    static void handle_mouse_scroll(double xoffset, double yoffset);
    static void handle_mouse_position();

    static bool key_pressed(int key);
    static bool key_down(int key);
    static bool key_released(int key);

    static bool mouse_pressed(int key);
    static bool mouse_down(int key);
    static bool mouse_released(int key);

    static bool key_pressed(std::string key);
    static bool key_down(std::string key);
    static bool key_released(std::string key);

    static bool mouse_pressed(std::string key);
    static bool mouse_down(std::string key);
    static bool mouse_released(std::string key);

    static double mouse_scroll();
    static glm::vec2 mouse_position();
    static glm::vec2 mouse_velocity();
    static glm::vec2 mouse_acceleration();
    static glm::vec2 pressed_mouse_position(int button);
    static glm::vec2 pressed_mouse_diff(int button);

    static std::unordered_map<std::string, std::string> QWERTY_TO_AZERTY;
};

}  // namespace ctx
#endif