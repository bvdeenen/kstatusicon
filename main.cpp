/*
 *   kstatusicon
 *
 *   Copyright (C) 2011 Bart van Deenen <info@vandeenensupport.com>
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

/*
 *  small application to create an icon in the kde status bar, that can be
 *  (shell) scripted via qdbus. See test-kstatusicon.sh for an example of how
 *  to do this.
 *
 */
#include "toplevel.h"

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>


int main (int argc, char *argv[])
{
    KAboutData aboutData( "kstatusicon", 0, ki18n( "KStatusIcon" ), "0.1",
                          ki18n( "KDE utility for scripted access to an icon in the status bar." ),
                          KAboutData::License_GPL,
                          ki18n( "(c) 2011 Bart van Deenen")
                        );

    aboutData.addAuthor( ki18n( "Bart van Deenen" ), KLocalizedString(), "info@vandeenensupport.com");

    KCmdLineArgs::init( argc, argv, &aboutData );

    KCmdLineOptions options;
    KCmdLineArgs::addCmdLineOptions( options );

    KApplication app;
    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

    TopLevel *toplevel=new TopLevel( &aboutData );

    args->clear();

    toplevel->show();

    return app.exec();
}


// kate: word-wrap off; encoding utf-8; indent-width 4; tab-width 4; line-numbers on; mixed-indent off; remove-trailing-space-save on; replace-tabs-save on; replace-tabs on; space-indent on;
// vim:set spell et sw=4 ts=4 nowrap cino=l1,cs,U1:
