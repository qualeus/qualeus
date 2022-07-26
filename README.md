<div id="top"></div>

![Qualeus project banner](https://raw.githubusercontent.com/qualeus/carta/main/Logo/Qualeus_banner.jpg)

[![Version][version-shield]][version-url]
[![Language][language-shield]][language-url]
[![Roadmap][roadmap-shield]][roadmap-url]
[![License][license-shield]][license-url]
[![Build][build-shield]][build-url]

<details open>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ol>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ol>
    </li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#authors">Authors</a></li>
  </ol>
</details>

## 1. About The Project

## 2. Getting Started

### 2.1. Prerequisites

The project is developed according to [c++17 standards](https://en.cppreference.com/w/cpp/17).

To build the engine, you will need the [CMake build tool](https://cmake.org/download/) `v3.8+`

You will also need a compiler for `c++17`, make sure yours is compatible (gcc `v8+`, [see support](https://gcc.gnu.org/projects/cxx-status.html#cxx17))

The program has been tested with the following compilers:

- **Linux:** GCC ([GNU Compiler Collection](https://gcc.gnu.org/))
- **Windows:** Mingw ([Minimalist GNU for Windows](https://www.mingw-w64.org/))

### 2.2. Installation

1. Download the project source or clone it with git: `git clone https://github.com/qualeus/engine.git`
2. Create a build directory: `cd engine && mkdir build`
3. Build the project with Cmake: `cd build && cmake -G "YOUR_COMPILER" -DBUILD_TESTS=ON ../..`
4. Build the targets and run tests: `cmake --build . && make CTEST_OUTPUT_ON_FAILURE=TRUE test`

<p align="right">(<a href="#top">back to top</a>)</p>

## 3. Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

Please read [CONTRIBUTING.md](CONSTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## 4. License

Distributed under the MIT License. See `LICENSE.txt` for more information.

## 5. Authors

- **LHOUTELLIER Maël** - _Initial work_ - [mlhoutel](https://github.com/mlhoutel)

<p align="right">(<a href="#top">back to top</a>)</p>
  
[build-shield]: https://img.shields.io/github/workflow/status/qualeus/qualeus/publish/main?style=flat-square
[build-url]: https://github.com/qualeus/qualeus/blob/main/.github/workflows/docs.yml
[version-shield]: https://img.shields.io/badge/version-0.5.2-orange?style=flat-square
[version-url]: https://github.com/qualeus/qualeus/blob/main/CMakeLists.txt
[language-shield]: https://img.shields.io/github/languages/top/qualeus/qualeus?style=flat-square
[language-url]: https://github.com/qualeus/qualeus/search?l=cpp
[roadmap-shield]: https://img.shields.io/badge/roadmap-available-brightgreen?style=flat-square
[roadmap-url]: https://github.com/orgs/qualeus/projects/2
[license-shield]: https://img.shields.io/github/license/qualeus/qualeus?style=flat-square
[license-url]: https://github.com/qualeus/qualeus/blob/main/LICENSE/
[gitter-shield]: https://img.shields.io/gitter/room/qualeus/qualeus?style=flat-square
[gitter-url]: https://gitter.im/simulatio_qualeus/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge
[logo]: ./sources/assets/logo.png
[screenshot]: ./docs/screenshots/Pictures/Benchmarking.png
