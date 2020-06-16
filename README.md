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
* [FreeImage](https://freeimage.sourceforge.io/) - Used for PNG saving. 
Usage reference: [UsingFreeImage3.11 for ImageOutput](http://graphics.stanford.edu/courses/cs148-10-summer/docs/UsingFreeImage.pdf)

* [glm](https://github.com/g-truc/glm) - Used for linear algebra

* [`stb_image.h`](https://github.com/nothings/stb/blob/master/stb_image.h) - Used for texture loading
