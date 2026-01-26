# Renderer layout

This directory is split into two main layers:

## RHI (Render Hardware Interface)
- **`RHI/`**: API-neutral interfaces and creation entry points.
  - `RHI/Device.ixx`: Factory functions for buffers, pipelines, framebuffers, etc.
  - `RHI/I*`: Abstract interfaces for buffers, textures, pipelines, render-pass encoders, etc.
  - `RHI/Types/`: Resource descriptors and enums (buffers, textures, pipelines, render passes, layouts).

The RHI layer is the contract implemented by backend-specific code (e.g., `Platform/OpenGL`).

## Renderer types and orchestration
- **`Types/`**: High-level renderer structures such as render phases, render graph context,
  materials, draw item data, and shared math/extent helpers.
- **`RenderGraph/`**: Pass definitions and execution order.
- **`Renderables/`**: Material and mesh wrappers.
- **`Shader/`**: Shader loading helpers.
- **`Window/`** and **`Ui/`**: Windowing and UI context interfaces.
- **`RenderQueue`** / **`Renderer`**: Frame submission and top-level renderer entry points.
