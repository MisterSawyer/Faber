#include "shader-stage.h"

fbr::ShaderStage::~ShaderStage()
{
	Destroy();
}

fbr::ShaderStage::ShaderStage(ShaderStageType type, const std::string& code) :
	m_type(type),
	m_code(code),
	m_initialized(false)
{
}

fbr::ShaderStage::ShaderStage(ShaderStageType type, std::string&& code) noexcept :
	m_type(type),
	m_code(std::move(code)),
	m_initialized(false)
{
}

bool fbr::ShaderStage::operator==(const ShaderStage& rhs) const
{
	if (m_type != rhs.m_type)return false;
	if (m_code != rhs.m_code) return false;

	return true;
}

bool fbr::ShaderStage::operator!=(const ShaderStage& rhs) const
{
	return !(*this == rhs);
}

fbr::ShaderStage::ShaderStage(const ShaderStage& other) :
	ShaderStage(other.m_type, other.m_code)
{
}

fbr::ShaderStage::ShaderStage(ShaderStage&& other) noexcept :
	ShaderStage(std::move(other.m_type), std::move(other.m_code))
{
}

fbr::ShaderStage& fbr::ShaderStage::operator=(const ShaderStage& other)
{
	m_type = other.m_type;
	m_code = other.m_code;

	//TODO is it better???
	//return *this = ShaderStage(other);

	return *this;
}

fbr::ShaderStage& fbr::ShaderStage::operator=(ShaderStage&& other) noexcept
{
	m_type = std::move(other.m_type);
	m_code = std::move(other.m_code);

	return *this;
}

bool fbr::ShaderStage::Initialized() const
{
	return m_initialized;
}

bool fbr::ShaderStage::Destroy()
{
	m_type = ShaderStageType::UNDEFINED;
	m_code.clear();
	m_initialized = false;

	return true;
}

const fbr::ShaderStageType& fbr::ShaderStage::GetType() const
{
	return m_type;
}

const std::string& fbr::ShaderStage::GetCode() const
{
	return m_code;
}

void fbr::ShaderStage::SetAsInitialized()
{
	m_initialized = true;
}
