/***
* Tasks and settings manager.
***/

#include "StorageManager.hpp"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace dayboard {

    StorageManager::StorageManager(const QString& settingsPath, const QString& tasksPath)
        : settingsPath_(settingsPath), tasksPath_(tasksPath) {}

    // SETTINGS

    SettingsModel StorageManager::loadSettings() {
        QFile file(settingsPath_);
        SettingsModel model;
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Could not open settings file for reading:" << settingsPath_;
            return model;
        }

        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        if (doc.isNull()) {
            qWarning() << "Invalid JSON in settings file:" << settingsPath_;
            return model;
        }
        QJsonObject obj = doc.object();

        QString themeTypeStr = obj.value("themeType").toString();
        if (themeTypeStr == "Light") {
            model.setThemeType(ThemeType::Light);
        } else if (themeTypeStr == "Dark") {
            model.setThemeType(ThemeType::Dark);
        } else {
            model.setThemeType(ThemeType::Custom);
        }

        QString detailsColorStr = obj.value("detailsColor").toString();
        if (detailsColorStr == "Black") {
            model.setDetailsColor(DetailsColor::Black);
        } else if (detailsColorStr == "Blue") {
            model.setDetailsColor(DetailsColor::Blue);
        } else if (detailsColorStr == "Purple") {
            model.setDetailsColor(DetailsColor::Purple);
        } else if (detailsColorStr == "Yellow") {
            model.setDetailsColor(DetailsColor::Yellow);
        } else if (detailsColorStr == "Pink") {
            model.setDetailsColor(DetailsColor::Pink);
        } else if (detailsColorStr == "Green") {
            model.setDetailsColor(DetailsColor::Green);
        } else if (detailsColorStr == "Red") {
            model.setDetailsColor(DetailsColor::Red);
        } else {
            model.setDetailsColor(DetailsColor::White);
        }

        QString overlayModeStr = obj.value("overlayMode").toString();
        if (overlayModeStr == "Clickable") {
            model.setOverlayMode(OverlayMode::Clickable);
        } else {
            model.setOverlayMode(OverlayMode::NonClickable);
        }

        model.setOverlayOpacity(obj.value("overlayOpacity").toInt());
        QJsonObject customThemeObj = obj.value("customTheme").toObject();
        CustomTheme customTheme(
            QColor(customThemeObj.value("backgroundPrimary").toString()),
            QColor(customThemeObj.value("backgroundSecondary").toString()),
            QColor(customThemeObj.value("textPrimary").toString()),
            QColor(customThemeObj.value("textSecondary").toString()),
            QColor(customThemeObj.value("accent").toString())
        );
        model.setCustomTheme(customTheme);

        return model;
    }

    void StorageManager::saveSettings(const SettingsModel& model) {
        QJsonObject obj;
        switch (model.getThemeType()) {
            case ThemeType::Light:
                obj["themeType"] = "Light";
                break;
            case ThemeType::Dark:
                obj["themeType"] = "Dark";
                break;
            case ThemeType::Custom:
                obj["themeType"] = "Custom";
                break;
        }

        switch (model.getDetailsColor()) {
            case DetailsColor::Black:
                obj["detailsColor"] = "Black";
                break;
            case DetailsColor::Blue:
                obj["detailsColor"] = "Blue";
                break;
            case DetailsColor::Purple:
                obj["detailsColor"] = "Purple";
                break;
            case DetailsColor::White:
                obj["detailsColor"] = "White";
                break;
            case DetailsColor::Pink:
                obj["detailsColor"] = "Pink";
                break;
            case DetailsColor::Green:
                obj["detailsColor"] = "Green";
                break;
            case DetailsColor::Red:
                obj["detailsColor"] = "Red";
                break;
            case DetailsColor::Yellow:
                obj["detailsColor"] = "Yellow";
                break;
        }

        switch (model.getOverlayMode()) {
            case OverlayMode::Clickable:
                obj["overlayMode"] = "Clickable";
                break;
            case OverlayMode::NonClickable:
                obj["overlayMode"] = "NonClickable";
                break;
        }

        obj["overlayOpacity"] = model.getOverlayOpacity();
        CustomTheme customTheme = model.getCustomTheme();
        QJsonObject customThemeObj;
        customThemeObj["backgroundPrimary"] = customTheme.backgroundPrimary.name();
        customThemeObj["backgroundSecondary"] = customTheme.backgroundSecondary.name();
        customThemeObj["textPrimary"] = customTheme.textPrimary.name();
        customThemeObj["textSecondary"] = customTheme.textSecondary.name();
        customThemeObj["accent"] = customTheme.accent.name();
        obj["customTheme"] = customThemeObj;

        QJsonDocument doc(obj);
        QFile file(settingsPath_);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning() << "Could not open settings file for writing:" << settingsPath_;
            return;
        }
        file.write(doc.toJson());
    }

    // TASKS

    TaskModel StorageManager::loadTasks() {
        QFile file(tasksPath_);
        TaskModel model;
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Could not open tasks file for reading:" << tasksPath_;
            return model;
        }

        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        if (doc.isNull()) {
            qWarning() << "Invalid JSON in tasks file:" << tasksPath_;
            return model;
        }

        QJsonArray arr = doc.object()["tasks"].toArray();
        for (auto v : arr) {
            QJsonObject o = v.toObject();
            Task task(
                o["id"].toInt(),
                o["title"].toString(),
                QDate::fromString(o["date"].toString(), Qt::ISODate),
                o["isDone"].toBool(),
                static_cast<Priority>(o["priority"].toInt())
            );
            model.addTask(task);
        }

        return model;
    }

    void StorageManager::saveTasks(const TaskModel& model) {
        QJsonArray arr;
        for (const Task& task : model.getAllTasks()) {
            QJsonObject obj;
            obj["id"] = task.getId();
            obj["title"] = task.getTitle();
            obj["date"] = task.getDate().toString(Qt::ISODate);
            obj["isDone"] = task.getCompleted();
            obj["priority"] = static_cast<int>(task.getPriority().value_or(Priority::Normal));
            arr.append(obj);
        }

        QJsonObject rootObj;
        rootObj["tasks"] = arr;

        QJsonDocument doc(rootObj);
        QFile file(tasksPath_);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning() << "Could not open tasks file for writing:" << tasksPath_;
            return;
        }
        file.write(doc.toJson());
    }

}  // namespace dayboard