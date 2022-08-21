#pragma once
#include <glew-2.1.0/include/GL/glew.h>
#include <faber/renderer/shader/shader-stage.h>

namespace fbr::opengl
{
	class ShaderStageOpenGL : public IShaderStage
	{
	public:
		ShaderStageOpenGL(ShaderStageType type, const std::string& code);
		ShaderStageOpenGL(ShaderStageType type, std::string&& code) noexcept;

		ShaderStageOpenGL(const ShaderStageOpenGL & other);
		ShaderStageOpenGL(ShaderStageOpenGL && other) noexcept;

		ShaderStageOpenGL& operator=(const ShaderStageOpenGL & other);
		ShaderStageOpenGL& operator=(ShaderStageOpenGL && other) noexcept;


		virtual ~ShaderStageOpenGL();

		bool Compile() override;
		bool Destroy() override;

		const GLuint& GetID() const;
	private:
		GLuint m_stageID;
	};
}