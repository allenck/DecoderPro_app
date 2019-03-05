#ifndef SECTIONMANAGER_H
#define SECTIONMANAGER_H
#include "abstractmanager.h"
#include "section.h"
#include <QString>
#include "decimalformat.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT SectionManager : public AbstractManager
{
    Q_OBJECT
public:
    explicit SectionManager(QObject *parent = 0);
    ~SectionManager() {}
    SectionManager(const SectionManager&) : AbstractManager() {}
    int getXMLOrder();
    QString getSystemPrefix();
    char typeLetter() ;
    /**
     * Method to create a new Section if the Section does not exist
     *   Returns null if a Section with the same systemName or userName
     *       already exists, or if there is trouble creating a new Section.
     */
    Section* createNewSection(QString systemName, QString userName);
    Section* createNewSection(QString userName);
    /**
     * Remove an existing Section
     */
    /*public*/ void deleteSection(Section* y);
    /**
     * Method to get an existing Section.  First looks up assuming that
     *      name is a User Name.  If this fails looks up assuming
     *      that name is a System Name.  If both fail, returns NULL.
     */
    /*public*/ Section* getSection(QString name);
    /*public*/ Section* getBySystemName(QString name);
    /*public*/ Section* getByUserName(QString key);

    /**
     * Validates all Sections
     */
    /*public*/ int validateAllSections(JmriJFrame* frame, LayoutEditor* lePanel);
    /**
     * Checks direction sensors in SSL for signals.
     * Returns '0' for no errors
     * Returns n, where n is a positive number for number of errors or warnings
     * Returns -1 if there is no LayoutEditor panel
     * Returns -2 if there are no Sections defined
     */
    /*public*/ int setupDirectionSensors(LayoutEditor* lePanel);
    /**
     * Removes direction sensors from SSL for all signals.
     * Returns '0' for no errors
     * Returns n, where n is a positive number for number of errors or warnings
     * Returns -1 if there is no LayoutEditor panel
     * Returns -2 if there are no Sections defined
     */
    /*public*/ int removeDirectionSensorsFromSSL(LayoutEditor* lePanel);

    /**
     * Initialize all blocking sensors that exist - sets them to 'ACTIVE'
     */
    /*public*/ void initializeBlockingSensors ();
    static /*public*/ SectionManager* instance();

    
public slots:
private:
    DecimalFormat* paddedNumber;// =  new DecimalFormat("0000");
    static SectionManager* _instance;// = NULL;

    int lastAutoSectionRef;// = 0;
    Logger log;
};
Q_DECLARE_METATYPE(SectionManager)
#endif // SECTIONMANAGER_H
