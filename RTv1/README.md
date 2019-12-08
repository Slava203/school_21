RTv1
=====================
<img src="https://github.com/Slava203/school_21/tree/master/RTv1/image/SDL_Logo.png" height="20" align="top"/>

RTv1 is a simple ray tracing program. The project was developed as a part of 42 school program.
It parses a 3D scene from a file and applies ray tracing algorithm to render the given scene.  

<img src="https://github.com/Slava203/school_21/tree/master/RTv1/image/Demo1.png">

Installation
-----------------------------------
Clone or download this repository and run `make` in command line while in the root of the repository. This will build executable called `RTv1`. 

Usage
-----------------------------------
`./RTv1 [scene_name]`  
`scne_name` must contain path to a valid scene.If the scene is not valid, RTv1 will write corresponding error on standard output.

Scene
-----------------------------------
Scene is a file which describes camera, lights and geometric objects that have to be rendered.
### Scene Syntax
```
scene
{
  cam_pos(x_coordinate y_coordinate z_coordinate)
  cam_dir(x_direction y_direction z_direction)
  ambient(level_of_ambient)
}

{
  Add object
}
```
### Object

This project can render such geometric shapes:  
- Light;
- Sphere;
- Plane;
- Cylinder;
- Cone.
#### Light Syntax
```
object(light)
{
  col(r_component g_component b_component)
  pos(x_coordinate y_coordinate z_coordinate)
  int(15)
}
```
#### Object Syntax
```
object(plane)
{
  col(r_component g_component b_component)
  pos(x_coordinate y_coordinate z_coordinate)
  rot(x_direction y_direction z_direction)
  spc(reflection_level)
}

object(sphere)
{
  col(r_component g_component b_component)
  pos(x_coordinate y_coordinate z_coordinate)
  size(radius)
  spc(reflection_level)
}

object(cylinder)
{
  col(r_component g_component b_component)
  pos(x_coordinate y_coordinate z_coordinate)
  rot(x_direction y_direction z_direction)
  size(radius)
  spc(reflection_level)
}

object(cone)
{
  col(r_component g_component b_component)
  pos(x_coordinate y_coordinate z_coordinate)
  rot(x_direction y_direction z_direction)
  size(radius)
  spc(reflection_level)
}
```
Control
-----------------------------------
<table width="100%">
<thead>
<tr>
<td width="40%" height="60px" align="center" cellpadding="0">
<strong>Description</strong>
</td>
<td width="10%" align="center" cellpadding="0">
<span style="width:70px">&nbsp;</span><strong>Key(s)</strong><span style="width:50px">&nbsp;</span>
</td>
</tr>
</thead>
<tbody>
<tr>
<td valign="top" height="30px">Close the program</td>
<td valign="top" align="center"><kbd>&nbsp;esc&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Translate camera/object along local X axis</td>
<td valign="top" align="center"><kbd>&nbsp;A&nbsp;</kbd> <kbd>&nbsp;D&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Translate camera/object along local Y axis</td>
<td valign="top" align="center"><kbd>&nbsp;W&nbsp;</kbd> <kbd>&nbsp;S&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Translate camera/object along local Z axis</td>
<td valign="top" align="center"><kbd>&nbsp;+ (num)&nbsp;</kbd> <kbd>&nbsp;- (num)&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Rotate camera/object along local X axis</td>
<td valign="top" align="center"><kbd>&nbsp;◄&nbsp;</kbd> <kbd>&nbsp;►&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Rotate camera/object along local Y axis</td>
<td valign="top" align="center"><kbd>&nbsp;▲&nbsp;</kbd> <kbd>&nbsp;▼&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Rotate object along local Z axis</td>
<td valign="top" align="center"><kbd><center>&nbsp;page&nbsp;<br /> up</center></kbd> <kbd><center>&nbsp;page&nbsp;<br /> down</center></kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Activate/deactivate gloss (specularity)</td>
<td valign="top" align="center"><kbd>&nbsp;G&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Increase/decrease size/angle of the selected object</td>
<td valign="top" align="center"><kbd>&nbsp;+&nbsp;</kbd> <kbd>&nbsp;-&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Increase/decrease the maximum number of reflections</td>
<td valign="top" align="center"><kbd>&nbsp;R&nbsp;</kbd> <kbd>&nbsp;F&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Increase/decrease the anti-aliasing (1 by default)</td>
<td valign="top" align="center"><kbd>&nbsp;O&nbsp;</kbd> <kbd>&nbsp;P&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Increase/decrease radius</td>
<td valign="top" align="center"><kbd>&nbsp;1 (num)&nbsp;</kbd> <kbd>&nbsp;2 (num)&nbsp;</kbd></td>
</tr>
</tbody>
</table>
