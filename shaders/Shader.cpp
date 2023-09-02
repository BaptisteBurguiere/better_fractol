#include <Shader.h>

Shader::Shader(const std::string &vertex_path, const std::string &fragment_path)
{
	this->_id = glCreateProgram();

	this->addShader(this->_id, vertex_path, GL_VERTEX_SHADER);
	this->addShader(this->_id, fragment_path, GL_FRAGMENT_SHADER);

	glLinkProgram(this->_id);

	int success;
	char message[512];
	glGetProgramiv(this->_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->_id, 512, NULL, message);
		std::cout << "Error linking shader program: " << message << std::endl;
	}
}

Shader::~Shader(void)
{
	if (this->_id != 0)
		glDeleteProgram(this->_id);
}

void Shader::use(void)
{
	glUseProgram(this->_id);
}

std::string Shader::readShaderFile(const std::string &path)
{
	std::string content;
	std::ifstream file(path, std::ios::in);

	if (!file)
	{
		std::cout << "Failed to open shader file: " << path << std::endl;
		return "";
	}

	std::string line = "";
	while (std::getline(file, line))
		content.append(line + '\n');

	file.close();
	return content;
}

void Shader::addShader(unsigned int id, const std::string &path, GLenum type)
{
	std::string content = this->readShaderFile(path);

	const GLchar *code[1];
	code[0] = content.c_str();

	GLint code_length[1];
	code_length[0] = (GLint)content.length();

	unsigned int shader;
	int success;
	char message[512];

	shader = glCreateShader(type);
	glShaderSource(shader, 1, code, code_length);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 521, NULL, message);
		std::cout << "Error compiling shader: " << message << std::endl;
		std::cout << "Shader location: " << path << std::endl;
	}
	glAttachShader(id, shader);
}

void Shader::set_float(const std::string & name, float value) const
{
    glUniform1f(glGetUniformLocation(this->_id, name.c_str()), value);
}
 
void Shader::set_vec4(const std::string & name, glm::vec4 vec) const
{
    glUniform4f(glGetUniformLocation(this->_id, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}