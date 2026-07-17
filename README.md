
# GLPaper (glpaper-es3 fork)
GLPaper is a wallpaper program for wlroots based wayland compositors such as sway that allows you to render glsl shaders as your wallpaper

> **Fork note:** This is a fork of [scoopta's glpaper](https://hg.sr.ht/~scoopta/glpaper)
> (imported at rev `af9827d20bfe`) patched to use an **OpenGL ES 3.0 context** so
> fragment shaders can be written in **GLSL ES 3.00** instead of the original ES 1.00.
>
> Your shaders must now start with `#version 300 es` and use modern syntax:
> - `in vec2 texCoords;` (was `varying`)
> - `out vec4 fragColor;` + write `fragColor` (was `gl_FragColor`)
> - `texture(...)` (was `texture2D`)
> - a `precision` qualifier is required, e.g. `precision highp float;`
>
> Old `#version 100` / `varying` / `gl_FragColor` shaders will no longer compile.

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
