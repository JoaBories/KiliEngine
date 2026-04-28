# ⚙️KiliEngine

**KiliEngine** is a **student-made 3D engine project** written in **C++** used to learn and experiment with engine architecture and low level rendering.

It’s built around [**SDL2**](https://github.com/libsdl-org/SDL) for windowing/input and [**OpenGL with GLEW**](https://github.com/nigels-com/glew) for rendering.

**Repo:** `JoaBories/KiliEngine`

---

## Libraries :

- [**SDL2**](https://github.com/libsdl-org/SDL) — window creation + input
- [**OpenGL with GLEW**](https://github.com/nigels-com/glew) — rendering backend
- [**Dear ImGui**](https://github.com/ocornut/imgui) — in-engine debug UI
- [**tinyobjloader**](https://github.com/tinyobjloader/tinyobjloader) — `.obj` mesh loading

## Engine systems & capabilities

### Rendering
- OpenGL renderer with support for: **3D Camera**, **Sprite Rendering**, **Tessellation** and **Mipmaps**
- Debug render with different modes : **UVs** / **Normals** / **Wireframe** and **Collision Boxes** and Sphere

### Assets / Resource management
An **Asset Manager** responsible for loading and managing: **Textures**, **Meshes** (supports **`.obj`**), **Shaders** and **Material** (for the moment it's just a list of shaders)

### Physics & collisions
- Physics with: **Gravity** and **Linear velocity**
- Collision system supporting: **Sphere colliders**, **Box colliders** and **Ray Cast**
- Includes **Line Trace** for queries in collisions.

### Input
A simple input layer (on top of **SDL2**) to manage: **Pressed** button states, **Mouse capture** (useful for camera controls).

---

## Example game

- Small [**Bowling**](https://github.com/JoaBories/KiliEngine/releases/tag/Bowling1.0) to demonstrate physics and collisions.
- Small [**Doom**](https://github.com/JoaBories/KiliEngine/releases/tag/DoomLike1.1) to push the Engine further, implement **ray cast** and read map from [Alexandre Coppens](https://github.com/Alexandre-Coppens)'s [DOOM-MapMaker](https://github.com/Alexandre-Coppens/14-Engine/tree/Doom-MapMaker).

## Project goals

This repo is mainly about exploring engine patterns, OpenGL rendering features and building gameplay foundations.
Expect experimentation and refactors as features evolve.
