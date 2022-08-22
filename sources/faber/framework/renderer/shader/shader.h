#pragma once
#include <string>
#include <vector>
#include <memory>
#include <type_traits>

#include <framework/logger/logger.h>
#include <framework/renderer/shader/shader-stage.h>

namespace fbr
{
	template <class T>
	concept ShaderStageDerivedConcept = std::is_base_of<IShaderStage, T>::value;

	template <ShaderStageDerivedConcept T>
	class IShaderProgram
	{
	public:
		IShaderProgram();
		virtual ~IShaderProgram();

		virtual bool Compile() = 0;
		virtual bool Use() = 0;
		virtual bool Destroy();

		bool Initialized() const;

		//-------- pipeline
		void InsertStage(const std::size_t& order, std::shared_ptr<T>&& stage);
		void InsertStage(const std::size_t& order, const std::shared_ptr<T>& stage);

		void AddStage(const std::shared_ptr<T>& stage);
		void AddStage(std::shared_ptr<T>&& stage);

	protected:
		bool CompilePipeline();
		void SetAsInitialized();

		const std::vector<std::shared_ptr<T>>& GetPipeline() const;

	private:
		bool m_initialized;
		std::vector<std::shared_ptr<T>> m_pipeline;
	};

	template <ShaderStageDerivedConcept T>
	IShaderProgram<T>::IShaderProgram()
	{
		m_initialized = false;
	}

	template <ShaderStageDerivedConcept T>
	IShaderProgram<T>::~IShaderProgram()
	{
		Destroy();
	}

	template <ShaderStageDerivedConcept T>
	bool IShaderProgram<T>::Initialized() const
	{
		return m_initialized;
	}

	template <ShaderStageDerivedConcept T>
	void IShaderProgram<T>::SetAsInitialized()
	{
		m_initialized = true;
	}

	template<ShaderStageDerivedConcept T>
	inline const std::vector<std::shared_ptr<T>>& IShaderProgram<T>::GetPipeline() const
	{
		return m_pipeline;
	}

	template <ShaderStageDerivedConcept T>
	void IShaderProgram<T>::InsertStage(const std::size_t& order, std::shared_ptr<T> && stage)
	{
		m_pipeline.insert(m_pipeline.begin() + order, std::move(stage));
	}

	template <ShaderStageDerivedConcept T>
	void IShaderProgram<T>::InsertStage(const std::size_t& order, const std::shared_ptr<T> & stage)
	{
		m_pipeline.insert(m_pipeline.begin() + order, stage);

	}

	template <ShaderStageDerivedConcept T>
	void IShaderProgram<T>::AddStage(const std::shared_ptr<T> & stage)
	{
		m_pipeline.push_back(stage);
	}

	template <ShaderStageDerivedConcept T>
	void IShaderProgram<T>::AddStage(std::shared_ptr<T> && stage)
	{
		m_pipeline.push_back(std::move(stage));
	}

	template <ShaderStageDerivedConcept T>
	bool IShaderProgram<T>::CompilePipeline()
	{
		for (auto& stage : m_pipeline)
		{
			if (!stage->Compile())
			{
				// stage cannot be compiled so whole pipeline is not compiled
				LOG_ERR("Problem when compiling shader pipeline");

				return false;
			}
		}

		return true;
	}

	template <ShaderStageDerivedConcept T>
	bool IShaderProgram<T>::Destroy()
	{
		m_initialized = false;

		bool success = true;
		for (auto& stage : m_pipeline)
		{
			if (!stage->Destroy())
			{
				// come shaders had problems when destroyed
				success = false;
				LOG_ERR("Problem when destroying shader stage");
			}
		}

		m_pipeline.clear();

		return success;
	}
}