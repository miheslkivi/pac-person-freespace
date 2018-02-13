
/* This file is derived from Qt4 example software "Ported Asteroids" and examples on getopt.h man page
*
*  Pac-person freespace continuum undiscreted ( PPFCU or p-pf-scu-d ) - Copyright (C) 2018 by Mikko Heiska
*
*
*/




/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#define FALSE 0
#define TRUE 1

#include <QtGui>
#include <QtWidgets>
#include <QtNetwork>
#include"gmu.h"
#include "toplevel.h"
#include<string>
#include<unistd.h>
#include<getopt.h>

#include <QtOpenGL>
#include <QOpenGLWidget>

#include<iostream>
#include<QSettings>
int main( int argc, char **argv )
{
    //  Q_INIT_RESOURCE(pacman);

    string hst="-h";
    string hst2="--h";
    string hst3="-help";
    string hst4="--help";
    string hst5="help";
    string hst6="h";
    gsvar nofa;
    nofa.filespath="../pac-person-freespace-0.9.1/filesforbin/";
    if( argc>1 )
    {
        if( hst.compare(   argv[1] )==0 or hst2.compare(   argv[1] )==0 or hst3.compare(   argv[1] )==0 or
                hst4.compare(   argv[1] )==0 or hst5.compare(   argv[1] )==0 or hst6.compare(   argv[1] )==0  )
        {
            string ths="cat ";
            ths+=nofa.filespath.toStdString()+string("help-cmd.txt");
            if(  system( ths.c_str() )==-1  )
            {
                cout << " main.cpp: error " << endl;

            }
            exit(0);
        }
    }

    nofa.nofa=-1;
    nofa.trail=-1;
    nofa.pac1x1=-1200;
    nofa.pac1y1=-600;
    nofa.ghostx=-388;
    nofa.ghosty=-2210;
    nofa.ghosts=-20;

    nofa.wwidth=-1700;
    nofa.wheight=-900;
    nofa.clinepacshipangle=-1234;
    nofa.ghinv=0;
    nofa.sightb=1;
    nofa.shortmsg=0;
    nofa.shortmsgcou=0;
    nofa.ghostscline=-1;

    nofa.opengl=0;
    nofa.openglcl=0;

    nofa.fullscreen=0;
    nofa.fullscreencl=0;

    nofa.drivemode=0;
    nofa.drivemodecl=0;

    nofa.ghinvcl=0;

    int c;
    int digit_optind = 0;
    string wid( "width" );
    string hei( "height" );
    string miss( "no-faulty-missiles");
    string miss2( "nofaultymissiles");
    string scafa( "scalefactor" );
    string notrail("no-trail");
    string notrail2("notrail");
    string trail("trail");
    string trail2("trial");

    string pac1x( "pacx" );
    string pac1y( "pacy" );

    string ghostx( "ghostx" );
    string ghosty( "ghosty" );

    string arena_picture( "arena_picture" );
    string overlay_picture( "overlay_picture" );
    string configfile( "configfile" );
    string ghosts( "ghosts" );

    string drivemode( "drivemode");

    string colorname( "colorname" );
    string pacangle("pacangle" );
    string openglon("openglon");
    string opengloff("opengloff");

    string fullscreen("fullscreen");

    string ghostshide("ghostshide");
    string ghostshide2("ghosts_hide");


    //  cout << endl << "--" << wid << " pix  ( " << nofa.wwidth << " )  --" << hei << " pix  ( " << nofa.wheight << " )  --" << miss << "   " << "--" << scafa << " 0.2 - 4  ( " << nofa.scker << " )  " << endl;

    while (1)
    {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] =
        {
        {"height",     required_argument, 0,  0 },
        { miss.c_str(),  no_argument,       0,  0 },
        {"width",  required_argument, 0,  0 },
        {miss2.c_str(), no_argument,       0,  0 },
        { scafa.c_str(),  required_argument, 0, 0},
        { notrail.c_str(),    no_argument, 0,  0 },
        { notrail2.c_str(),    no_argument, 0,  0 },
        { trail.c_str(),    no_argument, 0,  0 },
        { trail2.c_str(),    no_argument, 0,  0 },
        {pac1x.c_str(),     required_argument, 0,  0 },
        {pac1y.c_str(),     required_argument, 0,  0 },
        {ghostx.c_str(),     required_argument, 0,  0 },
        {ghosty.c_str(),     required_argument, 0,  0 },
        { arena_picture.c_str(),    required_argument, 0,  0 },
        { overlay_picture.c_str(),  required_argument, 0,  0 },
        { configfile.c_str(),  required_argument, 0,  0 },
        {  ghosts.c_str(),  required_argument, 0,  0 },
        { drivemode.c_str(),    no_argument, 0,  0 },
        { colorname.c_str(),    required_argument, 0,  0 },
        { pacangle.c_str(),    required_argument, 0,  0 },
        { openglon.c_str(),    no_argument, 0,  0 },
        { opengloff.c_str(),    no_argument, 0,  0 },
        { fullscreen.c_str(),    no_argument, 0,  0 },
        { ghostshide.c_str(),    no_argument, 0,  0 },
        { ghostshide2.c_str(),    no_argument, 0,  0 },


        {0,         0,                 0,  0 }
    };

        c = getopt_long(argc, argv, "abc:d:012",
                        long_options, &option_index);
        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            printf("option %s", long_options[option_index].name);

            if( long_options[ option_index ].name==miss or  long_options[ option_index ].name==miss2 )
            {
                nofa.nofa=1;
            }
            if( long_options[ option_index ].name==notrail or  long_options[ option_index ].name==notrail2 )
            {
                nofa.trail=0;

            }
            if( long_options[ option_index ].name==trail or  long_options[ option_index ].name==trail2 )
            {
                nofa.trail=1;

            }
            if( long_options[ option_index ].name==drivemode  )
            {
                nofa.drivemode=1;
                nofa.drivemodecl=1;
            }
            else
            {
                //   nofa.drivemode=0;

            }
            nofa.openglcl=0;

            if( long_options[ option_index ].name==opengloff  )
            {
                nofa.opengl=0;
                nofa.openglcl=1;
            }
            if( long_options[ option_index ].name==openglon  )
            {
                nofa.opengl=1;
                nofa.openglcl=1;

            }
            nofa.fullscreencl=0;
            if( long_options[ option_index ].name==fullscreen  )
            {
                nofa.fullscreen =1;
                nofa.fullscreencl=1;
            }
            nofa.ghinvcl=0;
            if( long_options[ option_index ].name==ghostshide or long_options[ option_index ].name==ghostshide2  )
            {
                nofa.ghinv=1;
                nofa.ghinvcl=1;

            }
            if (optarg)
            {
                printf(" with arg %s", optarg);
                if( long_options[option_index].name==wid )
                {
                    nofa.wwidth=atoi( optarg );
                }
                if( long_options[option_index].name==hei )
                {
                    nofa.wheight=atoi( optarg );
                }

                if( long_options[option_index].name==scafa )
                {
                    nofa.scafa=atof( optarg );
                }
                if( long_options[option_index].name==pac1x )
                {
                    nofa.pac1x1=atof( optarg );
                }
                if( long_options[option_index].name==pac1y )
                {
                    nofa.pac1y1=atof( optarg );
                }

                if( long_options[option_index].name==ghostx )
                {
                    nofa.ghostx=atof( optarg );
                }

                if( long_options[option_index].name==ghosty )
                {
                    nofa.ghosty=atof( optarg );
                }
                if( long_options[option_index].name==arena_picture )
                {
                    nofa.clinearenapic= optarg ;
                }
                if( long_options[option_index].name==overlay_picture )
                {
                    nofa.clinearenaoverlay= optarg ;
                }
                if( long_options[option_index].name==configfile )
                {
                    nofa.configfile= optarg ;
                }
                if( long_options[option_index].name==ghosts )
                {
                    nofa.ghostscline= atoi( optarg ) ;
                }
                if( long_options[option_index].name==colorname )
                {
                    nofa.clinecolorname=optarg ;
                }
                if( long_options[option_index].name==pacangle )
                {
                    nofa.clinepacshipangle=atof( optarg );
                }

            }



            printf("\n");
            break;

        case '0':
        case '1':
        case '2':
            if (digit_optind != 0 && digit_optind != this_option_optind)
                printf("digits occur in two different argv-elements.\n");
            digit_optind = this_option_optind;
            printf("option %c\n", c);
            break;

        case 'a':
            printf("option a\n");
            break;

        case 'b':
            printf("option b\n");
            break;

        case 'c':
            printf("option c with value '%s'\n", optarg);
            break;

        case 'd':
            printf("option d with value '%s'\n", optarg);

            break;

        case '?':
            break;

        default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }


    if (optind < argc)
    {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }
    if( nofa.configfile.size()==0 )
    {
        QString hh=nofa.filespath+"oma.ini";
        nofa.configfile=hh.toStdString();
    }
    else
    {


    }
    if( QFile::exists( nofa.configfile.c_str() )  )
    {
        cout << endl << "  configfile= " << nofa.configfile << endl;
    }
    else
    {
        cout << endl << nofa.configfile << "  not found in right place " << endl;
        return -1;

    }

    QSettings setti( nofa.configfile.c_str(), QSettings::NativeFormat);


    if( nofa.scafa<0.2 )
    {
        nofa.scafa=0.2;
    }
    if( nofa.scafa>4 )
    {
        nofa.scafa=4;
    }


    QApplication app(argc, argv);
    cout << endl << " main.cpp: here might be a strange error message for some unknown reason: No protocol specified     What? Why? " << endl;

    /*    if ((QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_1_5) == 0) {
        QMessageBox::critical(0, "OpenGL features missing",
                              "OpenGL version 1.5 or higher is required to run this .\n"
                              "The program will now exit.");
        return -1;
    }

    QSurfaceFormat fmt;
      fmt.setSamples(4);
    QSurfaceFormat::setDefaultFormat(fmt);
        */
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    
    if( nofa.wwidth<0 )
    {
        nofa.wwidth=setti.value("wwidth" ).toInt();
    }
    if( nofa.wheight<0 )
    {
        nofa.wheight=setti.value("wheight").toInt();
    }
    nofa.playmedia=setti.value("playmedia" ).toString();
    nofa.pausemedia=setti.value("pausemedia" ).toString();
    nofa.skipbackmedia=setti.value("skipbackmedia" ).toString();
    if( nofa.playmedia.size()>200 or nofa.pausemedia.size()>200 or nofa.skipbackmedia.size()>200 )
    {
        cout << endl << " too long VLC control string(s) in config file " << endl;
        return -1;


    }



    KAstTopLevel topLevel( nofa );


    topLevel.setWindowTitle( setti.value("window_title").toString() );

    topLevel.show();

    app.setQuitOnLastWindowClosed(true);

    // topLevel.oukey();


    return app.exec();
}
