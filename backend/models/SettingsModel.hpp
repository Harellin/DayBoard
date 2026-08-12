/***
* Settings working model
***/

#ifndef SETTINGSMODEL_MODEL_HPP_
#define SETTINGSMODEL_MODEL_HPP_

#include <QColor>

namespace dayboard {

    enum class ThemeType {
        Light,
        Dark,
        Custom
    };

    enum class DetailsColor {
        Black,
        Blue,
        Purple,
        White,
        Pink,
        Green
    };

    enum class OverlayMode {
        Clickable,
        NonClickable
    };

    struct CustomTheme {
        QColor backgroundPrimary;
        QColor backgroundSecondary;
        QColor textPrimary;
        QColor textSecondary;
        QColor accent;

        CustomTheme() = default;

        CustomTheme(QColor bg1, QColor bg2, QColor t1, QColor t2, QColor acc) : 
            backgroundPrimary(bg1), backgroundSecondary(bg2),
            textPrimary(t1), textSecondary(t2), accent(acc) {}
    };

    class SettingsModel {
        private:
            ThemeType themeType_;
            DetailsColor detailsColor_;
            OverlayMode overlayMode_;
            CustomTheme customTheme_;
            int overlayOpacity_;

        public:
            SettingsModel();

            ThemeType getThemeType() const { return themeType_; };
            void setThemeType(ThemeType themeType) { themeType_ = themeType; };

            DetailsColor getDetailsColor() const { return detailsColor_; };
            void setDetailsColor(DetailsColor detailsColor) { detailsColor_ = detailsColor; };

            OverlayMode getOverlayMode() const { return overlayMode_; };
            void setOverlayMode(OverlayMode overlayMode) { overlayMode_ = overlayMode; };

            CustomTheme getCustomTheme() const { return customTheme_; };
            void setCustomTheme(const CustomTheme &customTheme) { customTheme_ = customTheme; };

            int getOverlayOpacity() const { return overlayOpacity_; };
            void setOverlayOpacity(int overlayOpacity) { overlayOpacity_ = overlayOpacity; };
    };
}

#endif // SETTINGSMODEL_MODEL_HPP_