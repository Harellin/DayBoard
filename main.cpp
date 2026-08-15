/***
* Here we go, main file.
***/

#include <QApplication>
#include "backend/controllers/AppController.hpp"
#include "frontend/calendar/CalendarWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    dayboard::AppController controller("tasks.json", "settings.json");
    controller.loadAll();

    dayboard::CalendarWindow window(&controller);
    window.show();

    return app.exec();
}
