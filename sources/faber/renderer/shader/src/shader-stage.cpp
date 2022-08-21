#include <faber/renderer/shader/shader-stage.h>

fbr::IShaderStage::~IShaderStage()
{
	Destroy();
}

fbr::IShaderStage::IShaderStage(ShaderStageType type, const std::string& code) :
	m_type(type),
	m_code(code),
	m_initialized(false)
{
}

fbr::IShaderStage::IShaderStage(ShaderStageType type, std::string&& code) noexcept :
	m_type(type),
	m_code(std::move(code)),
	m_initialized(false)
{
}

bool fbr::IShaderStage::operator==(const IShaderStage& rhs) const
{
	if (m_type != rhs.m_type)return false;
	if (m_code != rhs.m_code) return false;

	return true;
}

bool fbr::IShaderStage::operator!=(const IShaderStage& rhs) const
{
	return !(*this == rhs);
}

fbr::IShaderStage::IShaderStage(const IShaderStage& other) :
	IShaderStage(other.m_type, other.m_code)
{
}

fbr::IShaderStage::IShaderStage(IShaderStage&& other) noexcept :
	IShaderStage(std::move(other.m_type), std::move(other.m_code))
{
}

fbr::IShaderStage& fbr::IShaderStage::operator=(const IShaderStage& other)
{
	m_type = other.m_type;
	m_code = other.m_code;

	//TODO is it better???
	//return *this = ShaderStage(other);

	return *this;
}

fbr::IShaderStage& fbr::IShaderStage::operator=(IShaderStage&& other) noexcept
{
	m_type = std::move(other.m_type);
	m_code = std::move(other.m_code);

	return *this;
}

bool fbr::IShaderStage::Initialized() const
{
	return m_initialized;
}

bool fbr::IShaderStage::Destroy()
{
	m_type = ShaderStageType::UNDEFINED;
	m_code.clear();
	m_initialized = false;

	return true;
}

const fbr::ShaderStageType& fbr::IShaderStage::GetType() const
{
	return m_type;
}

const std::string& fbr::IShaderStage::GetCode() const
{
	return m_code;
}

void fbr::IShaderStage::SetAsInitialized()
{
	m_initialized = true;
}
