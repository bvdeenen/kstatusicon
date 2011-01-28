#ifndef TOPLEVEL_H
#define TOPLEVEL_H

#include <QIcon>
#include <QPixmap>
#include <KSystemTrayIcon>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>


class QAction;
class KHelpMenu;
class KPassivePopup;
class KAboutData;



/**
 * @short the main class for kstatusicon
 *
 */
class TopLevel : public KSystemTrayIcon
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.vandeenensupport.TopLevel")
    Q_PROPERTY(QString icon READ icon WRITE setIconFile)
    Q_PROPERTY(QString name READ objectName WRITE setObjectName)
    public:
        explicit TopLevel(const KAboutData *aboutData, const QString &icon="" , QWidget *parent = 0);
        ~TopLevel();
        void setIconFile(const QString&);
        QString icon() { return m_iconfile; };

    public Q_SLOTS:

    private:
        void repaintTrayIcon();

    private:
        QString m_iconfile;
        QAction  *m_exitAct;
        KHelpMenu *m_helpMenu;
        QIcon m_icon;
        QPixmap m_pix;
};


#endif

// kate: word-wrap off; encoding utf-8; indent-width 4; tab-width 4; line-numbers on; mixed-indent off; remove-trailing-space-save on; replace-tabs-save on; replace-tabs on; space-indent on;
// vim:set spell et sw=4 ts=4 nowrap cino=l1,cs,U1:
