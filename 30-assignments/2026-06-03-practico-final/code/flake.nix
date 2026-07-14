{
  description = "Saca Muela — Sistema de Gestión Odontológica";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            (python3.withPackages (ps: with ps; [
              tkinter
            ]))
            sqlite
            plantuml
            black
            ruff
          ];

          shellHook = ''
            echo "Saca Muela — Dev Environment loaded"
            echo "Python : $(python3 --version)"
            echo "Tools  : black, ruff, plantuml, sqlite3"
            echo "Tkinter: $(python3 -c 'import tkinter; print("ok")')"
          '';
        };
      });
}
