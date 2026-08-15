/***
* Full App Controller and signals.
***/

#ifndef APP_CONTROLLER_HPP_
#define APP_CONTROLLER_HPP_ 

#include <QObject>
#include <QTimer>
#include <QString>
#include "../core/StorageManager.hpp"
#include "../models/TaskModel.hpp"
#include "../models/SettingsModel.hpp"

namespace dayboard {

    class AppController : public QObject {
        Q_OBJECT

        private:
            StorageManager* storage_;
            TaskModel taskModel_;
            SettingsModel settingsModel_;
            void saveTasks();
            void saveSettings();

        public:
            explicit AppController(const QString& tasksPath, 
                                const QString& settingsPath, 
                                QObject* parent = nullptr);
            ~AppController();
            
            void loadAll();
            void saveAll();
            void addTask(const Task& task);
            void removeTask(int id);
            void updateTask(const Task& task);
            void markTaskCompleted(int id);
            void applySettings(const SettingsModel& model);

            TaskModel& getTaskModel() { return taskModel_; }
            SettingsModel& getSettingsModel() { return settingsModel_; }

        signals:
            void tasksChanged();
            void settingsChanged();
            void errorOccurred(const QString& message);
    };

}  // namespace dayboard

#endif  // APP_CONTROLLER_HPP_