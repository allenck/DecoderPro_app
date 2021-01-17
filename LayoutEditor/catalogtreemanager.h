#ifndef CATALOGTREEMANAGER_H
#define CATALOGTREEMANAGER_H
#include "abstractmanager.h"
#include "liblayouteditor_global.h"

class CatalogTree;
class LIBLAYOUTEDITORSHARED_EXPORT CatalogTreeManager : public AbstractManager
{
    Q_OBJECT
public:
    explicit CatalogTreeManager(QObject *parent = 0);
    ~CatalogTreeManager() override{}
    CatalogTreeManager(const CatalogTreeManager&) : AbstractManager() {}
    static /*final*/ QStringList IMAGE_FILTER;// = {"gif", "jpg", "jpeg", "png"};
    static /*final*/ QStringList SOUND_FILTER;// = {"wav"};
    static /*final*/ QStringList SCRIPT_FILTER;// = {"py", "scpt"};
    /*public*/ virtual CatalogTree* getCatalogTree(QString /*name*/) {return NULL;}

    /**
     * Locate an instance based on a system name.  Returns null if no
     * instance already exists.
     * @return requested CatalogTree object or null if none exists
     */
    /*public*/ virtual NamedBean* getBySystemName(QString /*systemName*/) const {return NULL;}
    /**
     * Locate an instance based on a user name.  Returns null if no
     * instance already exists.
     * @return requested CatalogTree object or null if none exists
     */
    /*public*/ virtual NamedBean* getByUserName(QString /*userName*/) const {return NULL;}
    /**
     * Return an instance with the specified system and user names.
     * Note that two calls with the same arguments will get the same instance;
     * there is only one CatalogTree object representing a given physical CatalogTree
     * and therefore only one with a specific system or user name.
     *<P>
     * This will always return a valid object reference; a new object will be
     * created if necessary. In that case:
     *<UL>
     *<LI>If a null reference is given for user name, no user name will be associated
     *    with the CatalogTree object created; a valid system name must be provided
     *<LI>If both names are provided, the system name defines the
     *    hardware access of the desired CatalogTree, and the user address
     *    is associated with it. The system name must be valid.
     *</UL>
     * Note that it is possible to make an inconsistent request if both
     * addresses are provided, but the given values are associated with
     * different objects.  This is a problem, and we don't have a
     * good solution except to issue warnings.
     * This will mostly happen if you're creating CatalogTree objects when you should
     * be looking them up.
     * @return requested CatalogTree object (never null)
     */
    /*public*/ virtual CatalogTree* newCatalogTree(QString /*systemName*/, QString /*userName*/) {return nullptr;}

    /*public*/ virtual bool isIndexChanged() {return false;}

    /*public*/ virtual void indexChanged(bool /*changed*/) {}

    /**
     * Get a list of all CatalogTree objects' system names.
     */
    /*public*/  QStringList getSystemNameList() override{return QStringList();}

    /*public*/  void Register(NamedBean*) const override{}

    /*public*/ virtual void storeImageIndex() {}
    /*public*/ QString getNamedBeanClass()const override {
        return "NamedBean";
    }

    int getXMLOrder() const override
    {
     return Manager::MEMORIES; // ??
    }
signals:

public slots:
private:

};
Q_DECLARE_METATYPE(CatalogTreeManager)
#endif // CATALOGTREEMANAGER_H
