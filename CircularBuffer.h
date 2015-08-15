/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CircularBuffer.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvier <abouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/14 18:01:48 by abouvier          #+#    #+#             */
/*   Updated: 2015/08/15 05:38:17 by abouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include "Arduino.h"

template <typename T, size_t Size>
class CircularBuffer
{
public:
	typedef T value_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef size_t size_type;

private:
	value_type m_buffer[Size];
	pointer m_head;
	pointer m_end;
	pointer m_tail;
	size_type m_size;

public:
	CircularBuffer() : m_head(m_buffer), m_end(m_buffer + Size),
		m_tail(m_buffer + Size - 1), m_size(0) {}

	template <size_type U>
	CircularBuffer(const CircularBuffer<T, U> &that) : CircularBuffer()
	{
		*this = that;
	}

	template <size_type U>
	CircularBuffer &operator=(const CircularBuffer<T, U> &that)
	{
		//if (&that != this)
		{
			m_size = min(that.size(), capacity());
			for (size_type i = that.size() - m_size; i < that.size(); i++)
				push_back(that[i]);
		}
		return *this;
	}

	reference operator[](size_type offset)
	{
		return const_cast<reference>(
			const_cast<const CircularBuffer &>(*this)[offset]
		);
	}

	const_reference operator[](size_type offset) const
	{
		return m_head[offset < m_end - m_head ? offset : offset - capacity()];
	}

	void push_back(const_reference value)
	{
		if (full())
			pop_front();
		if (++m_tail == m_end)
			m_tail = m_buffer;
		*m_tail = value;
		m_size++;
	}

	void push_front(const_reference value)
	{
		if (full())
			pop_back();
		if (m_head-- == m_buffer)
			m_head += capacity();
		*m_head = value;
		m_size++;
	}

	void pop_back()
	{
		if (m_tail-- == m_buffer)
			m_tail += capacity();
		m_size--;
	}

	void pop_front()
	{
		if (++m_head == m_end)
			m_head = m_buffer;
		m_size--;
	}

	reference back()
	{
		return *m_tail;
	}

	const_reference back() const
	{
		return *m_tail;
	}

	reference front()
	{
		return *m_head;
	}

	const_reference front() const
	{
		return *m_head;
	}

	void clear()
	{
		m_head = m_buffer;
		m_tail = m_end - 1;
		m_size = 0;
	}

	size_type capacity() const
	{
		return Size;
	}

	size_type size() const
	{
		return m_size;
	}

	size_type reserve() const
	{
		return capacity() - size();
	}

	bool empty() const
	{
		return !size();
	}

	bool full() const
	{
		return size() == capacity();
	}
};

#endif
