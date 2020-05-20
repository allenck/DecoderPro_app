#include "namedbeanusagereport.h"
#include "namedbean.h"

/**
 * This is a data structure to pass usage information from getUsageReport() requests
 * back to the calling object.
 *
 * @author Dave Sand Copyright (C) 2020
 */
//@javax.annotation.concurrent.Immutable
///*public*/ class NamedBeanUsageReport {


/**
 * Create report with the required key.
 */
/*public*/ NamedBeanUsageReport::NamedBeanUsageReport(/*@Nonnull*/ QString usageKey) {
    //this(usageKey, null, "");
 this->usageKey = usageKey;
 this->usageBean = nullptr;
 this->usageData = "";
}

/**
 * Create report with the required key and a bean.
 */
/*public*/ NamedBeanUsageReport::NamedBeanUsageReport(/*@Nonnull*/ QString usageKey, NamedBean* usageBean) {
    //this(usageKey, usageBean, "");
 this->usageKey = usageKey;
 this->usageBean = usageBean;
 this->usageData = "";
}

/**
 * Create report with the required key and additional data.
 */
/*public*/ NamedBeanUsageReport::NamedBeanUsageReport(/*@Nonnull*/ QString usageKey, QString usageData) {
    //this(usageKey, null, usageData);
 this->usageKey = usageKey;
 this->usageBean = nullptr;
 this->usageData = usageData;
}

/**
 * Create a usage report.
 *
 * @param usageKey Identifies the report type.  Used to control result
 * processing.  Might also be used as a bundle key.
 * @param usageBean Identifies a related bean suach as SML destination mast.  Can be null.
 * @param usageData Optional additional data.
 */
/*public*/ NamedBeanUsageReport::NamedBeanUsageReport(/*@Nonnull*/ QString usageKey, NamedBean* usageBean, QString usageData) {
    this->usageKey = usageKey;
    this->usageBean = usageBean;
    this->usageData = usageData;
}
