/*
 *   This file is part of the KTeaTime application.
 *
 *   Copyright (C) 1998-1999  Matthias Hoelzer-Kluepfel <hoelzer@kde.org>
 *   Copyright (C) 2002-2003  Martin Willers <willers@xm-arts.de>
 *   Copyright (c) 2007-2009  Stefan Böhmann <kde@hilefoks.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include "toplevel.h"
//#include "timeedit.h"
//#include "settings.h"
//#include "tea.h"

#include <QString>
#include <QAction>
#include <QTimer>
#include <QPainter>
#include <QBrush>
#include <QActionGroup>

#include <KMenu>
#include <KActionCollection>
#include <KHelpMenu>
#include <KPassivePopup>
#include <KGlobalSettings>
#include <KNotification>
#include <KAboutData>


TopLevel::TopLevel(const KAboutData *aboutData, const QString &icon, QWidget *parent)
  : KSystemTrayIcon( loadIcon(icon), parent ),
    m_runningTeaTime( 0 ),
    m_nextNotificationTime( 0 ),
    m_icon( loadIcon( icon ) ),
    m_pix( loadIcon( icon ).pixmap( QSize( 22, 22 ) ) )
{
    QApplication::setQuitOnLastWindowClosed( false );

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
    checkState();
}


TopLevel::~TopLevel()
{
    delete m_helpMenu;
    delete m_timer;
    delete m_popup;
}


void TopLevel::checkState() {
    const bool state = m_runningTeaTime != 0;

    if( !state ) {
        m_popup->setView( i18n( "The Tea Cooker" ), i18n( "No steeping tea." ), m_pix );
        setToolTip( i18n( "The Tea Cooker" ) );
    }
}


void TopLevel::repaintTrayIcon()
{
    static float n=0;
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


void TopLevel::teaTimeEvent()
{
    QString title = i18n( "The Tea Cooker" );

        repaintTrayIcon();
    m_timer->start( 1000 );
}



void TopLevel::showPopup(QSystemTrayIcon::ActivationReason reason)
{
    if( reason == QSystemTrayIcon::Context ) {
        m_popup->setVisible( false );
    }
    else if( reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick ) {
        if( m_popup->isVisible() ) {
            m_popup->setVisible( false );
        }
        else {
            m_popup->show( calculatePopupPoint() );
        }
    }
}


QPoint TopLevel::calculatePopupPoint()
{
    QPoint pos = geometry().topLeft();

    int x = pos.x();
    int y = pos.y();
    int w = m_popup->minimumSizeHint().width();
    int h = m_popup->minimumSizeHint().height();

    QRect r = KGlobalSettings::desktopGeometry( QPoint( x+w/2, y+h/2 ) );

    if( x < r.center().x() ) {
        x += geometry().width();
    }
    else {
        x -= w;
    }

    if( (y+h) > r.bottom() ) {
        y = r.bottom() - h;
    }

    if( (x+w) > r.right() ) {
        x = r.right() - w;
    }

    if( y < r.top() ) {
        y = r.top();
    }

    if( x < r.left() ) {
        x = r.left();
    }

    return QPoint( x,y );
}


// kate: word-wrap off; encoding utf-8; indent-width 4; tab-width 4; line-numbers on; mixed-indent off; remove-trailing-space-save on; replace-tabs-save on; replace-tabs on; space-indent on;
// vim:set spell et sw=4 ts=4 nowrap cino=l1,cs,U1:
