#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

#include "Material.h"

#include "LightDirectional.h"
#include "LightPoint.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


#pragma region Model Data   
float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion 

#pragma region Camera Declare 
// Instanciate Camera class
//Camera camera(glm::vec3(0,0,3.0f), glm::vec3(0,0,0), glm::vec3(0,1.0f,0));
Camera camera(glm::vec3(0, 0, 3.0f), 10.0f, 0.0f, glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Light Declare
//LightDirectional light = LightDirectional(glm::vec3(0.0f, 10.0f, -5.0f), glm::vec3(glm::radians(45.0f), 0, 0), glm::vec3(10.0, 0, 0));
LightPoint light = LightPoint(glm::vec3(1.0f, 1.0f, -2.0f), glm::vec3(glm::radians(45.0f), 0, 0), glm::vec3(5.0, 5.0, 5.0));

#pragma endregion

#pragma region Input Declare
float lastX;
float lastY;
bool firstMouse = true;

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.speedZ = 1.0f;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.speedZ = -1.0f;
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.speedX = -1.0f;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.speedX = 1.0f;
    } else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.speedY = -1.0f;
    } else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.speedY = 1.0f;
    } else {
        camera.speedX = 0.0f;
        camera.speedY = 0.0f;
        camera.speedZ = 0.0f;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float deltaX, deltaY;
    deltaX = xpos - lastX;
    deltaY = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(deltaX, deltaY);
    //std::cout << deltaX << "," << deltaY << std::endl;
}
#pragma endregion

unsigned int LoadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot) {
    unsigned int TexBuffer;
    
    glGenTextures(1, &TexBuffer);
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, TexBuffer);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "load image failed" << std::endl;
    }
    stbi_image_free(data);
    return TexBuffer;
}


int main()
{
    #pragma region OPEN a Window
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    #pragma endregion

    #pragma region Init Shader Program
    // build and compile our shader program
    Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
    #pragma endregion

    #pragma region Init Material
    Material* myMaterial = new Material(myShader, 
        LoadImageToGPU("container2.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
        LoadImageToGPU("container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),
        glm::vec3(1.0f, 1.0f, 1.0f),
        32.0f);

    #pragma endregion

    #pragma region Init and Load Models to VAO, VBO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(6);
    // normal attribute
    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(7);
    // texture coord attribute
    glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(8);
    //glVertexAttribPointer(9, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(9);
    #pragma endregion

    #pragma region Init and Load Textures
    //unsigned int TexBufferA;
    //TexBufferA = LoadImageToGPU("container.jpg", GL_RGB, GL_RGB, 0);
    //unsigned int TexBufferB;
    //TexBufferB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 0);
    #pragma endregion
    
    #pragma region Prepare MVP Matrices
    glm::mat4 modelMat(1.0f);
    glm::mat4 viewMat(1.0f);
    glm::mat4 projMat(1.0f);
    projMat = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    #pragma endregion
    

    while (!glfwWindowShouldClose(window))
    {
        // Process Input
        processInput(window);

        // Clear Screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


        viewMat = camera.GetViewMatrix();

        for (unsigned int i = 0; i < 10; i++)
        {
            // Set Model Matrix
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 0.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            modelMat = model;
            
            // Set View and Projection Matrices here if you want 
            //
            
            // Set Material -> Shader Program
            myShader->use();
            
            // Set Material -> Textures
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
            glActiveTexture(GL_TEXTURE0 + 1);
            glBindTexture(GL_TEXTURE_2D, myMaterial->specular);

            // Set Material -> Uniforms
            //glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
            //glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 3);
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
            glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
            glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"), 0.1f, 0.1f, 0.1f);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPos"), light.position.x, light.position.y, light.position.z);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightColor"), light.color.x, light.color.y, light.color.z);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightDirUniform"), light.direction.x, light.direction.y, light.direction.z);
            glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);
            
            glUniform1f(glGetUniformLocation(myShader->ID, "lightP.constant"), light.constant);
            glUniform1f(glGetUniformLocation(myShader->ID, "lightP.linear"), light.linear);
            glUniform1f(glGetUniformLocation(myShader->ID, "lightP.quadratic"), light.quadratic);



            //glUniform3fv(glGetUniformLocation(myShader->ID, "material.ambient"), 1, glm::value_ptr(myMaterial->ambient));
            //glUniform3fv(glGetUniformLocation(myShader->ID, "material.diffuse"), 1, glm::value_ptr(myMaterial->diffuse));
            //glUniform3f(glGetUniformLocation(myShader->ID, "myMaterial.specular"), 1.0f, 1.0f, 1.0f);
            //glUniform1f(glGetUniformLocation(myShader->ID, "myMaterial.shininess"), 32.0f);
            myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
            myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
            myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
            myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);


            // Set Model
            glBindVertexArray(VAO);
            
            // Drawcall
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Clean up, prepare for next render loop
        glfwSwapBuffers(window);
        glfwPollEvents();
        camera.UpdateCameraPos();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Exit Program
    glfwTerminate();
    return 0;
}

