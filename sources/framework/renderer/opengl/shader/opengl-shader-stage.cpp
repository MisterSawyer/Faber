#include "opengl-shader-stage.h"
#include "../../../logger/logger.h" //TODO to trzeba dodaæ <>

fbr::ShaderStageOpenGL::ShaderStageOpenGL(ShaderStageType type, const std::string& code) : ShaderStage(type, code)
{
	m_stageID = 0;
}

fbr::ShaderStageOpenGL::ShaderStageOpenGL(ShaderStageType type, std::string&& code) noexcept : ShaderStage(type, std::move(code))
{
	m_stageID = 0;
}

fbr::ShaderStageOpenGL::ShaderStageOpenGL(const ShaderStageOpenGL & other) : ShaderStage(other)
{
	m_stageID = 0;
}

fbr::ShaderStageOpenGL::ShaderStageOpenGL(ShaderStageOpenGL&& other) noexcept : ShaderStage(std::move(other))
{
	m_stageID = 0;
}

fbr::ShaderStageOpenGL& fbr::ShaderStageOpenGL::operator=(const ShaderStageOpenGL& other)
{
	if (*this == other)return *this;
	Destroy();

	ShaderStage::operator=(other);

	return *this;
}

fbr::ShaderStageOpenGL& fbr::ShaderStageOpenGL::operator=(ShaderStageOpenGL && other) noexcept
{
	if (*this == other)return *this;
	Destroy();

	ShaderStage::operator=(std::move(other));

	return *this;
}

fbr::ShaderStageOpenGL::~ShaderStageOpenGL()
{
	Destroy();
	m_stageID = 0;
}

bool fbr::ShaderStageOpenGL::Compile()
{
	if (Initialized())
	{
		LOG_INF("Shader stage already compiled");
		return true;
	}

	switch (GetType())
	{
	case fbr::ShaderStageType::VERTEX_SHADER:			{	m_stageID = glCreateShader(GL_VERTEX_SHADER); break; }
	case fbr::ShaderStageType::TESS_CONTROL_SHADER:		{	m_stageID = glCreateShader(GL_TESS_CONTROL_SHADER); break; }
	case fbr::ShaderStageType::TESS_EVALUATION_SHADER:	{	m_stageID = glCreateShader(GL_TESS_EVALUATION_SHADER); break; }
	case fbr::ShaderStageType::GEOMETRY_SHADER:			{	m_stageID = glCreateShader(GL_GEOMETRY_SHADER); break; }
	case fbr::ShaderStageType::FRAGMENT_SHADER:			{	m_stageID = glCreateShader(GL_FRAGMENT_SHADER); break; }
	case fbr::ShaderStageType::COMPUTE_SHADER:			{	m_stageID = glCreateShader(GL_COMPUTE_SHADER); break; }
	default: {LOG_ERR("Unrecognized shader type");  return false; }
	}


	const GLchar* gl_code = GetCode().c_str();

	GLchar	errors_log[1024];
	GLint	result;

	glShaderSource(m_stageID, 1, &gl_code, nullptr);
	glCompileShader(m_stageID);
	glGetShaderiv(m_stageID, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(m_stageID, 1024, nullptr, errors_log);

		LOG_ERR("Compiling shader error\n" << errors_log);

		glDeleteShader(m_stageID);

		return false;
	}

	//SUCCESS
	SetAsInitialized();

	return true;
}

bool fbr::ShaderStageOpenGL::Destroy()
{
	bool initialized = Initialized();

	// Destroy data 
	ShaderStage::Destroy();

	//shader stage was not compiled (purly data storage)
	if (!initialized)return true;


	// shader was compiled
	if (m_stageID == 0)
	{
		//weird????
		LOG_ERR("Destroying shadewr stage of id 0?");
		return false;
	}

	glDeleteProgram(m_stageID);
	m_stageID = 0;

	return true;
}

const GLuint& fbr::ShaderStageOpenGL::GetID() const
{
	return m_stageID;
}
