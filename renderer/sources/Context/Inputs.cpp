#include "../../include/Context/Inputs.hpp"

namespace ctx {
Inputs::Inputs() { }

Inputs::KEYBOARD Inputs::keyboard = AZERTY;

glm::vec2 Inputs::m_mouse_position = glm::vec2();
glm::vec2 Inputs::m_mouse_velocity = glm::vec2();
glm::vec2 Inputs::m_mouse_acceleration = glm::vec2();
double Inputs::m_mouse_scroll = 0.0;

glm::vec2 Inputs::m_pressed_mouse_position[MOUSE_INPUT_SIZE] = {glm::vec2()};
glm::vec2 Inputs::m_pressed_mouse_diff[MOUSE_INPUT_SIZE] = {glm::vec2()};

bool Inputs::m_pressed_mouse[MOUSE_INPUT_SIZE] = {false};
bool Inputs::m_current_mouse[MOUSE_INPUT_SIZE] = {false};
bool Inputs::m_released_mouse[MOUSE_INPUT_SIZE] = {false};

bool Inputs::m_pressed_keys[KEYS_INPUT_SIZE] = {false};
bool Inputs::m_current_keys[KEYS_INPUT_SIZE] = {false};
bool Inputs::m_released_keys[KEYS_INPUT_SIZE] = {false};

void Inputs::reset_inputs() {
    Inputs::reset_keyboard_inputs();
    Inputs::reset_mouse_inputs();
}

void Inputs::reset_keyboard_inputs() {
    for (int i = 0; i < KEYS_INPUT_SIZE; i++) { m_pressed_keys[i] = false; }
    for (int i = 0; i < KEYS_INPUT_SIZE; i++) { m_released_keys[i] = false; }
}

void Inputs::reset_mouse_inputs() {
    for (int i = 0; i < MOUSE_INPUT_SIZE; i++) { m_pressed_mouse[i] = false; }
    for (int i = 0; i < MOUSE_INPUT_SIZE; i++) { m_released_mouse[i] = false; }

    m_mouse_scroll = 0.0;
}

void Inputs::assign_keyboard(KEYBOARD i_keyboard) {
    keyboard = i_keyboard;
}

int Inputs::convert_key(int key) {
    switch (keyboard) {
        case AZERTY: return convert_key_azerty(key);
        case QWERTY: return convert_key_querty(key);
        default: return key;
    }
}

int Inputs::convert_key_querty(int key) {
    return key;
}
int Inputs::convert_key_azerty(int key) {
    std::string s_key;
    s_key = (char)key;
    if (QWERTY_TO_AZERTY.find(s_key) != QWERTY_TO_AZERTY.end()) {
        std::string mapped = QWERTY_TO_AZERTY[s_key];
        return std::accumulate(mapped.begin(), mapped.end(), 0);
    }
    return key;
}

void Inputs::handle_keyboard_inputs(int key, int action) {
    int c_key = convert_key(key);  // Convert key with right keyboard

    // std::cout << "Key " << key << " [" << (char)key << "] => " << c_key << " [" << (char)c_key << "]" << std::endl;

    if (c_key >= 0 && c_key < KEYS_INPUT_SIZE) {
        if (action == 1) {  // GLFW_PRESS
            m_current_keys[c_key] = true;
            m_pressed_keys[c_key] = true;
        } else if (action == 0) {  // GLFW_RELEASE
            m_current_keys[c_key] = false;
            m_released_keys[c_key] = true;
        }
    }
}

void Inputs::handle_mouse_inputs(int button, int action) {
    if (button >= 0 && button < MOUSE_INPUT_SIZE) {
        if (action == 1) {  // GLFW_PRESS
            m_current_mouse[button] = true;
            m_pressed_mouse[button] = true;
        } else if (action == 0) {  // GLFW_RELEASE
            m_current_mouse[button] = false;
            m_released_mouse[button] = true;
        }
    }
}

void Inputs::handle_cursor_pos(double xpos, double ypos) {
    const glm::vec2 last_pos = m_mouse_position;
    const glm::vec2 last_vel = m_mouse_velocity;
    const glm::vec2 last_acc = m_mouse_acceleration;

    m_mouse_position = glm::vec2(xpos, ypos);
    m_mouse_velocity = m_mouse_position - last_pos;
    m_mouse_acceleration = m_mouse_velocity - last_vel;

    /*
    std::cout << "POS [" << m_mouse_position.x << ";" << m_mouse_position.y <<                         //
        "]\t\tVEL[" << m_mouse_velocity.x << "; " << m_mouse_velocity.y <<                             //
        "]\t\tACC[" << m_mouse_acceleration.x << "; " << m_mouse_acceleration.y << "] " << std::endl;  //
    */
}

void Inputs::handle_mouse_scroll(double xoffset, double yoffset) {
    m_mouse_scroll = yoffset;
}

void Inputs::handle_mouse_position() {
    // /!\ HandleMousePosition must be called after HandleMouseInputs & HandleCursorPos
    for (int i = 0; i < MOUSE_INPUT_SIZE; i++) {
        if (m_pressed_mouse[i]) m_pressed_mouse_position[i] = m_mouse_position;
        if (m_current_mouse[i]) m_pressed_mouse_diff[i] = m_mouse_position - m_pressed_mouse_position[i];
    }
}

bool Inputs::key_pressed(int key) {
    return m_pressed_keys[key];
}
bool Inputs::key_down(int key) {
    return m_current_keys[key];
}
bool Inputs::key_released(int key) {
    return m_released_keys[key];
}

bool Inputs::mouse_pressed(int key) {
    return m_pressed_mouse[key];
}
bool Inputs::mouse_down(int key) {
    return m_current_mouse[key];
}
bool Inputs::mouse_released(int key) {
    return m_released_mouse[key];
}

bool Inputs::key_pressed(std::string key) {
    return key_pressed(std::accumulate(key.begin(), key.end(), 0));
}
bool Inputs::key_down(std::string key) {
    return key_down(std::accumulate(key.begin(), key.end(), 0));
}
bool Inputs::key_released(std::string key) {
    return key_released(std::accumulate(key.begin(), key.end(), 0));
}

bool Inputs::mouse_pressed(std::string key) {
    return mouse_pressed(std::accumulate(key.begin(), key.end(), 0));
}
bool Inputs::mouse_down(std::string key) {
    return mouse_down(std::accumulate(key.begin(), key.end(), 0));
}
bool Inputs::mouse_released(std::string key) {
    return mouse_released(std::accumulate(key.begin(), key.end(), 0));
}

double Inputs::mouse_scroll() {
    return m_mouse_scroll;
}
glm::vec2 Inputs::mouse_position() {
    return m_mouse_position;
}
glm::vec2 Inputs::mouse_velocity() {
    return m_mouse_velocity;
}
glm::vec2 Inputs::mouse_acceleration() {
    return m_mouse_acceleration;
}
glm::vec2 Inputs::pressed_mouse_position(int button) {
    return m_pressed_mouse_position[button];
}
glm::vec2 Inputs::pressed_mouse_diff(int button) {
    return m_pressed_mouse_diff[button];
}

std::unordered_map<std::string, std::string> Inputs::QWERTY_TO_AZERTY = {

    {"q", "a"},  // conversion x => x
    {"b", "b"},  // conversion x => x
    {"c", "c"},  // conversion x => x
    {"d", "d"},  // conversion x => x
    {"e", "e"},  // conversion x => x
    {"f", "f"},  // conversion x => x
    {"g", "g"},  // conversion x => x
    {"h", "h"},  // conversion x => x
    {"i", "i"},  // conversion x => x
    {"j", "j"},  // conversion x => x
    {"k", "k"},  // conversion x => x
    {"l", "l"},  // conversion x => x
    {":", "m"},  // conversion x => x
    {"n", "n"},  // conversion x => x
    {"o", "o"},  // conversion x => x
    {"p", "p"},  // conversion x => x
    {"a", "q"},  // conversion x => x
    {"r", "r"},  // conversion x => x
    {"s", "s"},  // conversion x => x
    {"t", "t"},  // conversion x => x
    {"u", "u"},  // conversion x => x
    {"v", "v"},  // conversion x => x
    {"z", "w"},  // conversion x => x
    {"x", "x"},  // conversion x => x
    {"y", "y"},  // conversion x => x
    {"w", "z"},  // conversion x => x
    /*
    {"]", "$"},   // conversion x => x
    {"'", "ù"},   // conversion x => x
    {"\"", "*"},  // conversion x => x
    {"\"", "<"},  // conversion x => x
    {"m", ","},   // conversion x => x
    {",", ";"},   // conversion x => x
    {".", ":"},   // conversion x => x
    {"/", "!"},   // conversion x => x
    {"1", "&"},   // conversion x => x
    {"2", "é"},   // conversion x => x
    {"3", "\""},  // conversion x => x
    {"4", "'"},   // conversion x => x
    {"5", "("},   // conversion x => x
    {"6", "-"},   // conversion x => x
    {"7", "è"},   // conversion x => x
    {"8", "_"},   // conversion x => x
    {"9", "ç"},   // conversion x => x
    {"0", "à"},   // conversion x => x
    {"-", ")"},   // conversion x => x
    {"=", "="},   // conversion x => x
    {"2", "~"},   // conversion x => x
    {"3", "#"},   // conversion x => x
    {"4", "{"},   // conversion x => x
    {"5", "["},   // conversion x => x
    {"6", "|"},   // conversion x => x
    {"7", "`"},   // conversion x => x
    {"8", "\\"},  // conversion x => x
    {"9", "^"},   // conversion x => x
    {"-", "@"},   // conversion x => x
    {"-", "]"},   // conversion x => x
    {"=", "}"},   // conversion x => x
    */
    {"Q", "A"},  // conversion x => x
    {"B", "B"},  // conversion x => x
    {"C", "C"},  // conversion x => x
    {"D", "D"},  // conversion x => x
    {"E", "E"},  // conversion x => x
    {"F", "F"},  // conversion x => x
    {"G", "G"},  // conversion x => x
    {"H", "H"},  // conversion x => x
    {"I", "I"},  // conversion x => x
    {"J", "J"},  // conversion x => x
    {"K", "K"},  // conversion x => x
    {"L", "L"},  // conversion x => x
    {",", "M"},  // conversion x => x
    {"N", "N"},  // conversion x => x
    {"O", "O"},  // conversion x => x
    {"P", "P"},  // conversion x => x
    {"A", "Q"},  // conversion x => x
    {"R", "R"},  // conversion x => x
    {"S", "S"},  // conversion x => x
    {"T", "T"},  // conversion x => x
    {"U", "U"},  // conversion x => x
    {"V", "V"},  // conversion x => x
    {"Z", "W"},  // conversion x => x
    {"X", "X"},  // conversion x => x
    {"Y", "Y"},  // conversion x => x
    {"W", "Z"},  // conversion x => x
    /*
    {"]", "£"},   // conversion x => x
    {"'", "%"},   // conversion x => x
    {"\"", "µ"},  // conversion x => x
    {"\"", ">"},  // conversion x => x
    {"M", "?"},   // conversion x => x
    {",", "."},   // conversion x => x
    {".", "/"},   // conversion x => x
    {"/", "§"},   // conversion x => x
    {"1", "1"},   // conversion x => x
    {"2", "2"},   // conversion x => x
    {"3", "3"},   // conversion x => x
    {"4", "4"},   // conversion x => x
    {"5", "5"},   // conversion x => x
    {"6", "6"},   // conversion x => x
    {"7", "7"},   // conversion x => x
    {"8", "8"},   // conversion x => x
    {"9", "9"},   // conversion x => x
    {"0", "0"},   // conversion x => x
    {"-", "°"},   // conversion x => x
    {"=", "+"},   // conversion x => x
    */
};
}  // namespace ctx