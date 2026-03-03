# 3D Renderer
This project is a 3D renderer made in C using SDL2, it handles user input to move the camera around and lets the user load any wavefront (.obj) files.
It rotates the model and applies face lighting.

## Installation
```sh
git clone https://github.com/chalettt/3DR.git
cd 3DR && make
```

## Usage
```sh
./cube my_awesome_wavefront_file.obj
```

### Flags
-  -x Changes the x coordinate of the cube origin.
-  -y Changes the y coordinate of the cube origin.
-  -z Changes the z coordinate of the cube origin.
```sh
./cube my_awesome_wavefront_file.obj -x 67 -y 67 -z 67
```

### Inputs
- WASD to move around.
- Space and Left Control to respectively go up and down.
- Left Shift to go faster.
- Mouse movements as camera rotation.
