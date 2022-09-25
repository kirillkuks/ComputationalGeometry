#pragma once

#include <cassert>
#include <vector>


template <typename T>
class Stack
{
public:
	Stack() : m_size(0) {};
	~Stack() {};

	void Push(T const& value)
	{
		if (m_size < m_stack.size())
		{
			m_stack[m_size] = value;
		}
		else
		{
			m_stack.push_back(value);
		}
		++m_size;
	}

	T const& Pop()
	{
		assert(m_size > 0);

		--m_size;
		return m_stack[m_size];
	};


	T const& Top() const
	{
		assert(m_size > 0);

		return m_stack[m_size - 1];
	};

	T const& TopSecond() const
	{
		assert(m_size > 1);

		return m_stack[m_size - 2];
	};


	bool IsEmpty() const
	{
		return m_size == 0;
	}

	size_t Size() const
	{
		return m_size;
	}

	void Clear()
	{
		m_size = 0;
	}

private:
	std::vector<T> m_stack;
	size_t m_size;
};
