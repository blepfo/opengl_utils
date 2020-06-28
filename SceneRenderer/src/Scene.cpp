#include "SceneRenderer/Scene.hpp"
#include "SceneRenderer/Objects.hpp"
#include "SceneRenderer/Lights.hpp"


namespace SceneRenderer {

void SimpleScene::render() const {
    for(::SceneRenderer::StaticMaterialObject* object : this->objects) {
        object->render(this->lights, this->camera);
    }
}

} // namespace SceneRenderer
