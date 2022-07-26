## Using Font Data Embedded In Source Code

Compile and use [binary_to_compressed_c.cpp](https://github.com/ocornut/imgui/blob/master/misc/fonts/binary_to_compressed_c.cpp) to create a compressed C style array that you can embed in source code.

Build with, e.g:

```
cl.exe binary_to_compressed_c.cpp
g++ binary_to_compressed_c.cpp
clang++ binary_to_compressed_c.cpp
```

The tool can optionally output Base85 encoding to reduce the size of _source code_ but the read-only arrays in the actual binary will be about 20% bigger.

Usage:

```
binary_to_compressed_c.exe [-base85] [-nocompress] <inputfile> <symbolname>

/* Usage example: */

binary_to_compressed_c.exe myfont.ttf MyFont > myfont.cpp
binary_to_compressed_c.exe -base85 myfont.ttf MyFont > myfont.cpp
```

Then load the font with:
```cpp
ImFont* font = io.Fonts->AddFontFromMemoryCompressedTTF(compressed_data, compressed_data_size, size_pixels, ...);
```
or
```cpp
ImFont* font = io.Fonts->AddFontFromMemoryCompressedBase85TTF(compressed_data_base85, size_pixels, ...);
```

## Using Icons

Using an icon font (such as [FontAwesome](http://fontawesome.io) or [OpenFontIcons](https://github.com/traverseda/OpenFontIcons)) is an easy and practical way to use icons in your Dear ImGui application.
A common pattern is to merge the icon font within your main font, so you can embed icons directly from your strings without having to change fonts back and forth.

To refer to the icon UTF-8 codepoints from your C++ code, you may use those headers files created by Juliette Foucaut: https://github.com/juliettef/IconFontCppHeaders.
  
So you can use `ICON_FA_SEARCH` as a string that will render as a "Search" icon.

Example Setup:
```cpp
// Merge icons into default tool font
#include "IconsFontAwesome.h"
ImGuiIO& io = ImGui::GetIO();
io.Fonts->AddFontDefault();

ImFontConfig config;
config.MergeMode = true;
config.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
io.Fonts->AddFontFromFileTTF("fonts/fontawesome-webfont.ttf", 13.0f, &config, icon_ranges);
```
Example Usage:
```cpp
// Usage, e.g.
ImGui::Text("%s among %d items", ICON_FA_SEARCH, count);
ImGui::Button(ICON_FA_SEARCH " Search");
// C string _literals_ can be concatenated at compilation time, e.g. "hello" " world"
// ICON_FA_SEARCH is defined as a string literal so this is the same as "A" "B" becoming "AB"
```
See Links below for other icons fonts and related tools.

Here's an application using icons ("Avoyd", https://www.avoyd.com):
![avoyd](https://user-images.githubusercontent.com/8225057/81696852-c15d9e80-9464-11ea-9cab-2a4d4fc84396.jpg)

