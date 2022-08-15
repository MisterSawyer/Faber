#pragma once
#include <string>

namespace fbr
{
	enum class ShaderStageType : unsigned int
	{
		UNDEFINED = 0,
		VERTEX_SHADER,
		TESS_CONTROL_SHADER,
		TESS_EVALUATION_SHADER,
		GEOMETRY_SHADER,
		FRAGMENT_SHADER,
		COMPUTE_SHADER
	};

	class ShaderStage
	{
	public:
		virtual ~ShaderStage();

		ShaderStage(ShaderStageType type, const std::string& code);
		ShaderStage(ShaderStageType type, std::string && code) noexcept;

		bool operator == (const ShaderStage & rhs)const;
		bool operator != (const ShaderStage& rhs)const;

		bool Initialized() const;

		virtual bool Compile() = 0;
		virtual bool Destroy();

	protected:
		ShaderStage(const ShaderStage& other);
		ShaderStage(ShaderStage&& other) noexcept;
		ShaderStage& operator=(const ShaderStage& other);
		ShaderStage& operator=(ShaderStage&& other) noexcept;

		const ShaderStageType& GetType() const;
		const std::string& GetCode() const;
		void SetAsInitialized();

	private:
		ShaderStageType m_type;
		std::string m_code;

		bool m_initialized;
	};
}