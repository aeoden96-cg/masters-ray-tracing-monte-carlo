#!/bin/bash

build/PROJECT > image.ppm

# convert the project to a ppm image
pnmtopng image.ppm > result.png
rm image.ppm
