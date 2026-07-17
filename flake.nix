{
  description = "glpaper fork with an OpenGL ES 3.0 context for GLSL ES 3.00 shaders";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      systems = [ "x86_64-linux" "aarch64-linux" ];
      forAllSystems = f: nixpkgs.lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});

      mkGlpaper = pkgs: pkgs.stdenv.mkDerivation {
        pname = "glpaper-es3";
        version = "0-unstable-2026-07-17";
        src = self;

        nativeBuildInputs = with pkgs; [ meson ninja pkg-config ];
        buildInputs = with pkgs; [ wayland libGL ];

        meta = {
          description = "glpaper fork with an OpenGL ES 3.0 context for GLSL ES 3.00 shaders";
          homepage = "https://github.com/luvcie/glpaper-es3";
          license = pkgs.lib.licenses.gpl3Plus;
          mainProgram = "glpaper";
          platforms = pkgs.lib.platforms.linux;
        };
      };
    in
    {
      packages = forAllSystems (pkgs: rec {
        glpaper-es3 = mkGlpaper pkgs;
        default = glpaper-es3;
      });

      overlays.default = final: _prev: { glpaper-es3 = mkGlpaper final; };
    };
}
