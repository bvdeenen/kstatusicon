#include "toplevel.h"
#include "topleveladaptor.h"

#include <QString>
#include <QAction>
#include <QTimer>
#include <QPainter>
#include <QBrush>
#include <QActionGroup>
#include <QDBusConnection>

#include <KMenu>
#include <KActionCollection>
#include <KHelpMenu>
#include <KPassivePopup>
#include <KGlobalSettings>
#include <KNotification>
#include <KAboutData>

static float n=0;

TopLevel::TopLevel(const KAboutData *aboutData, const QString &icon, QWidget *parent)
  : KSystemTrayIcon( loadIcon(icon), parent ),
    m_runningTeaTime( 0 ),
    m_nextNotificationTime( 0 ),
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


    m_popup = new KPassivePopup();
    m_popup->setAutoDelete( false );

    m_timer = new QTimer( this );

    connect( m_timer, SIGNAL( timeout() ), this, SLOT( teaTimeEvent() ) );
    connect( this, SIGNAL( activated(QSystemTrayIcon::ActivationReason) ),
             this, SLOT( showPopup(QSystemTrayIcon::ActivationReason) ) );

    m_timer->start( 1000 );
}

void TopLevel::setIconfile(const QString &f)
{
    m_iconfile=f;
    m_icon =QIcon(loadIcon(f));
    repaintTrayIcon();
}

TopLevel::~TopLevel()
{
    delete m_helpMenu;
    delete m_timer;
    delete m_popup;
}


void TopLevel::repaintTrayIcon()
{
     m_pix = m_icon.pixmap( QSize( 22, 22 ) );

        QPainter p( &m_pix );
        p.setRenderHint( QPainter::Antialiasing );

        p.setBrush( QColor( 0, 255, 0, 190 ) );
        QRectF rectangle( 2, geometry().height()-12, 10, 10 );
        p.drawPie( rectangle, 90*16, 360*16 );

            p.setBrush( QColor(255, 0, 0, 190) );
            p.drawPie( rectangle, 90*16, -( 360*16 * n ) );
            n+=0.1;
            if ( n>1 ) n=0;
        setIcon( m_pix );
}


void TopLevel::reset()
{
    n=0;
}

void TopLevel::teaTimeEvent()
{
    QString title = i18n( "The Tea Cooker" );

        repaintTrayIcon();
    m_timer->start( 1000 );
}



// kate: word-wrap off; encoding utf-8; indent-width 4; tab-width 4; line-numbers on; mixed-indent off; remove-trailing-space-save on; replace-tabs-save on; replace-tabs on; space-indent on;
// vim:set spell et sw=4 ts=4 nowrap cino=l1,cs,U1:
