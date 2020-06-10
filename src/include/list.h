#ifndef _LIST_HPP_
# define _LIST_HPP_

template<typename T>
class				List
{
private:
	ListElem<T>		*m_first{NULL};
	ListElem<T>		*m_last{NULL};
	size_t			m_len{0};

public:
	size_t			len(void);
	void			~List(void);
};

template<typename T>
class				ListElem
{
private:
	ListElem		*m_next{NULL};
public:
	T				content;
	ListElem		next(void);
	ListElem		&operator++(ListElem &elem);
	ListElem		operator++(ListElem &elem, int);
}

#endif
