#include "jinputvalidatorpreferences.h"

/*private*/ /*static*/ JInputValidatorPreferences* JInputValidatorPreferences::defaultPreferences = nullptr;

/*public*/ /*static*/ /*synchronized*/ JInputValidatorPreferences* JInputValidatorPreferences::getPreferences() {
 if (defaultPreferences == nullptr) {
      defaultPreferences = new JInputValidatorPreferences();
  }
  return defaultPreferences;
}

/*public*/ /*static*/ JInputValidatorPreferences *JInputValidatorPreferences::getPreferences(Preferences* preferences) {
    return new JInputValidatorPreferences(preferences);
}

/*private*/ JInputValidatorPreferences::JInputValidatorPreferences() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: ldc           com/alexandriasoftware/swing/JInputValidatorPreferences
     * 3: invokestatic  java/util/prefs/Preferences.userNodeForPackage:(Ljava/lang/Class;)Ljava/util/prefs/Preferences;
     * 6: invokespecial com/alexandriasoftware/swing/JInputValidatorPreferences."<init>":(Ljava/util/prefs/Preferences;)V
     * 9: return
     *  */
    // </editor-fold>
}

/*private*/ JInputValidatorPreferences::JInputValidatorPreferences(Preferences* preferences) {
// Preferences defaults = Preferences.userNodeForPackage(JInputValidatorPreferences.class);
//  String fontAwesome = "/com/fontawesome/Font Awesome 5 Free-Solid-900.otf";
//  Font f;
//  try {
//      f = Font.createFont(Font.TRUETYPE_FONT, JInputValidatorPreferences.class.getResourceAsStream(preferences.get("font", defaults.get("font", fontAwesome))));
//  }
//  catch (FontFormatException | IOException ex) {
//      LoggerFactory.getLogger(this.getClass()).error("Unable to get Font resource named {}", preferences.get("font", fontAwesome), ex);
//      f = (new JLabel()).getFont();
//  }
//  font = f;
  unknownIcon = "\uf059";//preferences.get("unknown.icon", defaults.get("unknown.icon", "\uf059"));
  unknownColor = QColor(0x73BCF7);//new Color(preferences.getInt("unknown.color", defaults.getInt("inknown.color", 0x73BCF7)));
  informationIcon = "\uf05a";//preferences.get("information.icon", defaults.get("information.icon", "\uf05a"));
  informationColor = QColor(0x73BCF7);//new Color(preferences.getInt("information.color", defaults.getInt("information.color", 0x73BCF7)));
  successIcon = "\uf058";//preferences.get("success.icon", defaults.get("success.icon", "\uf058"));
  successColor = QColor(0x92D400);//new Color(preferences.getInt("success.color", defaults.getInt("success.color", 0x92D400)));
  warningIcon = "\uf071";//preferences.get("warning.icon", defaults.get("warning.icon", "\uf071"));
  warningColor = QColor(0xF0AB00);//new Color(preferences.getInt("warning.color", defaults.getInt("warning.color", 0xF0AB00)));
  dangerIcon = "\uf06a";//preferences.get("danger.icon", defaults.get("danger.icon", "\uf06a"));
  dangerColor = QColor(0xC9190B);//new Color(preferences.getInt("danger.color", defaults.getInt("danger.color", 0xC9190B)));
}

/*public*/ QFont JInputValidatorPreferences::getFont() {
 return font;
}


/**
 * Get the icon for the specified type. Note the icon can be any string that
 * can be rendered using the font returned by {@link #getFont()} although it
 * is recommended this be a Unicode glyph or emoji-style icon.
 *
 * @param type the validation type to get
 * @return the specified icon or an empty String if type is
 *         {@link Validation.Type#NONE} or not recognized
 */
/*public*/ QString JInputValidatorPreferences::getIcon(Validation::Type type) {
    switch (type) {
        case Validation::UNKNOWN:
            return unknownIcon;
        case Validation::INFORMATION:
            return informationIcon;
        case Validation::SUCCESS:
            return successIcon;
        case Validation::WARNING:
            return warningIcon;
        case Validation::DANGER:
            return dangerIcon;
        case Validation::NONE:
        default:
            // ignored, so return empty string
            return "";
    }
}

/**
 * Get the icon for the specified type.
 *
 * @param type the validation type to get
 * @return the specified color or {@link java.awt.SystemColor#textText} if
 *         type is {@link Validation.Type#NONE} or not recognized
 */
/*public*/ QColor JInputValidatorPreferences::getColor(Validation::Type type) {
    switch (type) {
        case Validation::UNKNOWN:
            return unknownColor;
        case Validation::INFORMATION:
            return informationColor;
        case Validation::SUCCESS:
            return successColor;
        case Validation::WARNING:
            return warningColor;
        case Validation::DANGER:
            return dangerColor;
        case Validation::NONE:
        default:
            // ignored, so return anything
            //return SystemColor.textText;
     return Qt::black;
    }
}
