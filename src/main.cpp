#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// #include "global.hpp"

// settings
unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

//size in tiles
unsigned int MAP_WIDTH = 0;
unsigned int MAP_HEIGHT = 0;

const char TITLE[] = "TITLE";

//maximum textures per tile
// const unsigned int MAX_TILE_TEX = 2;

// timing
double deltaTime = 0.0f;	// time between current frame and last frame
double lastFrame = 0.0f;

// float framtimes = 1 / fps;

enum MODE {
    PLAY,
    DEV,
    TOTAL
};


#include "functs/init/init.hpp"
// #include "functs/readFile/readFile.hpp"

#include "Camera.h"
#include "shader.h"
#include "functs/shaderFuncts.h"
#include "texture.h"
#include "functs/textureFuncts.h"
#include "classes/Object/Object.hpp"

#include "classes/LightCube/LightCube.hpp"

#include "classes/Lights/PointLight/PointLight.hpp"
#include "classes/Lights/Spotlight/Spotlight.hpp"

#include "classes/VertBuffer/VertBuffer.hpp"
#include "classes/VertArray/VertArray.hpp"

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

#include "functs/frambufferCallback.hpp"
#include "functs/processInput.hpp"
#include "functs/mouse_callback.hpp"

#include "functs/createWin.hpp"

int main(int argc, char* argv[]) {
    // if (*argv[1] - 48 < MODE::TOTAL)
    //     MODE mode = static_cast<MODE>(*argv[1] - 48);

    init();

    GLFWwindow* window = createWin();

    // stbi_set_flip_vertically_on_load(true);

    Shader lightingShader = compileShader("shaders/multiple_lights.vert", "shaders/multiple_lights.frag");
    Shader lightCubeShader = compileShader("shaders/light_cube.vert", "shaders/light_cube.frag");

    VertBuffer VBOR = VertBuffer();
    VertArray cubeVAO = VertArray();
    VertArray lightCubeVAO = VertArray();

    VBOR.BufferData();
    glBindBuffer(GL_ARRAY_BUFFER, VBOR.pntr);

    // first, configure the cube's VAO (and VBO)
    // unsigned int cubeVAO;//, EBO, NBO, TBO, 
    // glGenVertexArrays(1, &cubeVAO);

    glBindVertexArray(cubeVAO.pntr);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    // glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    // unsigned int lightCubeVAO;
    glBindVertexArray(lightCubeVAO.pntr);

    glBindBuffer(GL_ARRAY_BUFFER, VBOR.pntr);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // VBOR.pntr = NULL;

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------

    Texture diffuseMap = createTexture("textures/container2.png", true);
    Texture specularMap = createTexture("textures/container2_specular.png", true);

    Object objList[] = {
        Object(&cubeVAO, 36, glm::vec3(0.0f,  0.0f,  0.0f), 1.2, glm::vec3(0.0f,  0.0f,  0.0f), &diffuseMap, &specularMap),
        Object(&cubeVAO, 36, glm::vec3( 2.0f, 5.0f,  -15.0f), 1.2, glm::vec3(0.0f,  0.0f,  0.0f), &diffuseMap, &specularMap),
        Object(&cubeVAO, 36, glm::vec3(-1.5f, -2.2f, -2.5f), 1.2, glm::vec3(0.0f,  0.0f,  0.0f), &diffuseMap, &specularMap),
        Object(&cubeVAO, 36, glm::vec3(-3.8f, -2.0f, -12.3f), 1.2, glm::vec3(0.0f,  0.0f,  0.0f), &diffuseMap, &specularMap),
        Object(&cubeVAO, 36, glm::vec3( 2.4f, -0.4f, -3.5f), 1.2, glm::vec3(0.0f,  0.0f,  0.0f), &diffuseMap, &specularMap),
        Object(&cubeVAO, 36, glm::vec3(-1.7f, 3.0f,  -7.5f), 1.2, glm::vec3(0.0f,  0.0f,  0.0f), &diffuseMap, &specularMap),
        Object(&cubeVAO, 36, glm::vec3( 1.3f, -2.0f, -2.5f), 1.2, glm::vec3(0.0f,  0.0f,  0.0f), &diffuseMap, &specularMap),
        Object(&cubeVAO, 36, glm::vec3( 1.5f, 2.0f,  -2.5f), 1.2, glm::vec3(0.0f,  0.0f,  0.0f), &diffuseMap, &specularMap),
        Object(&cubeVAO, 36, glm::vec3( 1.5f, 0.2f,  -1.5f), 1.2, glm::vec3(0.0f,  0.0f,  0.0f), &diffuseMap, &specularMap),
        Object(&cubeVAO, 36, glm::vec3(-1.3f, 1.0f,  -1.5f), 1.2, glm::vec3(0.0f,  0.0f,  0.0f), &diffuseMap, &specularMap)
    };

    LightCube lightCubeList[] = {
        LightCube(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
        1.0f, 0.09f, 0.032f, &cubeVAO, glm::vec3(0.0f,  0.0f,  0.0f)),

        LightCube(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
        1.0f, 0.09f, 0.032f, &cubeVAO, glm::vec3( 2.3f, -3.3f, -4.0f)),

        LightCube(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
        1.0f, 0.09f, 0.032f, &cubeVAO, glm::vec3(-4.0f,  2.0f, -12.0f)),

        LightCube(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
        1.0f, 0.09f, 0.032f, &cubeVAO, glm::vec3( 0.0f,  0.0f, -3.0f))
    };

    // shader configuration
    // --------------------
    use(lightingShader);
    setInt(lightingShader, "material.diffuse", 0);
    setInt(lightingShader, "material.specular", 1);

    // for (Object i : objList) {
    //     i.scale(.5);
    // }

    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // test->setNum(test->getNum() + 1);
        // printf("%d", test->getNum());

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        use(lightingShader);
        setVec3(lightingShader, "viewPos", camera.Position);
        setFloat(lightingShader, "material.shininess", 32.0f);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index 
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        // directional light
        setVec3(lightingShader, "dirLight.direction", -0.2f, -1.0f, -0.3f);
        setVec3(lightingShader, "dirLight.ambient", 0.05f, 0.05f, 0.05f);
        setVec3(lightingShader, "dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        setVec3(lightingShader, "dirLight.specular", 0.5f, 0.5f, 0.5f);

        for (unsigned int i = 0; i < 4; i++) {
            setVec3(lightingShader, "pointLights[" + std::to_string(i) + "].position", lightCubeList[i].pos);
            setVec3(lightingShader, "pointLights[" + std::to_string(i) + "].ambient", lightCubeList[i].ambient);
            setVec3(lightingShader, "pointLights[" + std::to_string(i) + "].diffuse", lightCubeList[i].diffuse);
            setVec3(lightingShader, "pointLights[" + std::to_string(i) + "].specular", lightCubeList[i].specular);
            setFloat(lightingShader, "pointLights[" + std::to_string(i) + "].constant", lightCubeList[i].constant);
            setFloat(lightingShader, "pointLights[" + std::to_string(i) + "].linear", lightCubeList[i].linear);
            setFloat(lightingShader, "pointLights[" + std::to_string(i) + "].quadratic", lightCubeList[i].quadratic);
        }
        
        // spotLight
        // lightingShader.setVec3("spotLight.position", camera.Position);
        // lightingShader.setVec3("spotLight.direction", camera.Front);
        setVec3(lightingShader, "spotLight.position", camera.Position);
        setVec3(lightingShader, "spotLight.direction", camera.Front);
        setVec3(lightingShader, "spotLight.ambient", 0.0f, 0.0f, 0.0f);
        setVec3(lightingShader, "spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        setVec3(lightingShader, "spotLight.specular", 1.0f, 1.0f, 1.0f);
        setFloat(lightingShader, "spotLight.constant", 1.0f);
        setFloat(lightingShader, "spotLight.linear", 0.09f);
        setFloat(lightingShader, "spotLight.quadratic", 0.032f);
        setFloat(lightingShader, "spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        setFloat(lightingShader, "spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        setMat4(lightingShader, "projection", projection);
        setMat4(lightingShader, "view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        setMat4(lightingShader, "model", model);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap.texture);
        
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap.texture);
        
        glBindVertexArray(cubeVAO.pntr);
        //dont know why this works have tried to do objList[i].lastpos.x but breaks
        for (unsigned int i = 0; i < 10; i++) {
            objList[i].rotate(glm::vec3(glm::radians(glm::cos(glfwGetTime())),
                glm::radians(glm::sin(glfwGetTime())),
                0));
            // objList[i].model = glm::translate(objList[i].model, glm::vec3(
            //     0 + glm::sin(glfwGetTime()) * 0.5,
            //     0,
            //     0 + glm::cos(glfwGetTime()) * 0.5));
            objList[i].draw(&lightingShader);
        }

        // also draw the lamp object(s)
        use(lightCubeShader);
        setMat4(lightCubeShader, "projection", projection);
        setMat4(lightCubeShader, "view", view);
    
        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO.pntr);
        for (unsigned int i = 0; i < 4; i++) {
            lightCubeList[i].draw(&lightCubeShader);
        }

        // printf("X:%f|Y:%f|Z:%f\n", camera.Position.x, camera.Position.y, camera.Position.z);
        // printf("X:%f|Y:%f|Z:%f\n", camera.Front.x, camera.Front.y, camera.Front.z);
        // printf("%f\n", objList[1].model);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    cubeVAO.~VertArray();
    lightCubeVAO.~VertArray();
    VBOR.~VertBuffer();
    

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
