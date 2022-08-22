#pragma once

#include <glm/glm/glm.hpp> //TODO ????
#include <type_traits>
#include <concepts>
#include <functional>

namespace fbr
{
	template<typename T>
	concept ColorTypeConcept = 
		(std::is_floating_point<T>::value ||
		std::unsigned_integral<T>)
		&& std::is_convertible<T, float>::value; // conversion to glm::vec4


	template<ColorTypeConcept T>
	struct Color
	{
	public:
		virtual ~Color() = default;

		Color();

		Color(const T & R, const T& G, const T& B, const T & A = (T)(255));
		Color(T && R, T && G, T && B, T && A = (T)(255));

		Color(const glm::vec4 & vec);
		Color(glm::vec4 && vec) noexcept;

		Color(const Color & other);
		Color(Color && other) noexcept;

		Color& operator=(const Color & other);
		Color& operator=(Color && other) noexcept;

		Color& operator=(const glm::vec4 & vec);
		Color& operator=(glm::vec4 && vec) noexcept;

		void Set(const T& R, const T& G, const T& B, const T& A = (T)(255));
		void Set(T && R, T && G, T && B, T && A = (T)(255));

		void SetR(const T & value);
		void SetG(const T & value);
		void SetB(const T & value);
		void SetAlpha(const T & value);

		void SetR(T && value);
		void SetG(T && value);
		void SetB(T && value);
		void SetAlpha(T && value);

		const T & R() const;
		const T & G() const;
		const T & B() const;
		const T & Alpha() const;

		operator glm::vec4() const;

	private:
		T MatchRange(const T & val, const T range = T(255));

		T m_R, m_G, m_B;
		T m_alpha;
	};

	template<ColorTypeConcept T>
	inline Color<T>::Color()
	{
		m_R = (T)0;
		m_G = (T)0;
		m_B = (T)0;
		m_alpha = (T)0;
	}

	template<ColorTypeConcept T>
	inline Color<T>::Color(const T& R, const T& G, const T& B, const T& A)
	{
		m_R = MatchRange(R);
		m_G = MatchRange(G);
		m_B = MatchRange(B);
		m_alpha = MatchRange(A);
	}

	template<ColorTypeConcept T>
	inline Color<T>::Color(T&& R, T&& G, T&& B, T&& A)
	{
		m_R = std::move(MatchRange(R));
		m_G = std::move(MatchRange(G));
		m_B = std::move(MatchRange(B));
		m_alpha = std::move(MatchRange(A));
	}

	template<ColorTypeConcept T>
	inline Color<T>::Color(const glm::vec4& vec) : Color((T)vec.r, (T)vec.g, (T)vec.b, (T)vec.a)
	{
		// vec.r/g/b/a does not necessery must be of type T
	}

	template<ColorTypeConcept T>
	inline Color<T>::Color(glm::vec4&& vec) noexcept : Color(std::move((T)vec.r), std::move((T)vec.g), std::move((T)vec.b), std::move((T)vec.a))
	{
	}

	template<ColorTypeConcept T>
	inline Color<T>::Color(const Color& other) : Color(other.m_R, other.m_G, other.m_B, other.m_alpha)
	{
	}

	template<ColorTypeConcept T>
	inline Color<T>::Color(Color&& other) noexcept : Color(std::move(other.m_R), std::move(other.m_G), std::move(other.m_B), std::move(other.m_alpha))
	{
	}

	template<ColorTypeConcept T>
	inline Color<T> & Color<T>::operator=(const Color & other)
	{
		m_R = other.m_R;
		m_G = other.m_G;
		m_B = other.m_B;
		m_alpha = other.m_alpha;

		return *this;
	}

	template<ColorTypeConcept T>
	inline Color<T> & Color<T>::operator=(Color&& other) noexcept
	{
		m_R = std::move(other.m_R);
		m_G = std::move(other.m_G);
		m_B = std::move(other.m_B);
		m_alpha = std::move(other.m_alpha);

		return *this;
	}

	template<ColorTypeConcept T>
	inline Color<T>& Color<T>::operator=(const glm::vec4& vec)
	{
		return *this = Color<T>(vec);
	}

	template<ColorTypeConcept T>
	inline Color <T> & Color<T>::operator=(glm::vec4&& vec) noexcept
	{
		return *this = Color<T>(std::move(vec));
	}

	template<ColorTypeConcept T>
	inline void Color<T>::Set(const T& R, const T& G, const T& B, const T& A)
	{
		*this = Color<T>(R, G, B, A);
	}

	template<ColorTypeConcept T>
	inline void Color<T>::Set(T&& R, T&& G, T&& B, T&& A)
	{
		*this = Color<T>(std::move(R), std::move(G), std::move(B), std::move(A));
	}

	template<ColorTypeConcept T>
	inline void Color<T>::SetR(const T& value)
	{
		m_R = value % 255;
	}

	template<ColorTypeConcept T>
	inline void Color<T>::SetG(const T& value)
	{
		m_G = value % 255;
	}

	template<ColorTypeConcept T>
	inline void Color<T>::SetB(const T& value)
	{
		m_B = value % 255;
	}

	template<ColorTypeConcept T>
	inline void Color<T>::SetAlpha(const T& value)
	{
		m_alpha = value % 255;
	}

	template<ColorTypeConcept T>
	inline void Color<T>::SetR(T&& value)
	{
		m_R = std::move(value % 255);
	}

	template<ColorTypeConcept T>
	inline void Color<T>::SetG(T&& value)
	{
		m_G = std::move(value % 255);
	}

	template<ColorTypeConcept T>
	inline void Color<T>::SetB(T&& value)
	{
		m_B = std::move(value % 255);
	}

	template<ColorTypeConcept T>
	inline void Color<T>::SetAlpha(T&& value)
	{
		m_alpha = std::move(value % 255);
	}

	template<ColorTypeConcept T>
	inline const T& Color<T>::R() const
	{
		return m_R;
	}

	template<ColorTypeConcept T>
	inline const T& Color<T>::G() const
	{
		return m_G;
	}

	template<ColorTypeConcept T>
	inline const T& Color<T>::B() const
	{
		return m_B;
	}

	template<ColorTypeConcept T>
	inline const T& Color<T>::Alpha() const
	{
		return m_alpha;
	}

	template<ColorTypeConcept T>
	inline Color<T>::operator glm::vec4() const
	{
		return glm::vec4(m_R, m_G, m_B, m_alpha);
	}

	template<ColorTypeConcept T>
	inline T Color<T>::MatchRange(const T& val, const T range)
	{
		if (val <= range)return val;
		
		return MatchRange(val - range);
	}

	template<typename T>
	concept ColorTypeConceptNormalize = std::is_floating_point<T>::value;


	template <typename T>
	requires ColorTypeConceptNormalize<T>
	inline Color<T> normalize(const Color<T> & color)
	{
		return Color<T>(color.R() / (T)255.0, color.G() / (T)255.0, color.B() / (T)255.0, color.Alpha() / (T)255.0);
	}


	template <typename T>
	requires (!ColorTypeConceptNormalize<T>)
		inline Color<float> normalize(const Color<T>& color)
	{
		return Color<float>(color.R() / (float)255.f, color.G() / (float)255.f, color.B() / (float)255.f, color.Alpha() / (float)255.f);
	}
}