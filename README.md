## TODO
* SimpleRenderer (processInputs(inputMutables), renderObjects, createGui)
* Camera (origin, pitch, yaw, perspective)
* Object
  * createVAO (optionally using VBO/UVs)
  * activateShader() (set material uniforms, bind textures, or lookup a material setup function with MaterialId)
  * draw(camera) (binds VAO, activate shader, glDrawArrays() or glDrawElements())
  * Materials
    *activateShader() (bind textures, set uniforms)
    * ?Textures


## Requirements
* [`stb_image.h`](https://github.com/nothings/stb/blob/master/stb_image.h)
* [glm](https://github.com/g-truc/glm)
