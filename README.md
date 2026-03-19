### 🕹️ Test for Vianu Game Jam

This is a prototype engine/graphics test. It implements a custom **Normalized Device Coordinate (NDC)** system where the world is mapped from `-1.0` to `1.0` and manually projected onto the pixel grid.

**What's implemented so far:**
* **Manual Transformation Pipeline:** Handles rotation and translation via math functions rather than built-in engine shortcuts.
* **Coordinate Mapping:** A custom `screen()` function that handles Y-axis inversion and resolution scaling.
* **Dynamic Primitive Toggling:** Supports switching between solid triangle strips and wireframe line strips on the fly.
* **Framerate Independent Movement:** Uses fixed $DT$ (delta time) logic to ensure movement speed remains consistent at 360 FPS.

#### 🎮 Controls
| Key | Action |
| :--- | :--- |
| **W, A, S, D** | Move the object around the screen |
| **Left / Right Arrows** | Rotate the object |
| **Space** | Toggle **Wireframe Mode** |
| **R** | Reset position and rotation |
| **Escape** | Close the application |
