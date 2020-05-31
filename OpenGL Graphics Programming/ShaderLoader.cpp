#include "ShaderLoader.h" 
#include <fstream>
#include <vector>


GLuint ShaderLoader::CreateProgram(const char* _vertexShaderFilename, const char* _fragmentShaderFilename)
{
	GLuint program = glCreateProgram();

	const GLuint vertexID = CreateShader(GL_VERTEX_SHADER, _vertexShaderFilename);
	const GLuint fragmentID = CreateShader(GL_FRAGMENT_SHADER, _fragmentShaderFilename);

	std::string ID = std::to_string(vertexID) + "_" + std::to_string(fragmentID);
	
	GLCall(glAttachShader(program, vertexID));
	GLCall(glAttachShader(program, fragmentID));

	glLinkProgram(program);

	const auto shader = m_shaderMap->find(program);

	if (shader != m_shaderMap->end() && shader->second == ID)
	{
		std::cout << "Shader has already been compiled before!" << std::endl;
		return shader->first;
	}

	// Check for link errors
	int link_result = 0;
	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &link_result));
	if (link_result == GL_FALSE)
	{
		std::string programName = _vertexShaderFilename + *_fragmentShaderFilename;
		PrintErrorDetails(false, program, programName.c_str());
		return 0;
	}
	m_shaderMap->insert(std::pair<GLuint, std::string>(program, ID));
	return program;
}

GLuint ShaderLoader::CreateProgram(const char* _vertexShaderFilename, const char* _geometryShaderFilename, const char* _fragmentShaderFilename)
{
	GLuint program = glCreateProgram();

	const GLuint vertexID = CreateShader(GL_VERTEX_SHADER, _vertexShaderFilename);
	const GLuint geometryID = CreateShader(GL_GEOMETRY_SHADER, _geometryShaderFilename);
	const GLuint fragmentID = CreateShader(GL_FRAGMENT_SHADER, _fragmentShaderFilename);
	

	std::string ID = std::to_string(vertexID) + "_" + std::to_string(geometryID) + "_" + std::to_string(fragmentID);

	GLCall(glAttachShader(program, vertexID));
	GLCall(glAttachShader(program, geometryID));
	GLCall(glAttachShader(program, fragmentID));
	

	glLinkProgram(program);

	const auto shader = m_shaderMap->find(program);

	if (shader != m_shaderMap->end() && shader->second == ID)
	{
		std::cout << "Shader has already been compiled before!" << std::endl;
		return shader->first;
	}

	// Check for link errors
	int link_result = 0;
	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &link_result));
	if (link_result == GL_FALSE)
	{
		std::string programName = _vertexShaderFilename  + *_geometryShaderFilename + *_fragmentShaderFilename;
		PrintErrorDetails(false, program, programName.c_str());
		return 0;
	}
	m_shaderMap->insert(std::pair<GLuint, std::string>(program, ID));
	return program;
}

GLuint ShaderLoader::CreateProgram(const char* _vertexShaderFilename, const char* _tessellationControlShaderFilename,
	                               const char* _tessellationEvaluationShaderFilename, const char* _fragmentShaderFilename)
{
	GLuint program = glCreateProgram();

	const GLuint vertexID = CreateShader(GL_VERTEX_SHADER, _vertexShaderFilename);
	const GLuint tesselationControlID = CreateShader(GL_TESS_CONTROL_SHADER, _tessellationControlShaderFilename);
	const GLuint tesselationEvaluationID = CreateShader(GL_TESS_EVALUATION_SHADER, _tessellationEvaluationShaderFilename);
	const GLuint fragmentID = CreateShader(GL_FRAGMENT_SHADER, _fragmentShaderFilename);


	std::string ID = std::to_string(vertexID) + "_" + std::to_string(tesselationControlID) + "_" + std::to_string(tesselationEvaluationID) + "_" + std::to_string(fragmentID);

	GLCall(glAttachShader(program, vertexID));
	GLCall(glAttachShader(program, tesselationControlID));
	GLCall(glAttachShader(program, tesselationEvaluationID));
	GLCall(glAttachShader(program, fragmentID));


	glLinkProgram(program);

	const auto shader = m_shaderMap->find(program);

	if (shader != m_shaderMap->end() && shader->second == ID)
	{
		std::cout << "Shader has already been compiled before!" << std::endl;
		return shader->first;
	}

	// Check for link errors
	int link_result = 0;
	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &link_result));
	if (link_result == GL_FALSE)
	{
		std::string programName = _vertexShaderFilename
		                          + *_tessellationControlShaderFilename
		                          + *_tessellationEvaluationShaderFilename
		                          + *_fragmentShaderFilename;
		PrintErrorDetails(false, program, programName.c_str());
		return 0;
	}
	m_shaderMap->insert(std::pair<GLuint, std::string>(program, ID));
	return program;
}

GLuint ShaderLoader::CreateProgram(const char* _vertexShaderFilename, const char* _tessellationControlShaderFilename,
	                               const char* _tessellationEvaluationShaderFilename, const char* _geometryShaderFilename,
	                               const char* _fragmentShaderFilename)
{
	GLuint program = glCreateProgram();

	const GLuint vertexID = CreateShader(GL_VERTEX_SHADER, _vertexShaderFilename);
	const GLuint tessellationControlID = CreateShader(GL_TESS_CONTROL_SHADER, _tessellationControlShaderFilename);
	const GLuint tessellationEvaluationID = CreateShader(GL_TESS_EVALUATION_SHADER, _tessellationEvaluationShaderFilename);
	const GLuint geometryID = CreateShader(GL_GEOMETRY_SHADER, _geometryShaderFilename);
	const GLuint fragmentID = CreateShader(GL_FRAGMENT_SHADER, _fragmentShaderFilename);

	std::string ID = std::to_string(vertexID) + "_" + std::to_string(tessellationControlID) + "_" + std::to_string(tessellationEvaluationID) + "_" + std::to_string(geometryID) + "_" + std::to_string(fragmentID);

	GLCall(glAttachShader(program, vertexID));
	GLCall(glAttachShader(program, tessellationControlID));
	GLCall(glAttachShader(program, tessellationEvaluationID));
	GLCall(glAttachShader(program, geometryID));
	GLCall(glAttachShader(program, fragmentID));

	glLinkProgram(program);

	const auto shader = m_shaderMap->find(program);

	if (shader != m_shaderMap->end() && shader->second == ID)
	{
		std::cout << "Shader has already been compiled before!" << std::endl;
		return shader->first;
	}

	// Check for link errors
	int link_result = 0;
	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &link_result));
	if (link_result == GL_FALSE)
	{
		std::string programName = _vertexShaderFilename
			+ *_tessellationControlShaderFilename
			+ *_tessellationEvaluationShaderFilename
			+ *_geometryShaderFilename
			+ *_fragmentShaderFilename;
		PrintErrorDetails(false, program, programName.c_str());
		return 0;
	}
	m_shaderMap->insert(std::pair<GLuint, std::string>(program, ID));
	return program;
}

GLuint ShaderLoader::CreateShader(GLenum shaderType, const char* shaderName)
{
	//Create Shader
	const GLuint shaderID = glCreateShader(shaderType);

	std::string strShader = ReadShaderFile(shaderName);
	const char* cstrShader = strShader.c_str();

	GLCall(glShaderSource(shaderID, 1, &cstrShader, nullptr)); //Source string is already null terminating, so length can be nullptr

	GLCall(glCompileShader(shaderID));

	// Check for errors
	int compile_result = 0;
	GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compile_result));
	if (compile_result == GL_FALSE)
	{
		PrintErrorDetails(true, shaderID, shaderName);
		system("pause");
		return 0;
	}
	return shaderID;
}

std::string ShaderLoader::ReadShaderFile(const char *filename)
{
	// Open the file for reading
	std::ifstream file(filename, std::ios::in);
	std::string shaderCode;

	// Ensure the file is open and readable
	if (!file.good()) {
		std::cout << "Cannot read file:  " << filename << std::endl;
		return "";
	}

	// Determine the Size of of the file in m_characters and resize the string variable to accomodate
	file.seekg(0, std::ios::end);
	shaderCode.resize(static_cast<unsigned int>(file.tellg()));

	// Set the m_position of the next character to be read back to the beginning
	file.seekg(0, std::ios::beg);
	// Extract the contents of the file and store in the string variable
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

void ShaderLoader::PrintErrorDetails(bool isShader, GLuint id, const char* name)
{
	int infoLogLength = 0;
	// Retrieve the length of m_characters needed to contain the info log
	(isShader) ? glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength) : glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

	//Dynamically assign a char* string on the stack to be used for error message printing
	char* log = static_cast<char*>(alloca(static_cast<size_t>(infoLogLength * sizeof(char))));

	// Retrieve the log info and populate log variable
	(isShader) ? glGetShaderInfoLog(id, infoLogLength, nullptr, log) : glGetProgramInfoLog(id, infoLogLength, nullptr, log);
	std::cout << "Error compiling " << ((isShader) ? "shader" : "m_program") << ": " << name << std::endl;
	std::cout << log << std::endl;
}