#ifndef JINPUTVALIDATORPREFERENCES_H
#define JINPUTVALIDATORPREFERENCES_H
#include <QFont>
#include <QColor>
#include "preferences.h"
#include "validation.h"

class JInputValidatorPreferences
{
 public:
  /*public*/ static /*synchronized*/ JInputValidatorPreferences* getPreferences();
  /*public*/ static JInputValidatorPreferences* getPreferences(Preferences* preferences);
  /*public*/ QFont getFont();
  /*public*/ QString getIcon(Validation::Type type);
  /*public*/ QColor getColor(Validation::Type type);

 private:
  /*private*/ static JInputValidatorPreferences* defaultPreferences;// = nullptr;
  /*private*/ /*final*/  QFont font;
  /*private*/ /*final*/  QString unknownIcon;
  /*private*/ /*final*/  QColor unknownColor;
  /*private*/ /*final*/  QString informationIcon;
  /*private*/ /*final*/  QColor informationColor;
  /*private*/ /*final*/  QString successIcon;
  /*private*/ /*final*/  QColor successColor;
  /*private*/ /*final*/  QString warningIcon;
  /*private*/ /*final*/  QColor warningColor;
  /*private*/ /*final*/  QString dangerIcon;
  /*private*/ /*final*/  QColor dangerColor;
  /*private*/ JInputValidatorPreferences();
  /*private*/ JInputValidatorPreferences(Preferences* preferences);

  friend class JInputValidator;
};

#endif // JINPUTVALIDATORPREFERENCES_H
