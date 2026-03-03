# 3D Renderer
This project is a 3D renderer made in C using SDL2, it handles user input to move the camera around and lets the user load any wavefront (.obj) files.
It rotates the model and applies face lighting.

## Installation
```sh
git clone https://github.com/chalettt/3DR.git
cd 3DR && make
```
Do not forget to install SDL2 through your favorite package manager.

## Usage
```sh
./cube my_awesome_wavefront_file.obj
```

### Flags
-  -x Changes the x coordinate of the model origin.
-  -y Changes the y coordinate of the model origin.
-  -z Changes the z coordinate of the model origin.
```sh
./cube my_awesome_wavefront_file.obj -x 1 -y 2 -z 3
```

### Inputs
- WASD to move around.
- Space and Left Control to respectively go up and down.
- Left Shift to go faster.
- Mouse movements as camera rotation.

## Documentation
Each header file contains a doxygen documentation, you can run the following command to generate the full documentation (which will generate in /docs):
```sh
make doc
```
