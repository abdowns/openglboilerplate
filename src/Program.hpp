#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "Shader.hpp"


class Program {
    public:
        // fields
        Shader* vertexShader;
        Shader* fragmentShader;
        unsigned int id;
        bool isLinked;

        // methods
        Program();
        ~Program();

        void setVertexShader(Shader* shader);
        void setFragmentShader(Shader* shader);
        void linkProgram();

        std::string getLinkingErrors();

        void use();
    
    private:
        bool printErrors;
};

#endif // PROGRAM_HPP