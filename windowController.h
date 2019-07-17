#ifndef __WINDOWCONTROLLER_H__
#define __WINDOWCONTROLLER_H__

#include "controller.h"
#include "window.h"
#include "command.h"
#include "game.h"
#include "graphicalView.h"

#include <vector>

class WindowController : public Controller {
		Game& model;
		Xwindow& window;

		Command command() override;
		Point& point() override;
		char piece() override;

	public:
		WindowController(Game&, Xwindow&);
};

#endif