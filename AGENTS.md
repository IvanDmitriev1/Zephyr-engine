# AGENTS.ME — Zephyr Engine & Editor
Applies to the entire repository.

## Project overview
- C++23 game engine (`Zephyr`) with an editor (`ZephyrEditor`) targeting an OpenGL renderer path.
- Engine code is organized around C++ modules (`.ixx`) with a thin set of `.cpp` implementations where needed.
- Key domains:
  - `Zephyr/src/core`: application bootstrap, layer stack, and shared ownership helpers (`Ref`, `Scope`, `CreateRef`, `CreateScope`).
  - `Zephyr/src/events`: event definitions and macros for dispatch categories/types.
  - `Zephyr/src/logging`: logging infrastructure built on spdlog (`Zephyr::log` for engine messages, `Zephyr::applog` for app/editor output).
  - `Zephyr/src/Renderer`: rendering interfaces (`RHI::Device`, buffers, shaders, framebuffers, windows).
  - `ZephyrEditor/src`: editor application, ImGui UI, and debug panels (e.g., `UiComponets/DebugLog`).

## Build & run
- Windows + Visual Studio 2022 is the primary target (C++23 modules required).
- From the repo root run `premake5 vs2022` (or `RegenerateVSProject.bat`) to generate the solution.
- Build the `Zephyr` static library and the `ZephyrEditor` app using the `Debug|Opengl` or `Release|Opengl` configuration in the generated solution. The editor is the default startup project.
- Dependencies are vendored (GLFW, GLAD, GLM, spdlog, ImGui); avoid adding external package managers unless absolutely necessary.

## Coding style
- Match the existing module pattern: start with `module;` for bridge includes when needed, then `export module <name>;` and `export import` dependencies. Prefer modules over headers for new engine/editor code.
- Indent with tabs to stay consistent with current sources; keep braces on the same line as control statements and declarations.
- Favor engine utilities for ownership and diagnostics:
  - Use `Ref`/`Scope` (via `CreateRef`/`CreateScope`) instead of raw `new`/`delete`.
  - Use `Zephyr::Assert` for invariants and `Zephyr::log`/`Zephyr::applog` for output instead of ad-hoc prints.
- Keep renderer-agnostic code inside `Zephyr::RHI` interfaces; isolate API-specific details to the renderer backend instead of the editor or high-level engine layers.
- When extending ImGui UI, follow the patterns in `ZephyrEditor/src` (explicit dockspace setup, `Draw*` helpers, and `Begin`/`End` pairing) and reuse existing colors/fonts where possible.

## Testing & validation
- Before shipping changes, regenerate the solution and build `Zephyr` and `ZephyrEditor` in at least one configuration when possible. If you cannot build (e.g., OS/toolchain limits), call it out in your notes.
- Do not modify vendored dependency sources unless absolutely required; prefer adjustments in engine/editor code or build scripts.