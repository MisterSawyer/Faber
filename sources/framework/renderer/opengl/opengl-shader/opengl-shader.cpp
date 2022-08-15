#include "opengl-shader.h"
#include "../../../logger/logger.h" //TODO to trzeba dodaæ <>

fbr::opengl::ShaderOpenGL::ShaderOpenGL()
{
	m_programID = 0;
}

fbr::opengl::ShaderOpenGL::~ShaderOpenGL()
{
	Destroy();
}

bool fbr::opengl::ShaderOpenGL::Use()
{
	if (!Initialized()) {
		LOG_ERR("Shader program is not initialized");
		return false;
	}

	glUseProgram(m_programID);

	return true;
}

bool fbr::opengl::ShaderOpenGL::Destroy()
{
	if (m_programID == 0)
	{
		LOG_WAR("Destroying shader program of id 0?");
		return false;
	}

	glDeleteProgram(m_programID);
	m_programID = 0;

	return true;
}

bool fbr::opengl::ShaderOpenGL::Compile()
{
	if (!CompilePipeline())
	{
		LOG_ERR("Shader pipeline is not properly initialized");
		return false;
	}

	if (ShaderOpenGL::Initialized())
	{
		LOG_WAR("Shader program already compiled");
		return true;
	}

	m_programID = glCreateProgram();

	for (auto & stage : GetPipeline())
	{
		glAttachShader(m_programID, stage->GetID());
	}

	GLchar	errors_log[1024];
	GLint	result;

	glLinkProgram(m_programID);
	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);


	if (!result)
	{
		glGetProgramInfoLog(m_programID, 1024, nullptr, errors_log);

		LOG_ERR("Shader program linking error" << errors_log);

		glDeleteProgram(m_programID);
		m_programID = 0;

		return false;
	}

	//SUCCESS
	SetAsInitialized();
	return true;
}


