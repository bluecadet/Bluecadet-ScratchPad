# Penner Easing Functions for GLSL/HLSL

All the Penner easing functions we know and love but in a shader friendly format. File is a "cginc" type so you can use #include in Unity's HLSL shaders. But you'll need to copy/paste the methods into your own .frag file for use in GLSL since it doesn't support #include natively.

Feed in a 0.0f to 1.0f float to any of the methods and receive the eased 0.0f to 1.0f float.

Adapted & condensed from: https://github.com/glslify/glsl-easings