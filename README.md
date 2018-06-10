# OGL Loader

This is an OpenGL scene renderer.
Usign GLSL 3.30 core.

See the documentation [here](https://danifm.github.io/3DAv_2/) (generated with doxygen).

Licensed under MIT License. See docs/LICENSE.md for more info.

There is an executable in the binaries folder.

## Implemented features

- Terrain mesh generated from elevation texture.
- Scene graph (hierarchy between scene objects).
- Camera movement:
  - W/S. Forward and backwards.
  - Mouse. Rotate camera.
- Texture usage.
- Lighting: per vertex and per fragment.
- Skybox.
- Post processing.

## Usable shaders

This names are the ones that can be used in the scene.

### Scene object shaders

- **default_textured**: Unlit textured shader. Now used for the terrain.
- **default_textured_lit**: Per vertex lit shader.
- **frag_lit** (default_textured_lit_perfragment.vs/.fs): Per vertex lit shader.

### Other shaders

- **skybox**: default skybox shader.
- **postprocessing**: now its a sepia filter. A wave shader can be uncommented instead.