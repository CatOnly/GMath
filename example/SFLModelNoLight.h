#ifndef SFLMODELSNOLIGHT_H
#define SFLMODELSNOLIGHT_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewNoLight.h"
#include <QImage>
#include <QCoreApplication>
#include <QDebug>

class SFLModelNoLight: public SFLModelAbstract
{
public:
    SFLModelNoLight():SFLModelAbstract(){
        _btn->setText("基本操作");
        _view = new SFLViewNoLight(this);
//        _rotateAngle = glm::vec3(0.0, 0.0, 0.0);
//        _scale = glm::vec3(1.0, 1.0, 1.0);s
//        _move = glm::vec3(0.0, 0.0, 0.0);

        setHasTexture(false);
        setHasRightDirection(false);
        setIsOnlyDrawLine(false);
    }
    ~SFLModelNoLight(){
        if (!_hasInitialized) return;

        glDeleteProgram(_programID);
        glDeleteVertexArrays(1, &_vertexArrayObjRef);
        glDeleteBuffers(1, &_vertexBufferObjRef);
        glDeleteBuffers(1, &_elementBufferObjRef);
        glDeleteTextures(1, &_texture2DRef);
    }

    void initializeOpenGL() override {
        _programID = glCreateProgram();

        glGenVertexArrays(1, &_vertexArrayObjRef);
        glGenBuffers(1, &_vertexBufferObjRef);
        glGenBuffers(1, &_elementBufferObjRef);
        glGenTextures(1, &_texture2DRef);

        // order is not important
        setupTexture2D();
        setupShader();
        setupVertexArrayObject();

        // Bind Textures using texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture2DRef);
        glUniform1i(glGetUniformLocation(_programID, "ourTexture"), 0);
    }

    void render() override {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glUseProgram(_programID);
        glUniform1f(glGetUniformLocation(_programID, "hasRightDir"), _hasRightDirection ? 1.0f : 0.0f);
        glUniform1f(glGetUniformLocation(_programID, "colorWeight"), _mixColorWeight);

//        glm::mat4 transform(1.0);
//        transform = glm::rotate(transform, _rotateAngle.x, glm::vec3(1.0, 0.0, 0.0));
//        transform = glm::rotate(transform, _rotateAngle.y, glm::vec3(0.0, 1.0, 0.0));
//        transform = glm::rotate(transform, _rotateAngle.z, glm::vec3(0.0, 0.0, 1.0));
//        transform = glm::scale(transform, _scale);
//        transform = glm::translate(transform, _move);
//        transform = glm::perspective(_viewAngle, 1.0f, _viewFront, _viewFarther) * _delegateCamaera->viewMatrix() * transform;
//        glUniformMatrix4fv(glGetUniformLocation(_programID, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

        if (_hasTexture){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _texture2DRef);
        } else {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        glPolygonMode(GL_FRONT_AND_BACK, _isOnlyDrawLine ? GL_LINE : GL_FILL);
        glBindVertexArray(_vertexArrayObjRef);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void setRotate(double x, double y, double z){
//        _rotateAngle = glm::vec3((float)x, (float)y, (float)z);
    }
    void setScale(double x, double y, double z){
//        _scale = glm::vec3((float)x, (float)y, (float)z);
    }
    void setMove(double x, double y, double z){
//        _move = glm::vec3((float)x, (float)y, (float)z);
    }

    void setHasTexture(bool hasTexture){
        _hasTexture = hasTexture;
    }
    void setHasRightDirection(bool hasRightDir){
        _hasRightDirection = hasRightDir;
    }
    void setMixColorWeight(float weight){
        _mixColorWeight = weight;
    }
    float coloWeight(){
        return _mixColorWeight;
    }
    void setIsOnlyDrawLine(bool isDrawLine){
        _isOnlyDrawLine = isDrawLine;
    }
    void setViewAngle(GLfloat angle){
        _viewAngle = angle;
    }
    void setViewFront(GLfloat front){
        _viewFront = front;
    }
    void setViewFarther(GLfloat farther){
        _viewFarther = farther;
    }

private:
    bool _isOnlyDrawLine;
    bool _hasTexture;
    bool _hasRightDirection;
    float _mixColorWeight = 0.4;
//    glm::vec3 _rotateAngle;
//    glm::vec3 _scale;
//    glm::vec3 _move;
    GLfloat _viewAngle = 45.0;
    GLfloat _viewFront = 0.1;
    GLfloat _viewFarther = 100.0;

    GLuint _vertexArrayObjRef = 0;   // 顶点数组对象，储存 顶点属性
    GLuint _vertexBufferObjRef = 0;  // 顶点缓冲对象
    GLuint _elementBufferObjRef = 0; // 索引缓冲对象
    GLuint _texture2DRef = 0;
    GLuint _programID = 0;

    void setupVertexArrayObject() {
        // 3  ->  0
        // ^ |\   |
        // |   \  v
        // 2  <-  1
        GLfloat vertices[] = {
                // Positions          // Colors           // Texture Coords
                 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
                 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
                -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
        };

        GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        glBindVertexArray(_vertexArrayObjRef);

        glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjRef);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObjRef);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        // TexCoord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0); // Unbind VAO
    }

    void setupShader() {
        using namespace std;

        const char * shaderSrcVertex = "#version 330 core\
                                       precision mediump float;\
        layout (location = 0) in vec3 position;\
        layout (location = 1) in vec3 color;\
        layout (location = 2) in vec2 texCoord;\
        out vec3 ourColor;\
        out vec2 TexCoord;\
        uniform float hasRightDir;\
        uniform mat4 transform;\
        void main(){\
            gl_Position = transform * vec4(position, 1.0);\
            ourColor = color;\
            TexCoord = (hasRightDir == 1.0 ? vec2(texCoord.x, 1.0 - texCoord.y) : texCoord);\
        }";
        const char * shaderSrcFragment = "#version 330 core\
        in vec3 ourColor;\
        in vec2 TexCoord;\
        out vec4 color;\
        \
        uniform float colorWeight;\
        uniform sampler2D ourTexture;\
        \
        void main() {\
            color = mix(texture(ourTexture, TexCoord), vec4(ourColor, 1.0), colorWeight);\
        }";

        GLuint shaderVertex = loadShader(GL_VERTEX_SHADER, shaderSrcVertex);
        GLuint shaderFragment = loadShader(GL_FRAGMENT_SHADER, shaderSrcFragment);
        glAttachShader(_programID, shaderVertex);
        glAttachShader(_programID, shaderFragment);
        glLinkProgram(_programID);

        GLint success;
        const GLsizei bufferSize = 512;
        GLchar inforLog[bufferSize];
        glGetProgramiv(_programID, GL_LINK_STATUS, &success);
        if (!success){
            glGetProgramInfoLog(_programID, bufferSize, NULL, inforLog);
            qDebug() << "Error: Shader program link " << inforLog << endl;
        }

        glDeleteShader(shaderVertex);
        glDeleteShader(shaderFragment);
    }

    void setupTexture2D() {
        glActiveTexture(GL_TEXTURE0); // 默认激活可不写
        glBindTexture(GL_TEXTURE_2D, _texture2DRef);
        // Set our texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //
        // Set texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load, create texture and generate mipmaps
        QImage qImage(QString(":/theCat.jpg"));
        int width = qImage.width();
        int height = qImage.height();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, qImage.bits());
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLuint loadShader(GLenum type, const char *shaderSrc){
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &shaderSrc, NULL);
        glCompileShader(shader);

        GLint success;
        const GLsizei bufferSize = 512;
        GLchar inforLog[bufferSize];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(shader, bufferSize, NULL, inforLog);
            qDebug() << "Error: Shader compile " << (type == GL_VERTEX_SHADER ? "vertex" :"fragment") << inforLog << endl;
        }

        return shader;
    }
};

#endif // SFLMODELSNOLIGHT_H
