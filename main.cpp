/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:26:43 by adzikovs          #+#    #+#             */
/*   Updated: 2017/11/04 14:26:45 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <iostream>
#include "Window.class.hpp"
#include "Ranger.class.hpp"

int		main(void)
{
	Window	term;

	term.setSizes(initscr());
	start_color();
	init_pair(PLAYER, COLOR_BLUE, COLOR_BLACK);
	init_pair(BULLET, COLOR_WHITE, COLOR_BLACK);
	init_pair(ENEMY, COLOR_RED, COLOR_BLACK);
	init_pair(STAR, COLOR_YELLOW, COLOR_BLACK);
	noecho();
	term.loop();
	endwin();
	return (0);
}