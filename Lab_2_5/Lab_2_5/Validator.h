#ifndef  VALIDATOR_H
#define VALIDATOR_H

#include<iostream>
#include<string>
#include<functional>

namespace validation
{		
	template<class Tinp, class Tout, class TErrorType>
	struct Validator
	{
		Validator()
		{

		}

		Validator(const TErrorType& conv_error_msg, std::function<Tout(const Tinp& inp)> converter,
			std::function<bool(const Tout& value, TErrorType& error)> add_validation = nullptr)
		{
			m_convert_error_msg = conv_error_msg;

			m_converter = converter;

			m_add_validation = add_validation;
		}

		bool validate(const Tinp& input, TErrorType& error)
		{		
			Tout out;

			try
			{
				out = m_converter(input);
			}
			catch (...)//Some convertion error happened
			{
				error = m_convert_error_msg;

				return false;
			}

			if (!m_add_validation)
				return m_add_validation(out, error);

			return true;			
		}
		
	private:
#pragma region Fields
		TErrorType m_convert_error_msg;

		std::function<Tout(const Tinp& inp)> m_converter;

		std::function<bool(const Tout& value, TErrorType& error)> m_add_validation;
#pragma endregion
	};				
}

#endif // ! VALIDATOR_H

