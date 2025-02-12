// Includes
#include <shader.hpp>
#include <window.hpp>
#include <graphics_api.hpp>
#include <component.hpp>
#include <ctime>

using namespace Graphics;
using namespace Engine;
using namespace Math;

// Main code
int main(int argc, char* argv[]) {
    Window window(800, 600, "test");
    OpenGLGraphicsAPI graphics(window);

    Vertex vertices[] = {
        {{-0.5, -0.5, 0.0}, {0.0, 0.0}},
        {{ 0.5, -0.5, 0.0}, {1.0, 0.0}},
        {{-0.5,  0.5, 0.0}, {0.0, 1.0}},
        {{ 0.5,  0.5, 0.0}, {1.0, 1.0}}
    };

    int indices[] = {
        0, 1, 3,
        0, 3, 2
    };
    
    Mesh mesh(&graphics);
    mesh.setVertices(vertices, sizeof(vertices));
    mesh.setIndices(indices, sizeof(indices));

    Material material(&graphics);
    material.setAlbedo("../res/images/test.jpg");

    Renderer renderer(&graphics);
    renderer.setShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");
    renderer.mesh = &mesh;
    renderer.material = &material;

    // Calculating DeltaTime
    float dt = 0;

    Mat4 model = Mat4::identity();

    while (!window.shouldClose()) {
        window.clear(0.2, 0.2, 0.2);

        model = Mat4::rotation(model, dt, Vec3(0, 0, 1));

        renderer.shader->setUniform("model", model);
        renderer.render();

        // Checks and call events and swap the buffers
        dt = window.update();
    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}