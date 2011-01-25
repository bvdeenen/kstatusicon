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
 * @short the main class for KTeatime
 *
 * @author Stefan Böhmann <kde@hilefoks.org>
 */
class TopLevel : public KSystemTrayIcon
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.vandeenensupport.TopLevel")
    public:
        explicit TopLevel(const KAboutData *aboutData, const QString &icon = "kteatime", QWidget *parent = 0);
        ~TopLevel();

    public Q_SLOTS:
        void teaTimeEvent();
        void reset();
        void showPopup(QSystemTrayIcon::ActivationReason reason);

    private:
        void checkState();
        void loadTeaMenuItems();
        QPoint calculatePopupPoint();
        void repaintTrayIcon();

    private:
        QAction  *m_exitAct;
        KHelpMenu *m_helpMenu;
        QTimer *m_timer;
        KPassivePopup *m_popup;

        int m_runningTeaTime;
        int m_nextNotificationTime;

        /** should we use notifications defined by KNotification */
        bool m_usenotification;

        /** should we show a popup for events */
        bool m_usepopup;

        /** auto hide the popup? */
        bool m_autohide;

        /** time after the popup should be hide. */
        int m_autohidetime;

        /** remind us about a ready tea? */
        bool m_usereminder;

        /** the time bedween remind events */
        int m_remindertime;

        /** use a visual effect in the system tray icon. */
        bool m_usevisualize;

        const QIcon m_icon;

        QPixmap m_pix;
};


#endif

// kate: word-wrap off; encoding utf-8; indent-width 4; tab-width 4; line-numbers on; mixed-indent off; remove-trailing-space-save on; replace-tabs-save on; replace-tabs on; space-indent on;
// vim:set spell et sw=4 ts=4 nowrap cino=l1,cs,U1:
