/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AUnit.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 16:04:35 by adzikovs          #+#    #+#             */
/*   Updated: 2017/11/04 16:04:37 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AUnit.class.hpp"
#include "Window.class.hpp"

AUnit::AUnit(void) : x(0), y(0), symb('0'), action(0) {}

AUnit::AUnit(AUnit const &src) : x(src.x), y(src.y), symb(src.symb),
	action(src.action) {}

AUnit::AUnit(int x, int y) : x(x), y(y), symb('0'), action(0) {}

AUnit::~AUnit(void) {}

AUnit		&AUnit::operator=(AUnit const &src)
{
	this->x = src.x;
	this->y = src.y;
	this->symb = src.symb;
	this->action = src.action;
	return (*this);
}

bool		AUnit::mv(Window const &window, int dir) 
{
	if (dir == 'w')
	{
		if (window.checkCrd(this->x, this->y - 1))
		{
			this->y--;
			return (true);
		}
		else
			return (false);
	}
	else if (dir == 'a')
	{
		if (window.checkCrd(this->x - 1, this->y))
		{
			this->x--;
			return (true);
		}
		else
			return (false);
	}
	else if (dir == 's')
	{
		if (window.checkCrd(this->x, this->y + 1))
		{
			this->y++;
			return (true);
		}
		else
			return (false);
	}
	else if (dir == 'd')
	{
		if (window.checkCrd(this->x + 1, this->y))
		{
			this->x++;
			return (true);
		}
		else
			return (false);
	}
	else
		return (false);
}

bool		AUnit::mv(Window const &window, int x, int y)
{
	if (window.checkCrd(x, y))
	{
		this->x = x;
		this->y = y;
		return (true);
	}
	else
		return (false);
}

int			AUnit::getX(void) const
{
	return (this->x);
}

int			AUnit::getY(void) const
{
	return (this->y);
}

int			AUnit::getAction(void) const
{
	return (this->action);
}