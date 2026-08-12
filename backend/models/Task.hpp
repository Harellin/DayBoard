/***
* class Task
***/

#ifndef TASK_MODEL_HPP_
#define TASK_MODEL_HPP_

#include <QDate>
#include <QString>
#include <optional>
#include <cstdint>

namespace dayboard {

    enum Priority { Normal, High };

    class Task {
        private:
            int task_id;
            QString task_title;
            QDate task_date;
            bool task_completed;
            std::optional<Priority> task_priority;

        public:
            Task() = default;

            Task(int id, QString title, QDate date, bool completed, 
                std::optional<Priority> priority = std::nullopt)
                : task_id(id), task_title(title), task_date(date), task_completed(completed), task_priority(priority) {}

            int getId() const { return task_id; }

            QString getTitle() const { return task_title; }
            void setTitle(QString title) { task_title = title; }

            QDate getDate() const { return task_date; }
            void setDate(QDate date) { task_date = date; }

            bool getCompleted() const { return task_completed; }
            void setCompleted(bool completed) { task_completed = completed; }

            std::optional<Priority> getPriority() const { return task_priority; }
            void setPriority(std::optional<Priority> priority) { task_priority = priority; }
    };
} // namespace dayboard

#endif // TASK_MODEL_HPP_