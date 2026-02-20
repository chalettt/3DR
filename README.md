# Rotating cube
This project is the beginning of (I hope) a 3D renderer made in C and SDL, for now it only renders a rotating cube (no faces) and handles user input to move the camera around.

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
-  -x Change the x coordinate of the origin
-  -y Change the y coordinate of the origin
-  -z Change the z coordinate of the origin
```sh
./cube -x 67 -y 67 -z 67
```

### Inputs
- WASD to move around.
- Space and Left Control to respectively go up and down.
- Left Shift to go faster.
