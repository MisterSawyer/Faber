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

	class IShaderStage
	{
	public:
		virtual ~IShaderStage();

		IShaderStage(ShaderStageType type, const std::string& code);
		IShaderStage(ShaderStageType type, std::string && code) noexcept;

		bool operator == (const IShaderStage& rhs)const;
		bool operator != (const IShaderStage& rhs)const;

		bool Initialized() const;

		virtual bool Compile() = 0;
		virtual bool Destroy();

	protected:
		IShaderStage(const IShaderStage& other);
		IShaderStage(IShaderStage&& other) noexcept;
		IShaderStage& operator=(const IShaderStage& other);
		IShaderStage& operator=(IShaderStage&& other) noexcept;

		const ShaderStageType& GetType() const;
		const std::string& GetCode() const;
		void SetAsInitialized();

	private:
		ShaderStageType m_type;
		std::string m_code;

		bool m_initialized;
	};
}