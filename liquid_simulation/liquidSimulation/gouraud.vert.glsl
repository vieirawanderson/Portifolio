#version 120
/*
 * Michael Shafae
 * mshafae at fullerton.edu
 * 
 * A simple Gouraud shader with two light sources.
 * This file is the vertex shader which calculates
 * the the vector to the light, the vector to the viewer,
 * and the reflection vector. The color is calculated
 * using the Phong illumination equation.
 *
 * For more information see:
 *     <http://en.wikipedia.org/wiki/Gouraud_shading>
 *
 * $Id: gouraud.vert.glsl 5717 2015-04-15 17:31:49Z mshafae $
 *
 * Be aware that for this course, we are limiting ourselves to
 * GLSL v.1.2. This is not at all the contemporary shading
 * programming environment, but it offers the greatest degree
 * of compatability.
 *
 * Please do not use syntax from GLSL > 1.2 for any homework
 * submission.
 *
 */

// These are passed in from the CPU program, camera_control_*.cpp
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;
uniform vec4 light0_position;
uniform vec4 light0_color;
uniform vec4 light1_position;
uniform vec4 light1_color;

// out
varying vec4 myColor; 

vec4 phongIlumination (const in vec3 direction, const in vec4 lightcolor, const in vec3 normal, const in vec4 mydiffuse, const in vec4 myspecular, const in float myshininess){

  vec3 reflection = 2 * normal * dot(normal, direction) - direction;

  return (mydiffuse * lightcolor * max (dot(normal, direction), 0.0)) + (myspecular * lightcolor * pow (max(dot(normal,reflection), 0.0), myshininess));
}  

void main( ){
  vec4 ambient = vec4(0.2, 0.2, 0.2, 1.0);
  vec4 diffuse = vec4(0.5, 0.5, 0.5, 1.0);
  vec4 specular = vec4(1.0, 1.0, 1.0, 1.0);
  float shininess = 100;
  
	// Transforming The Vertex
  
  gl_Position = projectionMatrix * modelViewMatrix * gl_Vertex;

  // Calculating the color at this vertex
  // Fill me in!
  vec4 vPosition = modelViewMatrix * gl_Vertex;
  vec3 position = vPosition.xyz / vPosition.w;

  vec3 eyePosition = vec3(0,0,0);
  vec3 eyeDirection = normalize(eyePosition - position);

  vec4 _normal = normalMatrix * vec4(gl_Normal, 0.0);
  vec3 normal = normalize(_normal.xyz);

  vec3 position0 = light0_position.xyz / light0_position.w;
  vec3 direction0 = normalize(position0 - position);

  vec3 position1 = light1_position.xyz / light1_position.w;
  vec3 direction1 = normalize(position1 - position);

  vec3 half0 = normalize(direction0 + eyeDirection); 
  vec3 half1 = normalize(direction1 + eyeDirection); 

  vec4 color0 = phongIlumination(direction0, light0_color, normal, diffuse, specular, shininess);
  vec4 color1 = phongIlumination(direction1, light1_color, normal, diffuse, specular, shininess);

  
  // Sum the colors and pass it along to the fragment shader.
  myColor = ambient + color0 + color1;

}
