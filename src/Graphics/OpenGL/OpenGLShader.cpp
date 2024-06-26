#include "CrazyEngine/Graphics/OpenGL/OpenGLShader.h"

#include <fstream>
#include <sstream>
#include <string>

#include <Vendor/glad/glad.h>

namespace CrazyEngine
{
    OpenGLShader::OpenGLShader(const char* vertexFilePath, const char* fragmentFilePath, int textureSlots)
    {
        std::string vertexCode, fragCode;
        std::ifstream vertexFile, fragFile;

        try
        {
            // Reading Vertex Shader
            vertexFile.open(vertexFilePath);
            std::stringstream vertexStream;
            vertexStream << vertexFile.rdbuf();
            vertexFile.close();
            vertexCode = vertexStream.str();

            // Reading Fragment Shader
            fragFile.open(fragmentFilePath);
            std::stringstream fragStream;
            fragStream << fragFile.rdbuf();
            fragFile.close();
            fragCode = fragStream.str();
        }
        catch(const std::exception& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        const char* vertexCodeStr = vertexCode.c_str();
        const char* fragCodeStr = fragCode.c_str();

        int success;
        char infoLog[1024];

        // Vertex Shader Compilation

        unsigned int vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderHandle, 1, &vertexCodeStr, NULL);
        glCompileShader(vertexShaderHandle);
        glGetShaderiv(vertexShaderHandle, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(vertexShaderHandle, 1024, NULL, infoLog);
            std::cout << "Failed to compile vertex shader." << infoLog << std::endl;
            return;
        }

        // Fragment Shader Compilation

        unsigned int fragShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShaderHandle, 1, &fragCodeStr, nullptr); 
        glCompileShader(fragShaderHandle);
        glGetShaderiv(fragShaderHandle, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(fragShaderHandle, 1024, NULL, infoLog);
            std::cout << "Failed to compile fragment shader." << infoLog << std::endl;
            return;
        }

        // Create Shader Program

        m_ShaderID = glCreateProgram();
        glAttachShader(m_ShaderID, vertexShaderHandle);
        glAttachShader(m_ShaderID, fragShaderHandle);
        glLinkProgram(m_ShaderID);

        glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(m_ShaderID, 1024, nullptr, infoLog);
            std::cout << "Failed to link shaders." << std::endl;
            return;
        }

        // Shader Deletion

        glDeleteShader(vertexShaderHandle);
        glDeleteShader(fragShaderHandle);

        // Setting Texture Samplers

        if (textureSlots == 0)
        {
            return;
        }

        int* samplers = new int[textureSlots];
        for (int i = 0; i < textureSlots; ++i)
        {
            samplers[i] = i;
        }
        
        Bind();
        SetIntArray("u_Textures", textureSlots, samplers);
        Unbind();
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_ShaderID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_ShaderID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetBool(const char* name, bool value)
    {
        glUniform1i(glGetUniformLocation(m_ShaderID, name), (int)value); 
    }

    void OpenGLShader::SetInt(const char* name, int value)
    {
        glUniform1i(glGetUniformLocation(m_ShaderID, name), value); 
    }

    void OpenGLShader::SetIntArray(const char* name, const int count, int* value)
    {
        glUniform1iv(glGetUniformLocation(m_ShaderID, name), count, value); 
    }

    void OpenGLShader::SetFloat(const char* name, float value)
    {
        glUniform1f(glGetUniformLocation(m_ShaderID, name), value);
    }

    void OpenGLShader::SetFloat3(const char* name, float value1, float value2, float value3)
    {
        glUniform3f(glGetUniformLocation(m_ShaderID, name), value1, value2, value3);
    }

    void OpenGLShader::SetFloat2Array(const char* name, const int count, CrazyEngine::Vector2* value)
    {
        glUniform2fv(glGetUniformLocation(m_ShaderID, name), count, (float*)value);
    }

    void OpenGLShader::SetFloat3Array(const char* name, const int count, CrazyEngine::Vector3* value)
    {
        glUniform3fv(glGetUniformLocation(m_ShaderID, name), count, (float*)value);
    }

    void OpenGLShader::SetFloatArray(const char* name, const int count, float* value)
    {
        glUniform1fv(glGetUniformLocation(m_ShaderID, name), count, value);
    }

    void OpenGLShader::SetMatrix4(const char* name, const Matrix4& matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name), 1, GL_FALSE, (GLfloat*)&matrix);
    }
}