/***
* Window for calendar displaying.
***/

#ifndef CALENDARWINDOW_HPP
#define CALENDARWINDOW_HPP

#include <QWidget>
#include <QTableWidget>
#include "../../backend/controllers/AppController.hpp"
#include "ui_CalendarWindow.h"

namespace dayboard {

class CalendarWindow : public QWidget {
    Q_OBJECT

public:
    explicit CalendarWindow(AppController* controller, QWidget* parent = nullptr);

    void setWeeks(int weeks);
    void setShowWeekends(bool show);
    void refresh();

private slots:
    void onCellClicked(int row, int column);
    void onTasksChanged();

private:
    Ui::CalendarWindow* ui;
    AppController* controller_;
    QTableWidget* table_;
    int weeks_;
    bool showWeekends_;

    void buildTable();
    void fillTasks();
};

} // namespace dayboard

#endif // CALENDARWINDOW_HPP
