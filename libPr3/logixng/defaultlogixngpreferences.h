#ifndef DEFAULTLOGIXNGPREFERENCES_H
#define DEFAULTLOGIXNGPREFERENCES_H

#include <preferencesbean.h>
#include "profilemanager.h"
#include "malesocket.h"
#include "logixngpreferences.h"

class Preferences;
class DefaultLogixNGPreferences : public PreferencesBean, public LogixNGPreferences
{
  Q_OBJECT
  Q_INTERFACES(LogixNGPreferences)
 public:
  explicit DefaultLogixNGPreferences(QObject *parent = nullptr);
  ~DefaultLogixNGPreferences() {}
  DefaultLogixNGPreferences(const DefaultLogixNGPreferences&): PreferencesBean(ProfileManager::getDefault()->getActiveProfile()) {}
  /*public*/  static /*final*/ QString START_LOGIXNG_ON_LOAD;// = "startLogixNGOnStartup";
  /*public*/  static /*final*/ QString USE_GENERIC_FEMALE_SOCKETS;// = "useGenericFemaleSockets";
  /*public*/  static /*final*/ QString INSTALL_DEBUGGER;// = "installDebugger";
  /*public*/  static /*final*/ QString SHOW_SYSTEM_USER_NAMES;// = "showSystemUserNames";
  /*public*/  static /*final*/ QString ERROR_HANDLING_TYPE;// = "errorHandlingType";
  /*public*/  static /*final*/ QString TREE_EDITOR_HIGHLIGHT_ROW;// = "treeEditorHighlightRow";
  /*public*/  bool compareValuesDifferent(LogixNGPreferences* prefs);
  /*public*/  void apply(LogixNGPreferences* prefs);
  /*public*/  void save();
  /*public*/  QString getClass() override {return "jmri.jmrit.logixng.implementation.DefaultLogixNGPreferences";}
  /*public*/  void setStartLogixNGOnStartup(bool value)override;
  /*public*/  bool getStartLogixNGOnStartup()override;
  /*public*/  void setShowSystemUserNames(bool value)override;
  /*public*/  bool getShowSystemUserNames()override;
  /*public*/  void setInstallDebugger(bool value)override;
  /*public*/  bool getInstallDebugger()override;
  /*public*/  void setErrorHandlingType(ErrorHandlingType::TYPES type) override;
  /*public*/  ErrorHandlingType::TYPES getErrorHandlingType()override;
  /*public*/  void setTreeEditorHighlightRow(bool value)override;
  /*public*/  bool getTreeEditorHighlightRow()override;

  QObject* self() override{return (QObject*)this;}
 private:

  /*private*/ bool _startLogixNGOnLoad = true;
  /*private*/ bool _showSystemUserNames = false;
  /*private*/ bool _installDebugger = true;
  /*private*/ ErrorHandlingType::TYPES _errorHandlingType = ErrorHandlingType::ShowDialogBox;
  /*private*/ bool _treeEditorHighlightRow = false;
  /*private*/ void readPreferences(Preferences* sharedPreferences);

};
Q_DECLARE_METATYPE(DefaultLogixNGPreferences)
#endif // DEFAULTLOGIXNGPREFERENCES_H
