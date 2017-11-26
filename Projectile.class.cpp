/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Projectile.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:11:20 by adzikovs          #+#    #+#             */
/*   Updated: 2017/11/05 15:11:22 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Projectile.class.hpp"
#include "Enemy.class.hpp"
#include "Window.class.hpp"

Projectile::Projectile(void) : AUnit(), prev(NULL), next(NULL) {}

Projectile::Projectile(Projectile const &src) : AUnit(src), prev(NULL), next(NULL) {}

Projectile::~Projectile(void) {}

Projectile::Projectile(Projectile **begin, int x, int y) :
	AUnit()
{
	this->x = x;
	this->y = y;
	this->next = *begin;
	this->action = 'w';
	if (*begin)
		(*begin)->prev = this;
	this->prev = NULL;
	if (this->next)
		this->symb = this->next->symb;
	else
		this->symb = '*';
	*begin = this;
}

Projectile			&Projectile::operator=(Projectile const &src)
{
	this->x = src.x;
	this->y = src.y;
	this->symb = src.symb;
	this->action = src.action;
	return (*this);
}

bool		Projectile::print(void) const
{
	if (move(this->y, this->x) == ERR || addch(this->symb) == ERR)
		return (false);
	else
		return (true);
}

bool		Projectile::print(Projectile *projectiles)
{
	attron(COLOR_PAIR(BULLET));
	while (projectiles)
	{
		projectiles->print();
		projectiles = projectiles->next;
	}
	attroff(COLOR_PAIR(BULLET));
	return (true);
}

bool		Projectile::setAction(int action)
{
	this->action = action;
	return (true);
}

Projectile			*Projectile::del(Projectile **enemy)
{
	Projectile	*temp;
	Projectile	*ret;
	int		fr = 1;

	temp = *enemy;
	if (*enemy)
		ret = (*enemy)->next;
	else
		ret = NULL;
	if (*enemy && (*enemy)->prev)
	{
		if (enemy == &((*enemy)->prev->next)
			|| ((*enemy)->next && enemy == &((*enemy)->next->prev)))
			fr = 0;
		(*enemy)->prev->next = (*enemy)->next;
		if ((*enemy)->next)
			(*enemy)->next->prev = (*enemy)->prev;
		if (fr == 1)
			*enemy = (*enemy)->prev;
		delete temp;
	}
	else if (*enemy && (*enemy)->next)
	{
		if (enemy != &((*enemy)->next->prev))
			*enemy = (*enemy)->next;
		else
			enemy = &((*enemy)->next);
		(*enemy)->prev = NULL;
		delete temp;
	}
	else if (*enemy)
	{
		*enemy = NULL;
		delete temp;
	}
	return (ret);
}

bool				Projectile::checkCollision(Enemy* &enemy, int &score)
{
	Enemy	*tmp;
	int		fr = 0;

	tmp = enemy;
	while (tmp)
	{
		if (tmp->checkCollision(*this))
		{
			if (tmp == enemy)
				fr = 1;
			Enemy::del(&tmp);
			score++;
			if (fr == 1)
			{
				fr = 0;
				enemy = tmp;
			}
			return (true);
		}
		tmp = tmp->getNext();
	}
	return (false);
}

Projectile*			&Projectile::getNext(void)
{
	return (this->next);
}