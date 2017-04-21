#!/bin/sh

# Converts a .gv specification for a digraph to a PNG image and views it with eog.

dot -v -Tpng $1.gv > $1.png && eog $1.png
