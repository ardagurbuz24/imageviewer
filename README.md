SDL2 Image Viewer

A lightweight, hardware-accelerated image viewer built with C and SDL2. This tool allows users to view images instantly by dragging and dropping files into the window.
🚀 Features

    Hardware Acceleration: Uses GPU textures for efficient rendering.

    Drag & Drop: Drag any JPG or PNG file into the window to view it instantly.

    Dynamic Loading: Automatically manages memory and reloads textures on the fly.

    Cross-Format Support: Handles multiple image formats via SDL_image.

🛠 Installation
Prerequisites

Ensure you have SDL2 and SDL2_image libraries installed:

    Linux: sudo apt install libsdl2-dev libsdl2-image-dev

    macOS: brew install sdl2 sdl2_image

    Windows: Download development minGW/VC files from libsdl.org.

Build

Compile the project using gcc:

`gcc main.c -o image_viewer -lSDL2 -lSDL2_image`

🖥 Usage

    Run the application: ./image_viewer

    Drag and Drop any image file (.jpg, .png) directly into the application window.

    Close the window to exit.

📂 Current Progress

    [x] Basic window and renderer setup.

    [x] Image loading and texture management.

    [x] Event loop with SDL_QUIT support.

    [x] Drag and Drop (SDL_DROPFILE) support.

    [ ] Aspect Ratio correction (Coming soon!).