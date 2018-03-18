
/*
*
*  Pac-person freespace continuum undiscreted ( PPFCU or p-pf-scu-d ) - Copyright (C) 2018 by Mikko Heiska
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


#include<QLine>

#include<QRect>
#include<QColor>
#include<string>
#include<QString>
#include<iostream>

#include<sstream>
#include<QString>
#include<QFont>
#include<QPainter>
#include<QPoint>
#include<QPixmap>
using namespace std;


void flipb( bool &var )
{
    if( var)
        var=0;
    else
        var=1;


}
bool flb( bool var )
{
    if( var)
        return 0;
    else
        return 1;

}

void flipchar( char &varch )
{

    if( varch==1 )
    {
        varch=0;
    }
    else
    {
        if( varch==0 )
        {
            varch=1;
        }

    }


}


void switchchar( char &var, int cou )
{

    var++;

    if(var>=cou )
    {
        var=0;
    }

}

void limsetb(double &vaa, string sname  , bool showr)
{
    if( vaa>254 )
    {
        if(showr )
        {
            cout << endl << " limsetb: " << sname << " vaa=" << vaa << endl;
        }
        vaa=254;
    }
    if( vaa<0 )
    {
        if(showr )
        {
            cout << endl << " limsetb: " << sname << " vaa=" << vaa << endl;
        }
        vaa=0;

    }

}
void limsetc(double &vaa, double lim, string sname  , bool showr)
{
    if( vaa>lim )
    {
        if(showr )   cout << endl << " limsetc: " << sname << " vaa=" << vaa << endl;
        vaa=lim;
    }
    if( vaa<0 )
    {
        if(showr )   cout << endl << " limsetc: " << sname << " vaa=" << vaa << endl;
        vaa=0;

    }

}


double prec( double val, double pre )
{
    double aa;
    int ival;

    ival=val/pre;

    aa=ival*pre;

    return aa;
}

void coubo( const char* name, bool val )
{
    if( val )
    {
        cout << endl << name << "=on" << endl << endl;

    }
    else
    {
        cout << endl << name << "=off" << endl << endl;

    }

}
void tograyscale( QPixmap* qpxm  )
{
    int  itey, itex;

    QImage ima=qpxm->toImage();
    QImage imags=ima;


    //imags=ima.convertToFormat( QImage::Format_Indexed8, colv /*, Qt::MonoOnly */ ) ;

    int val;
    for( itey=0 ; itey<ima.height() ; itey++  )
    {
        for( itex=0 ; itex<ima.width() ; itex++  )
        {
            val=( qRed( ima.pixel( itex, itey  ) )+ qGreen( ima.pixel( itex, itey  ) )+
                  qBlue( ima.pixel( itex, itey  ) ) )/3;
            imags.setPixel( itex, itey, qRgb( val, val , val  ) );

        }

    }


    qpxm->convertFromImage( imags );



}


void pathandfile( QString path, string &file )
{
    string res=path.toStdString()+file;
    file=res;
}

float randf( float lim )
{

    if( lim==0 )
    {
        cout << endl << " randf: ERROR:  0 " << endl;
        exit(-1);
    }
    return ( random()%int( lim*12000 ) )/12000;
}

