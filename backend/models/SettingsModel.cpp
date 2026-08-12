/***
* Settings working model
***/

#include "SettingsModel.hpp"

namespace dayboard {

    static QColor getEnumDetailsColor(DetailsColor color) {
        switch (color) {
            case DetailsColor::Black: return QColor("#000000");
            case DetailsColor::Blue:    return QColor("#2e81a4");
            case DetailsColor::Purple:  return QColor("#6b3180");
            case DetailsColor::White:    return QColor("#ffffff");
            case DetailsColor::Pink:    return QColor("#b1386c");
            case DetailsColor::Green:    return QColor("#19966f");
        }
        return QColor("#5f6163");
    }

    SettingsModel::SettingsModel()
        : themeType_(ThemeType::Light),
          detailsColor_(DetailsColor::Black),
          overlayMode_(OverlayMode::Clickable),
          overlayOpacity_(80),
          customTheme_(QColor("#ffffff"), QColor("#f0f0f0"),
                    QColor("#000000"), QColor("#555555"), getEnumDetailsColor(detailsColor_))
    {}

}