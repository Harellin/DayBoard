/***
* Window for calendar displaying.
***/

#include "CalendarWindow.hpp"
#include "ui_CalendarWindow.h"

namespace dayboard {

    CalendarWindow::CalendarWindow(AppController* controller, QWidget* parent)
        : QWidget(parent),
          controller_(controller),
          weeks_(4),
          showWeekends_(true)
    {
        ui = new Ui::CalendarWindow();
        ui->setupUi(this);
        table_ = ui->calendarTable;
        connect(table_, &QTableWidget::cellClicked, this, &CalendarWindow::onCellClicked);
        connect(controller_, &AppController::tasksChanged, this, &CalendarWindow::refresh);
        refresh();
    }

    void CalendarWindow::setWeeks(int weeks) {
        weeks_ = weeks;
        refresh();
    }

    void CalendarWindow::setShowWeekends(bool show) {
        showWeekends_ = show;
        refresh();
    }

    void CalendarWindow::refresh() {
        buildTable();
        fillTasks();
    }

    void CalendarWindow::onTasksChanged() {
        fillTasks();
    }

    void CalendarWindow::buildTable() {
        int columns = showWeekends_ ? 7 : 5;
        table_->clear();
        table_->setRowCount(weeks_);
        table_->setColumnCount(columns);

        QStringList headers;
        headers << "Mon" << "Tue" << "Wed" << "Thu" << "Fri";
        if (showWeekends_) {
            headers << "Sat" << "Sun";
        }
        table_->setHorizontalHeaderLabels(headers);
    }

    void CalendarWindow::fillTasks() {
        table_->clearContents();
        const auto& tasks = controller_->getTaskModel().getAllTasks();

        for (const Task& t : tasks) {
            int row = t.getDate().weekNumber() % weeks_;
            int col = t.getDate().dayOfWeek() - 1;

            if (!showWeekends_ && col >= 5)
                continue;

            QString text = table_->item(row, col) ? table_->item(row, col)->text() : QString();
            text += t.getTitle() + "\n";
            QTableWidgetItem* item = new QTableWidgetItem(text);
            table_->setItem(row, col, item);
        }
    }

    void CalendarWindow::onCellClicked(int row, int column) {
        // fill later
    }
} // namespace dayboard