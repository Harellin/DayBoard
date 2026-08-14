/***
* Task working model
***/

#ifndef TASKMODEL_MODEL_HPP_
#define TASKMODEL_MODEL_HPP_

#include "Task.hpp"
#include <QVector>
#include <optional>

namespace dayboard {

    class TaskModel {
        private:
            QVector<Task> tasks_;

        public:
            TaskModel() = default;

            void addTask(const Task &task);
            void removeTask(int id);
            void updateTask(const Task &task);

            Task* getTaskById(int id);
            const Task* getTaskById(int id) const;
            QVector<Task> getTasksByDate(QDate date) const;
            const QVector<Task>& getAllTasks() const;

            bool containsTask(int id) const;
            int getTaskCount() const;
            void clearTasks();
    };

} // namespace dayboard

#endif // TASKMODEL_MODEL_HPP_