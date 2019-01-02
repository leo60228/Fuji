# Fuji
[![works badge](https://cdn.jsdelivr.net/gh/nikku/works-on-my-machine@v0.2.0/badge.svg)](https://github.com/nikku/works-on-my-machine)

A toolkit for porting maps for the game Celeste to the Nintendo Switch. Includes the following:

* Switch Application: A patcher for Celeste's dialog file, so that you don't have to redistribute all of it with your mod.
* Switchify: Patches Celeste maps to be compatible with an unmodified game. Depends on Maple.
* Atlas Modifications (WIP): Enables modifying Celeste atlas files. Currently contains Ahorn's dumper as a standalone script, but will be enabled to add support for repacking atlases. Depends on Maple and Cairo.jl.
* Differ: A CLI app built around Collage to create binary diffs. Currently not very formalized.
