/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:57:35 by adzikovs          #+#    #+#             */
/*   Updated: 2017/11/04 17:57:37 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.class.hpp"
#include "Enemy.class.hpp"

Enemy::Enemy(void) : AUnit(), next(NULL), prev(NULL) {}

Enemy::Enemy(Enemy const &src) : AUnit(src.x, src.y),
	next(NULL), prev(NULL)
{
	this->symb = src.symb;
	this->action = src.action;
}

Enemy::Enemy(Window const &window, Enemy **begin, int y) : AUnit()
{

	std::srand(time(NULL) + clock());
	this->y = y;
	this->x = std::rand()%window.getX();
	this->next = *begin;
	if (*begin)
		(*begin)->prev = this;
	this->prev = NULL;
	if (std::rand()%2)
		this->symb = '8';
	else
		this->symb = 'V';
	*begin = this;
}

Enemy::Enemy(Window const &window, Enemy **begin) : AUnit()
{

	std::srand(time(NULL) + clock());
	this->y = -1;
	this->x = std::rand()%window.getX();
	this->next = *begin;
	if (*begin)
		(*begin)->prev = this;
	this->prev = NULL;
	this->symb = '.';
	*begin = this;
}

Enemy::~Enemy(void)
{
	if (this->prev)
	{
		this->prev->next = this->next;
	}
}

Enemy			&Enemy::operator=(Enemy const &src)
{
	this->x = src.x;
	this->y = src.y;
	this->symb = src.symb;
	this->action = src.action;
	return (*this);
}

bool			Enemy::print(void) const
{
	if (move(this->y, this->x) == ERR || addch(this->symb) == ERR)
		return (false);
	else
		return (true);
}

bool			Enemy::print(Enemy *enemies)
{
	while (enemies)
	{
		enemies->print();
		enemies = enemies->next;
	}
	return (true);
}

Enemy			*Enemy::del(Enemy **enemy)
{
	Enemy	*temp;
	Enemy	*ret;
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

Enemy*			&Enemy::getNext(void)
{
	return (this->next);
}

bool			Enemy::checkCollision(AUnit const &Gref)
{
	if (this->x == Gref.getX() && this->y == (Gref.getY() - 1) && Gref.getAction() == 'w')
		return (true);
	if (this->x == Gref.getX() && (this->y + 1) == (Gref.getY() - 1) && Gref.getAction() == 'w')
		return (true);
	if (this->x == Gref.getX() && (this->y + 1) == (Gref.getY() + 1) && Gref.getAction() == 's')
		return (true);
	if (this->x == (Gref.getX() - 1) && (this->y + 1) == Gref.getY() && Gref.getAction() == 'a')
		return (true);
	if (this->x == (Gref.getX() + 1) && (this->y + 1) == Gref.getY() && Gref.getAction() == 'd')
		return (true);
	if (this->x == Gref.getX() && (this->y + 1) == Gref.getY() && Gref.getAction() == 0)
		return (true);
	return (false);
}