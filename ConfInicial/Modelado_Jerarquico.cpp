
/*
Pr�ctica 5
Mart�nez Pav�n Mar�a Guadalupe
318071280
Fecha de entrega: 5-marzo-2025
*/

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//For model
float	hombro = 0.0f;
float codo = 0.0f;
float mu�eca = 0.0f;
float dedo1 = 0.0f;
float dedo2 = 0.0f;
float dedo3 = 0.0f; 

int main() {
    glfwInit();
    //Verificaci�n de compatibilidad 
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Pr�ctica 5. Maria Guadalupe Martinez Pavon", nullptr, nullptr);

    int screenWidth, screenHeight;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    //Verificaci�n de errores de creacion  ventana
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    //Verificaci�n de errores de inicializaci�n de glew

    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }


    // Define las dimensiones del viewport
    glViewport(0, 0, screenWidth, screenHeight);


    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);

    // enable alpha support
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Build and compile our shader program
    Shader ourShader("Shader/core.vs", "Shader/core.frag");


    // Set up vertex data (and buffer(s)) and attribute pointers
    // use with Orthographic Projection


    

    // use with Perspective Projection
    float vertices[] = {
        -0.5f, -0.5f, 0.5f, 
        0.5f, -0.5f, 0.5f,  
        0.5f,  0.5f, 0.5f,  
        0.5f,  0.5f, 0.5f,  
        -0.5f,  0.5f, 0.5f, 
        -0.5f, -0.5f, 0.5f, 
        
        -0.5f, -0.5f,-0.5f, 
         0.5f, -0.5f,-0.5f, 
         0.5f,  0.5f,-0.5f, 
         0.5f,  0.5f,-0.5f, 
        -0.5f,  0.5f,-0.5f, 
        -0.5f, -0.5f,-0.5f, 
        
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  -0.5f, 0.5f,
      
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f,  0.5f, 
        0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };




    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    // Enlazar  Vertex Array Object
    glBindVertexArray(VAO);

    //2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    

    //Posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

    
    glm::mat4 projection=glm::mat4(1);

    projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
    glm::vec3 color= glm::vec3(0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {

        Inputs(window);
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        ourShader.Use();
        glm::mat4 model = glm::mat4(1);
        glm::mat4 view = glm::mat4(1);
        glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
        glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp



        //View set up 
        view = glm::translate(view, glm::vec3(movX, movY, movZ));
        view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
        GLint uniformColor = ourShader.uniformColor;

        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));


        glBindVertexArray(VAO);

        //Model 
        model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //hombro
        modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
        color = glm::vec3(0.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A

        //Model Antebrazo 
        model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0));
        model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
        color = glm::vec3(1.0f, 0.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//B

        //Model palma 
        model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(mu�eca), glm::vec3(1.0f, 0.0, 0.0f));
        modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//C

        // Dedo 1 A (�ndice)
        model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.35f, 0.45f));
        model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.6f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.2f, 0.25f, 0.25f));
        color = glm::vec3(0.0f, 1.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Dedo 1 B
        model = glm::translate(modelTemp, glm::vec3(0.6f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.8f, 0.25f, 0.25f));
        color = glm::vec3(1.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Dedo 1 C 
        model = glm::translate(modelTemp, glm::vec3(0.4f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0, 1.0f));
        model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.6f, 0.25f, 0.25f));
        color = glm::vec3(1.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Dedo 2 A(Medio)
        model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.35f, 0.18f));
        model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.75f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.5f, 0.25f, 0.25f));
        color = glm::vec3(0.0f, 1.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        
        // Dedo 2B
        model = glm::translate(modelTemp, glm::vec3(0.75f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.25f, 0.25f));
        color = glm::vec3(1.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color)); 
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Dedo 2 C
        model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f)); 
        model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0, 1.0f)); 
        model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(0.7f, 0.25f, 0.25f));
        color = glm::vec3(1.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color)); 
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

         //Dedo 3 A (Anular)
        model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.35f, -0.1f));
        model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.7f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.4f, 0.25f, 0.25f));
        color = glm::vec3(0.0f, 1.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

         // Dedo 3 B
        model = glm::translate(modelTemp, glm::vec3(0.7f, 0.0f, 0.0f)); 
        model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0, 1.0f)); 
        modelTemp = model = glm::translate(model, glm::vec3(0.45f, 0.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(0.9f, 0.25f, 0.25f));
        color = glm::vec3(1.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color)); 
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Dedo 3 C
        model = glm::translate(modelTemp, glm::vec3(0.45f, 0.0f, 0.0f)); 
        model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0, 1.0f)); 
        model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(0.6f, 0.25f, 0.25f));
        color = glm::vec3(1.0f, 1.0f, 0.0f); 
        glUniform3fv(uniformColor, 1, glm::value_ptr(color)); 
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Dedo 4 A (Me�ique)
        model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.35f, -0.39f));
        model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.25f, 0.25f));
        color = glm::vec3(0.0f, 1.0f, 1.0f); 
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Dedo 4 B
        model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f)); 
        model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0, 1.0f)); 
        modelTemp = model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.7f, 0.25f, 0.25f));
        color = glm::vec3(1.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Dedo 4 C 
        model = glm::translate(modelTemp, glm::vec3(0.35f, 0.0f, 0.0f)); 
        model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0, 1.0f)); 
        model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(0.5f, 0.25f, 0.25f));
        color = glm::vec3(1.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //PULGAR A
        model = glm::translate(modelTemp2, glm::vec3(0.1f, -0.2f, 0.5f)); 
        model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0, 1.0f)); 
        modelTemp = model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(0.8f, 0.25f, 0.25f));
        color = glm::vec3(0.0f, 1.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color)); 
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Dedo 5 B 
        model = glm::translate(modelTemp, glm::vec3(0.4f, 0.0f, 0.0f)); 
        model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0, 1.0f)); 
        model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(0.6f, 0.25f, 0.25f));
        color = glm::vec3(1.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        
        // Swap the screen buffers
        glfwSwapBuffers(window);
    
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);


    glfwTerminate();
    return EXIT_SUCCESS;
 }

void Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movX += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movX -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        movY += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        movY -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movZ -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movZ += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rot += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rot -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        hombro += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        hombro -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        codo += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        codo -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        mu�eca += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        mu�eca -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        if (dedo1 < 45.0f) { dedo1 += 0.5f; }
        else { dedo1 += 0.0f; }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        if (dedo1 > -35.f) { dedo1 -= 0.5f; }
        else { dedo1 -= 0.0f; }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        if (dedo2 < 0.0f) { dedo2 += 0.5f; }
        else { dedo2 += 0.0f; }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        if (dedo2 > -90.f) { dedo2 -= 0.5f; }
        else { dedo2 -= 0.0f; }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        dedo3 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        dedo3 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        if (dedo3 < 30.0f) { dedo3 += 0.5f; } 
        else { dedo3 += 0.0f; }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        if (dedo3 > 0.0f) { dedo3 -= 0.5f; } 
        else { dedo3 -= 0.0f; }
}