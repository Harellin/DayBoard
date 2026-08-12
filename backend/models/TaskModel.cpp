/***
* Task working model
***/

#include "TaskModel.hpp"
#include <algorithm>

namespace dayboard {

    TaskModel::TaskModel() {}

    void TaskModel::addTask(const Task &task) {
        tasks_.append(task);
    }

    void TaskModel::removeTask(int id) {
        for (int i = 0; i < tasks_.size(); ++i) {
            if (tasks_[i].getId() == id) {
                tasks_.remove(i);
                return;
            }
        }
    }

    void TaskModel::updateTask(const Task &task) {
        for (int i = 0; i < tasks_.size(); ++i) {
            if (tasks_[i].getId() == task.getId()) {
                tasks_[i] = task;
                return;
            }
        }
    }

    std::optional<Task> TaskModel::getTaskById(int id) const {
        auto it = std::find_if(tasks_.begin(), tasks_.end(),
            [id](const Task &t) { return t.getId() == id; });
            
        if (it != tasks_.end()) {
            return *it;
        }
        return std::nullopt;
    }

    QVector<Task> TaskModel::getTasksByDate(QDate date) const {
        QVector<Task> result;
        for (const auto &task : tasks_) {
            if (task.getDate() == date) {
                result.append(task);
            }
        }
        return result;
    }

    const QVector<Task>& TaskModel::getAllTasks() const {
        return tasks_;
    }

    bool TaskModel::containsTask(int id) const {
        for (const auto &t : tasks_) {
            if (t.getId() == id) {
                return true;
            }
        }
        return false;
    }

    int TaskModel::getTaskCount() const {
        return tasks_.size();
    }

    void TaskModel::clearTasks() {
        tasks_.clear();
    }

} // namespace dayboard