#!/bin/bash

curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
cargo install sccache
cargo install fd-find
cargo install ripgrep

apt update
apt install -y stow
pushd ~/.dotfiles
stow -S zsh
popd
apt install -y zsh