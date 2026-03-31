## 🚀 Custom SDL3 Game Engine

This lightweight, object-oriented 2D engine is built on top of **SDL3**, designed to abstract the complexities of low-level rendering while providing a flexible, layer-based architecture for game development. 

The engine uses a normalized coordinate system ($(-1, -1)$ to $(1, 1)$), ensuring that your logic remains consistent regardless of window resolution.

---

### 🏛️ Core Architecture

#### **1. The Application & Layers**
The heart of the engine is the `Application` class. It manages the window lifecycle, hardware acceleration, and the main game loop.
* **Configuration:** Initialize the app using `ApplicationConfiguration` to set your window title, dimensions, and target framerate.
* **Layer System:** The engine uses a **Layer Stack**. You create custom classes derived from `Layer`, and the Application automatically handles:
    * `onEvent`: Dispatched during the SDL polling phase.
    * `update`: Where your game logic lives.
    * `render`: Where draw calls are submitted.

#### **2. The Rendering Pipeline**
The `Renderer` acts as a smart wrapper around `SDL_Renderer*`. It specializes in batching geometry data for high performance.
* **Geometry-Based:** Everything is rendered via `SDL_RenderGeometry`.
* **Coordinate Mapping:** While you work in a logical $(-1, 1)$ space, the engine uses a suite of utility functions (`screen()`, `aspect()`, `rotate()`, `translate()` and `scale()`) to automatically map your objects to the correct pixel coordinates without stretching.

---

### 📦 Object Hierarchy

The engine utilizes a progressive inheritance model to give objects more "physical" properties as needed:

| Class | Description |
| :--- | :--- |
| **Object** | The raw primitive. Contains vertices, indices, colors, and textures. |
| **TransformObject** | Adds spatial awareness. Includes `theta` (rotation), `offset` (position), and `scale`. |
| **CollisionObject** | Adds hit detection. Includes the `collides_with()` method for interaction logic. |
| **PhysicsObject** | Adds movement dynamics. Manages `velocity` and `acceleration` via an internal `update()` loop. |

---

### 🛠️ Mathematical Utilities
Located in `utils.hpp`, these functions handle the heavy lifting of linear algebra so you don't have to:
* **Translation & Scaling:** Moves and sizes objects within the normalized space.
* **Rotation:** Handles vertex math for the `theta` property.
* **Aspect Correction:** Automatically adjusts rendering to maintain square proportions on widescreen monitors.

---

### 🕹️ Quick Start Example
```cpp
// 1. Define a configuration
ApplicationConfiguration config{"My Game", {1280, 720}, 60};

// 2. Create the app
Application app(config);

// 3. Push your custom Layer
app.pushLayer<AppLayer>();

// 4. Run
app.run();
```

currently valid compile command: `g++ src/renderer.cpp src/layer.cpp src/object.cpp src/texture.cpp src/main.cpp src/transform_object.cpp src/physics_object.cpp src/app.cpp src/collision_object.cpp -Iinclude -Llib -o window -g -Wall -Wextra -fsanitize=address -O0 -std=c++23 -lSDL3`
