#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace Spoonity {

    //Vertex data
    struct Vertex
    {
        //Position
        glm::vec3 Position;
        //Normal
        glm::vec3 Normal;
        //TexCoords
        glm::vec2 TexCoords;
        //Tangent
        glm::vec3 Tangent;
        //Bitangent
        glm::vec3 Bitangent;
    };

    //Texture data
    struct Texture
    {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh {

    //Variables
    private:
        //Mesh Data
        std::vector<Vertex> _Vertices;
        std::vector<unsigned int> _Indices;
        std::vector<Texture> _Textures;
        unsigned int _VAO, _VBO, _EBO;

    //Functions
    public:

        //Constructor
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

        //Render the mesh
        void Draw(Shader shader) const;

    private:

        //Initializes all the buffer objects/arrays
        void setupMesh();
    };
}