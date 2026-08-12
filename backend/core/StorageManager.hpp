/***
* Tasks and settings manager.
***/

#ifndef STORAGEMANAGER_HPP_
#define STORAGEMANAGER_HPP_

#include <QString>
#include "../models/TaskModel.hpp"
#include "../models/SettingsModel.hpp"

namespace dayboard {

    class StorageManager {
        private:
            QString settingsPath_;
            QString tasksPath_;

        public:
            StorageManager(const QString& settingsPath, const QString& tasksPath);

            SettingsModel loadSettings();
            void saveSettings(const SettingsModel& model);

            TaskModel loadTasks();
            void saveTasks(const TaskModel& model);
    };

}  // namespace dayboard

#endif  // STORAGEMANAGER_HPP_