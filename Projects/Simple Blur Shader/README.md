# Blur Shader

This project shows the workflow needed to do a two pass filter on a scene to get a bloom/blur effect. Project is well commented.

## Workflow:

- Draw itmes into scene FBO
- Draw the scene FBO into a blur FBO 1 and apply a horizontal blur using the shader
- Draw the result of blur FBO 1 into blur FBO 2 while applying a vertical blur shader
- Draw the original scene and the result of the second blur pass on top of it