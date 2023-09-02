#ifndef SHADER_H
# define SHADER_H

# include <GL/glew.h>
# include <string>
# include <iostream>
# include <fstream>
# include <glm.hpp>

class Shader
{
	public:
		Shader(const std::string &vertex_path, const std::string &fragment_path);
		~Shader(void);

		void use(void);

		void set_float(const std::string & name, float value) const;
		void set_vec4(const std::string & name, glm::vec4 vec) const;
		
	private:
		unsigned int _id;

		std::string readShaderFile(const std::string &path);
		void addShader(unsigned int id, const std::string &path, GLenum type);
};

#endif