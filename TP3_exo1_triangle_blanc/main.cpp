#include "glimac/default_shader.hpp"
#include "p6/p6.h"

int main()
{
    auto ctx = p6::Context{{1280, 720, "TP3 EX1"}};
    ctx.maximize_window();

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    // Buffer
    //  Initialization buffer
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Binding buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Fill buffer
    //  Creation tab of float containing coordinates of my points
    GLfloat vertices[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f, 0.5f
    };
    // Sending the data
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    // Unbinding the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // VAO
    // Creation VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);

    // Binding VAO
    glBindVertexArray(vao);

    // Activation vertex
    static constexpr GLuint vertex_attr_position = 0;
    glEnableVertexAttribArray(vertex_attr_position);
    // //Re-Binding vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(vertex_attr_position, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

    // Unbinding Buffer & VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Declare your infinite update loop.
    ctx.update = [&]() {
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        // Clear the window
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind VAO
        glBindVertexArray(vao);

        // Shader
        glimac::bind_default_shader();
        //  Draw triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Unbind vao
        glBindVertexArray(0);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}