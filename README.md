# 3D Renderer
This project is the beginning of, hopefully, a full 3D renderer made in C and SDL, for now it only renders a wireframe rotating cube and handles user input to move the camera around.

## Installation
```sh
git clone https://github.com/chalettt/RotCube.git
cd RotCube && make
```

## Usage
```sh
./cube
```

### Flags
-  -x Changes the x coordinate of the cube origin.
-  -y Changes the y coordinate of the cube origin.
-  -z Changes the z coordinate of the cube origin.
```sh
./cube -x 67 -y 67 -z 67
```

### Inputs
- WASD to move around.
- Space and Left Control to respectively go up and down.
- Left Shift to go faster.
- Mouse movements as camera rotation.
