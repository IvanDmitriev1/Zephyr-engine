# Renderer layout

This directory is split into three main layers:

## RHI (Render Hardware Interface)
- **`RHI/Interfaces/`**: API-neutral interfaces and creation entry points.
  - `RHI/Interfaces/Device.ixx`: Factory functions for buffers, pipelines, framebuffers, etc.
  - `RHI/Interfaces/I*`: Abstract interfaces for buffers, textures, pipelines, render-pass encoders, etc.
- **`RHI/Types/`**: Resource descriptors and enums (buffers, textures, pipelines, render passes, layouts).

The RHI layer is the contract implemented by backend-specific code (e.g., `Platform/OpenGL`).

## Core renderer orchestration
- **`Core/Types/`**: High-level renderer structures such as render phases, render graph context,
  materials, draw item data, and shared math/extent helpers.
- **`Core/Graph/`**: Render graph, pass interfaces, draw batches, and pass implementations.
- **`Core/Resources/`**: Material and mesh wrappers plus pipeline cache.
- **`Core/Shaders/`**: Shader loading helpers.
- **`Core/Frame/`** and **`Core/Scene/`**: Frame submission and scene-to-render bridge logic.

## Platform abstractions
- **`Platform/`**: Windowing and UI context interfaces.
