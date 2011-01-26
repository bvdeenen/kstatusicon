#include "toplevel.h"
#include "topleveladaptor.h"

#include <QString>
#include <QAction>
#include <QTimer>
#include <QPainter>
#include <QDBusConnection>

#include <KMenu>
#include <KActionCollection>
#include <KHelpMenu>
#include <KPassivePopup>
#include <KGlobalSettings>
#include <KNotification>
#include <KAboutData>


TopLevel::TopLevel(const KAboutData *aboutData, const QString &icon, QWidget *parent)
  : KSystemTrayIcon( loadIcon(icon), parent ),
    m_icon( loadIcon( icon ) ),
    m_pix( loadIcon( icon ).pixmap( QSize( 22, 22 ) ) )
{
    new TopLevelAdaptor(this);
    QApplication::setQuitOnLastWindowClosed( false );
    QDBusConnection::sessionBus().registerObject("/TopLevel", this);
    QDBusConnection::sessionBus().registerService("com.vandeenensupport.Toplevel");

    m_exitAct = actionCollection()->action(KStandardAction::name( KStandardAction::Quit ) );
    m_exitAct->setShortcut( 0 ); // Not sure if it is correct.

    m_helpMenu = new KHelpMenu( 0, aboutData, false );


    contextMenu()->addMenu( m_helpMenu->menu() );
    contextMenu()->addAction( m_exitAct );

}

void TopLevel::setIconFile(const QString &f)
{
    m_iconfile=f;
    m_icon =QIcon(loadIcon(f));
    repaintTrayIcon();
}

TopLevel::~TopLevel()
{
    delete m_helpMenu;
}


void TopLevel::repaintTrayIcon()
{
    m_pix = m_icon.pixmap( QSize( 22, 22 ) );
    setIcon( m_pix );
}



// kate: word-wrap off; encoding utf-8; indent-width 4; tab-width 4; line-numbers on; mixed-indent off; remove-trailing-space-save on; replace-tabs-save on; replace-tabs on; space-indent on;
// vim:set spell et sw=4 ts=4 nowrap cino=l1,cs,U1:
