{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs, ... }: let
    system = "x86_64-linux";

    lib = nixpkgs.lib;
    pkgs = import nixpkgs { inherit system; };
  in {
    devShells.${system}.default = pkgs.mkShell rec {
      buildInputs = with pkgs; [
        platformio
        libusb1
      ];

      shellHook = ''
        zsh
        exit
      '';

      LD_LIBRARY_PATH = lib.makeLibraryPath buildInputs;
    };
  };
}
