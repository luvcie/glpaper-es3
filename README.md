
# GLPaper (glpaper-es3 fork)
GLPaper is a wallpaper program for wlroots based wayland compositors such as sway that allows you to render glsl shaders as your wallpaper

> **Fork note:** This is a fork of [scoopta's glpaper](https://hg.sr.ht/~scoopta/glpaper)
> (imported at rev `af9827d20bfe`) patched to use an **OpenGL ES 3.2 context** so
> fragment shaders can be written in **GLSL ES 3.20** instead of the original ES 1.00.
>
> Your shaders must now start with `#version 320 es` and use modern syntax:
> - `in vec2 texCoords;` (was `varying`)
> - `out vec4 fragColor;` + write `fragColor` (was `gl_FragColor`)
> - `texture(...)` (was `texture2D`)
> - a `precision` qualifier is required, e.g. `precision highp float;`
>
> Old `#version 100` / `varying` / `gl_FragColor` shaders will no longer compile.

## What GLSL ES 3.20 adds

GLSL ES 3.20 is ES 3.0 plus the features added in 3.1 and 3.2.

Added in 3.1:
- Compute shaders (general GPU work, separate from drawing)
- Shader storage buffers (SSBOs), large read/write buffers shared with the GPU
- Image load/store, reading and writing textures directly, with atomic ops
- Atomic counters
- Arrays of arrays

Added in 3.2:
- Geometry shaders (create or discard geometry on the fly)
- Tessellation shaders (subdivide surfaces for more detail)
- `textureGather`, grab 4 neighboring texels in one call
- Cubemap array textures (`samplerCubeArray`)
- Advanced blend modes (multiply, overlay, and friends)
- Per-sample shading and `gl_HelperInvocation`

Keep in mind glpaper only runs one vertex and one fragment shader. Most of
the big additions above (compute, geometry, tessellation, SSBOs, images) need
extra pipeline stages or buffer setup that glpaper does not provide, so you
cannot reach them from your fragment shader. What you can actually use from a
fragment shader here: `textureGather`, cubemap arrays, and `gl_HelperInvocation`.

See the [GLSL ES 3.20 spec](https://registry.khronos.org/OpenGL/specs/es/3.2/GLSL_ES_Specification_3.20.html) for the full language reference.

[![builds.sr.ht status](https://builds.sr.ht/~scoopta/glpaper.svg)](https://builds.sr.ht/~scoopta/glpaper?)
## Dependencies
	libwayland-dev
	libegl-dev
	pkg-config
	meson
## Building
	hg clone https://hg.sr.ht/~scoopta/glpaper
	cd glpaper
	meson setup build
	ninja -C build
## Installing
	sudo ninja -C build install
## Uninstalling
	sudo ninja -C build uninstall
## Bug Reports
Please file bug reports at https://todo.sr.ht/~scoopta/glpaper
## Contributing
Please submit patches to https://lists.sr.ht/~scoopta/glpaper

You can find documentation here https://man.sr.ht/hg.sr.ht/email.md
## Packages
If you're on Arch there's an unofficial AUR package https://aur.archlinux.org/packages/glpaper-hg/
