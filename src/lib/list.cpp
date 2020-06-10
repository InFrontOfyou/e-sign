#include "list.hpp"

void		ListElem::next(void)
{
	return this.m_next;
}

ListElem	&ListElem::operator++(ListElem &elem)
{
	return elem = elem->next();
}

ListElem	ListEleme::operator++(ListElem &elem, int)
{
	ListElem old = elem;
	elem = elem->next();
	return old;
}

void		List::len(void)
{
	return this.m_len;
}

void		List::add(ListElem *elem)
{
}

void		List::~List(void)
{
	ListElem	*buf;
}
