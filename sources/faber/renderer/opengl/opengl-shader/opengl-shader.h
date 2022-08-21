#pragma once
#include <glew-2.1.0/include/GL/glew.h> // TODO erase ??

#include <faber/renderer/shader/shader.h>
#include <faber/renderer/opengl/opengl-shader/opengl-shader-stage.h>

namespace fbr::opengl
{
	class ShaderOpenGL : public IShaderProgram<ShaderStageOpenGL>
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