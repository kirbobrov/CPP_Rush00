/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:53:56 by adzikovs          #+#    #+#             */
/*   Updated: 2017/11/04 14:53:58 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.class.hpp"
#include "Ranger.class.hpp"
#include "Enemy.class.hpp"
#include "Projectile.class.hpp"

int				Window::loop(void)
{
	Ranger		Gref(this->getX()/2, this->getY() - 1);
	Enemy		*Klissans = NULL;
	Projectile	*Bullets = NULL;
	Enemy		*Background = NULL;
	int			ret;
	int			a;

	
	Gref.print();
	while (this->checkSizes())
	{
		ret = this->proceedInput(Gref);
		ret |= this->Update(Gref, Klissans, Bullets, Background);
		if (ret & EXIT || ret & FREE)
		{
			while (Klissans)
				Enemy::del(&Klissans);
			if (ret & EXIT)
			{
				this->Draw(Gref, Klissans, Bullets, Background);
				nodelay(this->window, false);
				this->GameOver();
				sleep(3);
				a = getch();
				while (a != 'q')
					a = getch();
				return (0);
			}
		}
		this->Draw(Gref, Klissans, Bullets, Background);
		Window::finishFrame();
	}
	return	(0);
}

void			Window::GameOver(void)
{
	erase();
	attron(COLOR_PAIR(BULLET));
	mvprintw(this->y/2, (this->x/2) - 5, "Game Over!");
	mvprintw(this->y/2 + 1, (this->x/2) - 5, "Score: %d", this->score);
	mvprintw(this->y/2 + 2, (this->x/2) - 7, "Press Q to exit");
	attroff(COLOR_PAIR(BULLET));
	refresh();
}

int				Window::proceedInput(Ranger &Gref)
{
	int		a;

	a = Window::getKey();
	if (a == 'w' || a == 'a' || a == 's' || a == 'd' || a == ' ')
		Gref.setAction(*this, a);
	else if (a == 'q')
		return (EXIT);
	else if (a == 'j')
		return (FREE);
	return (_OK);
}

int				Window::Update(Ranger &Gref, Enemy* &Klissans, Projectile* &Bullets, Enemy* &Background)
{
	static unsigned int		k = 0;
	int						i;
	Enemy					*temp;
	Projectile				*tmp;
	int						ret;
	int						fr = 0;
	std::srand(time(NULL) + clock());
	
	ret = _OK;
	i = 0;
	while (i < std::rand()%3)
	{
		new Enemy(*this, &Klissans, -1);
		i++;
	}
	i = 0;
	while (i < std::rand()%3)
	{
		new Enemy(*this, &Background);
		i++;
	}
	tmp = Bullets;
	while (tmp)
	{
		if (tmp->checkCollision(Klissans, this->score))
		{
			if (tmp == Bullets)
				fr = 1;
				tmp = Projectile::del(&tmp);
			if (fr == 1)
			{
				fr = 0;
				Bullets = tmp;
			}
		}
		else
			tmp = tmp->getNext();
	}
	temp = Klissans;
	while (temp)
	{
		if (temp->checkCollision(Gref))
		{
			if (Gref.takeDamage(1))
				ret = EXIT;
		}
		if (temp->mv(*this, 's') == false)
		{
			if (temp == Klissans)
				fr = 1;
			temp = Enemy::del(&temp);
			if (fr == 1)
			{
				fr = 0;
				Klissans = temp;
			}
		}
		else
			temp = temp->getNext();
	}
	temp = Background;
	if ((k%4) == 0)
	{
		while (temp)
		{
			if (temp->mv(*this, 's') == false)
			{
				if (temp == Background)
					fr = 1;
				temp = Enemy::del(&temp);
				if (fr == 1)
				{
					fr = 0;
					Background = temp;
				}
			}
			else
				temp = temp->getNext();
		}
	}
	tmp = Bullets;
	while (tmp)
	{
		if (tmp->mv(*this, 'w') == false)
		{
			if (tmp == Bullets)
				fr = 1;
			tmp = Projectile::del(&tmp);
			if (fr == 1)
			{
				fr = 0;
				Bullets = tmp;
			}
		}
		else
			tmp = tmp->getNext();
	}
	Gref.justDoIT(*this, &Bullets);
	k++;
	return (ret);
}

int				Window::Draw(Ranger &Gref, Enemy *Klissans, Projectile *projectiles, Enemy *Background)
{
	erase();
	attron(COLOR_PAIR(STAR));
	Enemy::print(Background);
	attroff(COLOR_PAIR(STAR));
	attron(COLOR_PAIR(ENEMY));
	Enemy::print(Klissans);
	attroff(COLOR_PAIR(ENEMY));
	Projectile::print(projectiles);
	Gref.print();
	attron(COLOR_PAIR(BULLET));
	mvprintw(0, 0, "Score: %d", this->score);
	mvprintw(1, 0, "HP: %d", Gref.getHP());
	attron(COLOR_PAIR(BULLET));
	refresh();
	return (0);
}

Window::Window(void) : score(0) {};

Window::Window(Window const &src) : x(src.x), y(src.y) , window(src.window) {}

Window			&Window::operator=(Window const &src)
{
	this->x = src.x;
	this->y = src.y;
	return (*this);
}

void			Window::setSizes(WINDOW *window)
{
	this->window = window;
	nodelay(this->window, true);
	getmaxyx(this->window, this->y, this->x);
}

bool			Window::checkSizes(void) const
{
	int		x;
	int		y;

	getmaxyx(this->window, y, x);
	if (this->x != x || this->y != y)
		return (false);
	else
		return (true);
}

int				Window::getKey(void)
{
	int				a;
	std::string		buff;
	std::stringstream	conv;

	a = getch();
	if (a)
	{
		if (a >= 32 && a <= 126)
			return (a);
		else if (a == 27)
		{
			getch();
			getch();
			return (0);
		}
		else
		{
			conv << a;
			conv >> buff;
			addstr(buff.c_str());
			return (0);
		}
	}
	else
		return (0);
}
	
bool			Window::checkCrd(int x, int y) const
{
	if (x < 0 || x >= this->x)
		return (false);
	else if (y < 0 || y >= this->y)
		return (false);
	else
		return (true);
}

int				Window::finishFrame(void)
{
//	usleep(30000);
	static clock_t	last = clock();
	clock_t			curr = clock();

	while ((((float)curr - (float)last)/CLOCKS_PER_SEC) < 0.1)
		curr = clock();
	last = curr;
	return (0);
}

int				Window::getX(void) const
{
	return (this->x);
}

int				Window::getY(void) const
{
	return (this->y);
}