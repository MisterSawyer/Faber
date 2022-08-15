#pragma once
#include <GL/glew.h>
#include "../../shader/shader.h"
#include "opengl-shader-stage.h"

namespace fbr
{
	class ShaderOpenGL : public ShaderProgram<ShaderStageOpenGL>
	{
	public:
		ShaderOpenGL();

		//TODO copy pipeline
		ShaderOpenGL(const ShaderOpenGL& other) = delete;
		virtual ~ShaderOpenGL();

		bool Compile() override;
		bool Use() override;
		bool Destroy() override;

	private:
		GLuint m_programID;
	};
}