#include "../../include/Context/Inputs.hpp"

namespace ctx {
Inputs::Inputs() {}

Inputs::KEYBOARD Inputs::keyboard = AZERTY;

glm::vec2 Inputs::mouse_position = glm::vec2();
glm::vec2 Inputs::mouse_velocity = glm::vec2();
glm::vec2 Inputs::mouse_acceleration = glm::vec2();
double Inputs::mouse_scroll = 0.0;

glm::vec2 Inputs::pressed_mouse_position[MOUSE_INPUT_SIZE] = {glm::vec2()};
glm::vec2 Inputs::pressed_mouse_diff[MOUSE_INPUT_SIZE] = {glm::vec2()};

bool Inputs::pressed_mouse[MOUSE_INPUT_SIZE] = {false};
bool Inputs::current_mouse[MOUSE_INPUT_SIZE] = {false};
bool Inputs::released_mouse[MOUSE_INPUT_SIZE] = {false};

bool Inputs::pressed_keys[KEYS_INPUT_SIZE] = {false};
bool Inputs::current_keys[KEYS_INPUT_SIZE] = {false};
bool Inputs::released_keys[KEYS_INPUT_SIZE] = {false};

void Inputs::ResetInputs() {
    Inputs::ResetKeyboardInputs();
    Inputs::ResetMouseInputs();
}

void Inputs::ResetKeyboardInputs() {
    for (int i = 0; i < KEYS_INPUT_SIZE; i++) { pressed_keys[i] = false; }
    for (int i = 0; i < KEYS_INPUT_SIZE; i++) { released_keys[i] = false; }
}

void Inputs::ResetMouseInputs() {
    for (int i = 0; i < MOUSE_INPUT_SIZE; i++) { pressed_mouse[i] = false; }
    for (int i = 0; i < MOUSE_INPUT_SIZE; i++) { released_mouse[i] = false; }

    mouse_scroll = 0.0;
}

void Inputs::AssignKeyboard(KEYBOARD i_keyboard) { keyboard = i_keyboard; }

int Inputs::ConvertKey(int key) {
    switch (keyboard) {
        case AZERTY: return ConvertKeyAzerty(key);
        case QWERTY: return ConvertKeyQuerty(key);
        default: return key;
    }
}

int Inputs::ConvertKeyQuerty(int key) { return key; }
int Inputs::ConvertKeyAzerty(int key) {
    std::string s_key;
    s_key = (char)key;
    if (QWERTY_TO_AZERTY.find(s_key) != QWERTY_TO_AZERTY.end()) {
        std::string mapped = QWERTY_TO_AZERTY[s_key];
        return std::accumulate(mapped.begin(), mapped.end(), 0);
    }
    return key;
}

void Inputs::HandleKeyboardInputs(int key, int action) {
    int c_key = ConvertKey(key);  // Convert key with right keyboard

    // std::cout << "Key " << key << " [" << (char)key << "] => " << c_key << " [" << (char)c_key << "]" << std::endl;

    if (c_key >= 0 && c_key < KEYS_INPUT_SIZE) {
        if (action == 1) {  // GLFW_PRESS
            current_keys[c_key] = true;
            pressed_keys[c_key] = true;
        } else if (action == 0) {  // GLFW_RELEASE
            current_keys[c_key] = false;
            released_keys[c_key] = true;
        }
    }
}

void Inputs::HandleMouseInputs(int button, int action) {
    if (button >= 0 && button < MOUSE_INPUT_SIZE) {
        if (action == 1) {  // GLFW_PRESS
            current_mouse[button] = true;
            pressed_mouse[button] = true;
        } else if (action == 0) {  // GLFW_RELEASE
            current_mouse[button] = false;
            released_mouse[button] = true;
        }
    }
}

void Inputs::HandleCursorPos(double xpos, double ypos) {
    const glm::vec2 last_pos = mouse_position;
    const glm::vec2 last_vel = mouse_velocity;
    const glm::vec2 last_acc = mouse_acceleration;

    mouse_position = glm::vec2(xpos, ypos);
    mouse_velocity = mouse_position - last_pos;
    mouse_acceleration = mouse_velocity - last_vel;

    /*
    std::cout << "POS [" << mouse_position.x << ";" << mouse_position.y <<                         //
        "]\t\tVEL[" << mouse_velocity.x << "; " << mouse_velocity.y <<                             //
        "]\t\tACC[" << mouse_acceleration.x << "; " << mouse_acceleration.y << "] " << std::endl;  //
    */
}

void Inputs::HandleMouseScroll(double xoffset, double yoffset) { mouse_scroll = yoffset; }

void Inputs::HandleMousePosition() {
    // /!\ HandleMousePosition must be called after HandleMouseInputs & HandleCursorPos
    for (int i = 0; i < MOUSE_INPUT_SIZE; i++) {
        if (pressed_mouse[i]) pressed_mouse_position[i] = mouse_position;
        if (current_mouse[i]) pressed_mouse_diff[i] = mouse_position - pressed_mouse_position[i];
    }
}

bool Inputs::KeyPressed(int key) { return pressed_keys[key]; }
bool Inputs::KeyDown(int key) { return current_keys[key]; }
bool Inputs::KeyReleased(int key) { return released_keys[key]; }

bool Inputs::MousePressed(int key) { return pressed_mouse[key]; }
bool Inputs::MouseDown(int key) { return current_mouse[key]; }
bool Inputs::MouseReleased(int key) { return released_mouse[key]; }

bool Inputs::KeyPressed(std::string key) { return KeyPressed(std::accumulate(key.begin(), key.end(), 0)); }
bool Inputs::KeyDown(std::string key) { return KeyDown(std::accumulate(key.begin(), key.end(), 0)); }
bool Inputs::KeyReleased(std::string key) { return KeyReleased(std::accumulate(key.begin(), key.end(), 0)); }

bool Inputs::MousePressed(std::string key) { return MousePressed(std::accumulate(key.begin(), key.end(), 0)); }
bool Inputs::MouseDown(std::string key) { return MouseDown(std::accumulate(key.begin(), key.end(), 0)); }
bool Inputs::MouseReleased(std::string key) { return MouseReleased(std::accumulate(key.begin(), key.end(), 0)); }

double Inputs::MouseScroll() { return mouse_scroll; }
glm::vec2 Inputs::MousePosition() { return mouse_position; }
glm::vec2 Inputs::MouseVelocity() { return mouse_velocity; }
glm::vec2 Inputs::MouseAcceleration() { return mouse_acceleration; }
glm::vec2 Inputs::PressedMousePosition(int button) { return pressed_mouse_position[button]; }
glm::vec2 Inputs::PressedMouseDiff(int button) { return pressed_mouse_diff[button]; }

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