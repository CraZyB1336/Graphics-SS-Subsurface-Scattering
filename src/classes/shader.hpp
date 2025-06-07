#ifndef SHADER_HPP
#define SHADER_HPP
#pragma once

#include <glad/glad.h>

#include <cassert>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>

namespace Shader
{
    const std::string SHADER_VERSION = "#version 430 core";

    class Shader
    {
        private:
            GLuint  programID;
            GLint   status;
            GLint   length;

        public:
            Shader() {
                programID = glCreateProgram();
            }

            /**
             * @brief Activate the shader.
             */
            void activate()
            {
                glUseProgram(programID);
            }

            /**
             * @brief Deactivate the shader.
             */
            void deactivate()
            {
                glUseProgram(0);
            }

            /**
             * @brief Retrieve the program ID.
             * @return The program ID of the shader.
             */
            GLuint getProgramID()
            {
                return programID;
            }

            /**
             * @brief Remove the shader from memory.
             */
            void destroy()
            {
                glDeleteProgram(programID);
            }

            /**
             * @brief Turn source file to a char pointer.
             * @param filename The filename location of the source file.
             */
            std::string getSource(std::string const &filename)
            {
                std::ifstream fd(filename.c_str());

                if (fd.fail())
                {
                    fprintf(stderr, "Error locating shader file: \"%s\"\n", filename.c_str());
                    return nullptr;
                }

                std::string content(std::istreambuf_iterator<char>(fd), (std::istreambuf_iterator<char>()));

                std::istringstream iss(content);
                std::string line;
                std::string result;

                // Remove #version from file
                while (std::getline(iss, line))
                {
                    std::string trimmed = line;
                    trimmed.erase(0, trimmed.find_first_not_of(" \t"));

                    if (trimmed.find("#version") != 0)
                    {
                        result += line + "\n";
                    }
                }

                return result;
            }

            /**
             * @brief Attach a shader to the current shader program.
             * @param filename The shader file location.
             */
            void attach(std::string const &filename)
            {
                // Create shader object
                std::string sourceString = getSource(filename).c_str();
                attachWithSource(filename, sourceString, false);
            }

            /**
             * @brief Attach a shader to the current shader program.
             * @param filename The shader file location.
             * @param source The parsed shader source file.
             */
            void attachWithSource(std::string const &filename, std::string const &sourceFile, bool filenameIsExtension)
            {
                auto shader = create(filename, filenameIsExtension);
                std::string combinedWithVersion = SHADER_VERSION + '\n' + sourceFile;
                const char* source = combinedWithVersion.c_str();
                glShaderSource(shader, 1, &source, nullptr);
                glCompileShader(shader);

                // Display errors
                glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
                if (!status)
                {
                    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
                    std::unique_ptr<char[]> buffer(new char[length]);
                    glGetShaderInfoLog(shader, length, nullptr, buffer.get());
                    fprintf(stderr, "%s\n%s", filename.c_str(), buffer.get());
                }

                assert(status);
                
                // Attach and free memory.
                glAttachShader(programID, shader);
                glDeleteShader(shader);
            }

            /**
             * @brief Combines two source shader programs into one shader program.
             */
            std::string combine(std::string const &source1, std::string const &source2)
            {
                return source1 + source2;
            }

            /**
             * @brief Links all attached shaders into a shader program.
             */
            void link()
            {
                glLinkProgram(programID);

                glGetProgramiv(programID, GL_LINK_STATUS, &status);
                if (!status)
                {
                    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
                    std::unique_ptr<char[]> buffer(new char[length]);
                    glGetProgramInfoLog(programID, length, nullptr, buffer.get());
                    fprintf(stderr, "%s\n%s", buffer.get());
                }

                assert(status);
            }

            /**
             * @brief Easily retrieve a uniform location in this shader program.
             */
            GLuint getUniformFromName(std::string const &uniformName)
            {
                return glGetUniformLocation(programID,  uniformName.c_str());
            }
        
        private:
            GLuint create(std::string const &filename, bool filenameIsExtension)
            {
                std::string ext = filename;

                if (!filenameIsExtension)
                {
                    auto idx = filename.rfind(".");
                    ext = filename.substr(idx + 1);
                }

                if      (ext == "comp") return glCreateShader(GL_COMPUTE_SHADER);
                else if (ext == "frag") return glCreateShader(GL_FRAGMENT_SHADER);
                else if (ext == "vert") return glCreateShader(GL_VERTEX_SHADER);
                else                    return false;
            }
    };
};

#endif