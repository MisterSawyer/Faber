#pragma once
#include <string>
#include <vector>
#include <memory>
#include <type_traits>

#include "../../logger/logger.h"
#include "shader-stage.h"

namespace fbr
{
	template <class T>
	concept ShaderStageDerivedConcept = std::is_base_of<ShaderStage, T>::value;

	template <ShaderStageDerivedConcept T>
	class ShaderProgram
	{
	public:
		ShaderProgram();
		virtual ~ShaderProgram();

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
	ShaderProgram<T>::ShaderProgram()
	{
		m_initialized = false;
	}

	template <ShaderStageDerivedConcept T>
	ShaderProgram<T>::~ShaderProgram()
	{
		Destroy();
	}

	template <ShaderStageDerivedConcept T>
	bool ShaderProgram<T>::Initialized() const
	{
		return m_initialized;
	}

	template <ShaderStageDerivedConcept T>
	void ShaderProgram<T>::SetAsInitialized()
	{
		m_initialized = true;
	}

	template<ShaderStageDerivedConcept T>
	inline const std::vector<std::shared_ptr<T>>& ShaderProgram<T>::GetPipeline() const
	{
		return m_pipeline;
	}

	template <ShaderStageDerivedConcept T>
	void ShaderProgram<T>::InsertStage(const std::size_t& order, std::shared_ptr<T> && stage)
	{
		m_pipeline.insert(m_pipeline.begin() + order, std::move(stage));
	}

	template <ShaderStageDerivedConcept T>
	void ShaderProgram<T>::InsertStage(const std::size_t& order, const std::shared_ptr<T> & stage)
	{
		m_pipeline.insert(m_pipeline.begin() + order, stage);

	}

	template <ShaderStageDerivedConcept T>
	void ShaderProgram<T>::AddStage(const std::shared_ptr<T> & stage)
	{
		m_pipeline.push_back(stage);
	}

	template <ShaderStageDerivedConcept T>
	void ShaderProgram<T>::AddStage(std::shared_ptr<T> && stage)
	{
		m_pipeline.push_back(std::move(stage));
	}

	template <ShaderStageDerivedConcept T>
	bool ShaderProgram<T>::CompilePipeline()
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
	bool ShaderProgram<T>::Destroy()
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