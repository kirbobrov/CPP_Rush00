/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ranger.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 15:43:51 by adzikovs          #+#    #+#             */
/*   Updated: 2017/11/04 15:43:53 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.class.hpp"
#include "Ranger.class.hpp"
#include "Projectile.class.hpp"

Ranger::Ranger(void) : AUnit()
{
	this->HP = 3;
	this->symb = 'U';
}

Ranger::Ranger(Ranger const &src) : AUnit(src.x, src.y)
{
	this->HP = src.HP;
	this->symb = 'U';
}

Ranger::Ranger(int x, int y) : AUnit(x, y)
{
	this->HP = 3;
	this->symb = 'U';
}

Ranger::~Ranger(void) {}

Ranger		&Ranger::operator=(Ranger const &src)
{
	this->x = src.x;
	this->y = src.y;
	this->symb = src.symb;
	this->action = src.action;
	return (*this);
}

bool		Ranger::print(void) const
{
	attron(COLOR_PAIR(PLAYER));
	if (move(this->y, this->x) == ERR || addch(this->symb) == ERR)
		return (false);
	else
		return (true);
	attroff(COLOR_PAIR(PLAYER));
}

bool		Ranger::setAction(Window const &window, int action)
{
	int		valid_action[5];
	int		i;
	Ranger	check;

	check = *this;
	valid_action[0] = 'w';
	valid_action[1] = 'a';
	valid_action[2] = 's';
	valid_action[3] = 'd';
	valid_action[4] = ' ';
	i = 0;
	while (i < 5)
	{
		if (action == valid_action[i])
		{
			if (i > 3 || check.mv(window, action))
				this->action = action;
			else
				this->action = 0;
			return (true);
		}
		i++;
	}
	return (false);
}

int			Ranger::justDoIT(Window const &window, Projectile **projectiles)
{
	this->mv(window, this->action);
	if (this->action == ' ')
		new Projectile(projectiles, this->getX(), this->getY());
	this->action = 0;
	return (0);
}

bool		Ranger::takeDamage(int damage)
{
	if (this->HP > damage)
	{
		this->HP -= damage;
		return (false);
	}
	else
	{
		this->HP = 0;
		return (true);
	}
}

int			Ranger::getHP(void) const
{
	return (this->HP);
}