# 🌀 Mandelbrot Set Visualizer

![Mandelbrot Set Example](https://github.com/h1gro/Mandelbrot/screenshots/image.png)

A project for visualizing the Mandelbrot set using the SFML graphics library in C++. Allows exploring the fractal with zooming, color scheme customization, and image saving capabilities.

[![SFML](https://img.shields.io/badge/SFML-2.5.1-blue.svg)](https://www.sfml-dev.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## 📋 About

The Mandelbrot set is a fractal defined by complex number iterations. This project implements:
- Interactive fractal visualization
- Keybords zooming
- Panning with arrow keys/QWES
- Dynamic color scheme switching
- PNG image saving
- View reset functionality

## Optimization

At this project we used GCC optimizations flags: -O1, -O2, -O3. Also there are 3 different vesions of realizations (gradation by optimization): simple version, arrays version and intrin version.

### 1. Simple version

Every point (x,y) from graphics window we calculate with Mandelbrot calculation and paint depending on the number of calculations for this point. Define departure point out of the window by comparing with max circle radius for the observed window.

### 2. Array version

Every 4 points we put on arrays (like x = {x0, x0 + 1, x0 + 2, x0 + 3} and y = {...}) and processing coordinates of this points by cycles in 4 iterations. Paint points depending on the number of all 4 points - calcs. Define departure point out of the window by bits mask.


### 3. Intrin Version

Every 4 points we packed in containers size 4 with type __m128. Processing with coordinates we carry out by SIMD instructions (assembly codes for working with low level tools: like registers, stack). By this intrinsics we defined points departures and maximum calculates of 4 points by two bits masks.

info about intrinsisc you can find there:
https://www.laruence.com/sse/#expand=4929,133,4929,0,5022,951,4929&text=_mm_move
http://www.ccfit.nsu.ru/~kireev/lab4/lab4intr.htm


## 🛠️ Installation

### Build
```bash
git clone https://github.com/h1gro/Mandelbrot.git
cd Mandelbrot
mkdir build && cd build
cmake ..
cmake --build .
```
