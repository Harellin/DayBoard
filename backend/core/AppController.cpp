/***
* Full App Controller and signals.
***/

#include "AppController.hpp"
#include <QDebug>

namespace dayboard {
    AppController::AppController(const QString& tasksPath,
                             const QString& settingsPath,
                             QObject* parent) : 
        QObject(parent),
        storage_(new StorageManager(settingsPath, tasksPath)),
        taskModel_(), settingsModel_() {}

    AppController::~AppController() {
        delete storage_;
    }

    void AppController::loadAll() {
        try {
            settingsModel_ = storage_->loadSettings();
            emit settingsChanged();
        } catch (const std::exception& e) {
            emit errorOccurred(QString("Error loading settings: %1").arg(e.what()));
        }
        try {
            taskModel_ = storage_->loadTasks();
            emit tasksChanged();
        } catch (const std::exception& e) {
            emit errorOccurred(QString("Error loading tasks: %1").arg(e.what()));
        }
    }

    void AppController::saveAll() {
        saveSettings();
        saveTasks();
    }

    void AppController::addTask(const Task& task) {
        taskModel_.addTask(task);
        saveTasks();
        emit tasksChanged();
    }

    void AppController::removeTask(int id) {
        taskModel_.removeTask(id);
        saveTasks();
        emit tasksChanged();
    }

    void AppController::updateTask(const Task& task) {
        taskModel_.updateTask(task);
        saveTasks();
        emit tasksChanged();
    }

    void AppController::markTaskCompleted(int id) {
        Task* taskOpt = taskModel_.getTaskById(id);
        if (taskOpt) {
            taskOpt->setCompleted(!taskOpt->getCompleted());
            saveTasks();
            emit tasksChanged();
        } else {
            emit errorOccurred(QString("Task with ID %1 not found").arg(id));
        }
    }

    void AppController::applySettings(const SettingsModel& model) {
        settingsModel_ = model;
        saveSettings();
        emit settingsChanged();
    }

    void AppController::saveTasks() {
        try {
            storage_->saveTasks(taskModel_);
        } catch (...) {
            qWarning() << "Failed to save tasks";
            emit errorOccurred(QStringLiteral("Failed to save tasks"));
        }
    }

    void AppController::saveSettings() {
        try {
            storage_->saveSettings(settingsModel_);
        } catch (...) {
            qWarning() << "Failed to save settings";
            emit errorOccurred(QStringLiteral("Failed to save settings"));
        }
    }

}  // namespace dayboard
