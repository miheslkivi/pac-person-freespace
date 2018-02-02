/*
*
*  Pac-person freespace continuum undiscreted ( PPFCU or p-pf-scu-d ) - Copyright (C) 2018 by
*
*
*** You may use this file under the terms of the BSD license as follows:
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
    **   * The names of its contributors may not be used to endorse or promote
    **     products derived from this software without specific prior written
    **     permission.
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
    **
    **
    ****************************************************************************/



#include<sstream>
#include<QString>
#include<QFont>
#include<QPainter>
#include<QPoint>
#include<iostream>
#include<string>
using namespace std;

const char *hudm( const char *parn, double arv  )
{
    string tth=parn;
    string sparn, sar;
    stringstream ssparn;
    ssparn << arv;
ssparn >> sar;
sparn+=tth;
    sparn+=" ";
    sparn+=sar;

    return sparn.c_str() ;
}

QString hudmqs( const char *parn, double arv  )
{
QString tth=parn;
    QString sparn;
string      sar;
    stringstream ssparn;
    ssparn << arv;
ssparn >> sar;
sparn+=tth;
    sparn+=" ";
    sparn+=sar.c_str();

    return sparn ;
}

QString hudmqsbool( const char *parn, int arv  )
{
QString tth=parn;
    QString sparn;
string      sar;
    stringstream ssparn;
    if( arv==0 )
    {
        sar="off";

    }
    if( arv>=1 )
    {
        sar="on";

    }
    ssparn << arv;


sparn+=tth;
    sparn+=" ";
    sparn+=sar.c_str();


    return sparn ;
}


void hudbool( QString mes, char offoron, QPainter *mespainter, QString bfontname, QPoint pla  )
{
    QFont offont(bfontname, 17, 25 );
    QFont bon(bfontname , 20,  81 );
    if( offoron>=1 )
    {
        mespainter->setFont( bon );
     //   mespainter->drawText( pla, hudmqsbool( mes.toAscii(), offoron  ) );
           mespainter->drawText( pla, hudmqsbool( mes.toLatin1(), offoron  ) );

    }
    else
    {
        mespainter->setFont( offont );
     //   mespainter->drawText( pla, hudmqsbool( mes.toAscii(), offoron  ) );
        mespainter->drawText( pla, hudmqsbool( mes.toLatin1(), offoron  ) );

    }

}
int boolt( int baa )
{
   if( baa!=1 )
   {
    return 0;
   }
   else
   {
       return 1;

   }
}
