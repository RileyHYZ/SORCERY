#ifndef __WINDOWCONTROLLER_H__
#define __WINDOWCONTROLLER_H__

#include "controller.h"
#include "window.h"
#include "command.h"
#include "game.h"
#include "graphicalView.h"

#include <vector>

class WindowController : public Controller {
		Xwindow& window;
		bool enhancementsOn;

		Command command() override;
		Point& point() override;
		char piece() override;

	public:
		WindowController(Xwindow&, bool);
};

#endif