<img src="https://github.com/Slava203/school_21/tree/master/RTv1/image/SDL_Logo.png" height="20" align="top"/>

# RTv1
RTv1 is a simple ray tracing program. The project was developed as a part of 42 school program.
It parses a 3D scene from a file and applies ray tracing algorithm to render the given scene.  

<img src="https://github.com/Slava203/school_21/tree/master/RTv1/image/Demo1.png">

## Installation
Clone or download this repository and run `make` in command line while in the root of the repository. This will build executable called `RTv1`. 

## Usage
`./RTv1 [scene_name]`  
`scne_name` must contain path to a valid scene.If the scene is not valid, RTv1 will write corresponding error on standard output.

## Scene Syntax

scene
{
  cam_pos(x_coordinate y_coordinate z_coordinate)
  cam_dir(x_direction y_direction z_direction)
  ambient(level_of_ambient)
}
