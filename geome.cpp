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


#include<cmath>
#include<iostream>
#include"geome.h"

using namespace std;

void anglelinepac( double kulmrad, double pit, double &xtu, double &ytu )
{


    xtu= ( cos( kulmrad )*pit );
    ytu= ( sin( kulmrad )*pit );
}
double  distancepac( double x1, double y1, double x2, double y2 )
{
    return sqrt( ( ( x1-x2 ) * ( x1-x2 ) )  + ( ( y1-y2 ) * ( y1-y2 ) ) );
}

double qpfdistance( QPointF po1, QPointF po2, float po1p, float po2p )
{
 return distancepac( po1.x()+po1p, po1.y()+po1p, po2.x()+po2p, po2.y()+po2p   ) ;

}


double degrad( double degreespac )
{
    double rad_kulm;
    rad_kulm=( degreespac*M_PI )/180.0;
    return rad_kulm;
}
double raddeg( double rad_kulm )
{
    double asteet;
    asteet=( rad_kulm /M_PI )*180.0;


    return asteet;
}

double angdiffpac( double radang1, double radang2 )
{
    double t1, t2, t3, radt;

    t1=radang1-radang2;
    t2=t1-( 2*M_PI );
    t3=t1+( 2*M_PI );
    if( abs( t2 )< abs( t3 ) ) radt=t2;
    else radt=t3;
    if( abs( t1 )<abs( radt ) ) radt=t1;

    return  radt ;
//    return rd( t );

}

double angdiffabs(double radang1, double radang2 )
{
    double t1, t2, t3, radt;

    t1=radang1-radang2;
    t2=t1-( 2*M_PI );
    t3=t1+( 2*M_PI );
    if( abs( t2 )< abs( t3 ) ) radt=t2;
    else radt=t3;
    if( abs( t1 )<abs( radt ) ) radt=t1;

    return  fabs( radt );


}


double linedistpac( double x1, double y1, double x2, double y2, double px, double py, double &xvas, double &yvas )
{
    double ku= double( y2-y1 ) / double( x2-x1 );

    double ku2=-1.0/ku;

    double x=0, y=0, et=0;


    if( x1!=x2 and y1!=y2 )
        {
            x = ( ( -1.0*ku2*double( px ) ) +double( py )+( -1.0*double( y1 ) ) + ku*double( x1 ) ) / ( ku -  ku2 );

            y=( double( x-x1 )*ku )+y1;
            et=sqrt( ( ( x-px )*( x-px ) ) + ( ( y-py ) * ( y-py ) ) );
        }
    else
        {
            if( x1==x2 )
                {
                    et=abs( x1-px );
                    x=x1;
                    y=py;
                }
            if( y1==y2 )
                {
                    et=abs( y1-py );
                    x=px;
                    y=y1;
                }
            if( x1==x2 and y1==y2 )
                {
                    et=0;
                    x=px;
                    y=py;
                }
        }

xvas=x;
yvas=y;

    return et;
}
double linedistc( double x1, double y1, double x2, double y2, double px, double py )
{
    double vas, th, th2;
    vas=linedistpac( x1, y1, x2, y2, px, py, th, th2  );
    return vas;

       }




double rme( double c, double k )
{
    double tul;

    tul = sqrt( ( c*c ) / ( ( k*k )+1 ) );

    if( k>0 )
    {
        return tul;
    }
    else
    {
        return tul*-1;
    }


}

double katee( double x, double et )
{
    double kat;
    kat=sqrt( ( et*et )- ( x * x ) );

    return kat;
}

void kda( double x1, double y1,  double x2, double y2, double &xvas, double &yvas  )
{
    double  xx, yy, cc;
cc=distancepac( 0, 0, x2, y2  );
   xx=rme( cc, y1/x1   );
yy=katee( xx, cc );

xvas=xx;
yvas=yy;


    //return tul;
}

double uvas( double x1, double y1, double x2, double y2 )
{
    double xvas, yvas, vt, tul, cc;
    kda( x1, y1, x2, y2, xvas, yvas  );
    vt=linedistc( 0, 0, x2, y2, xvas, yvas  );
    cc=distancepac( 0, 0, x2, y2  );

    tul=katee( vt, cc  );

    return tul;
}



/*------------------------*/

void vektminus( double x1, double y1, double x2, double y2, double &xvas, double &yvas   )
{
   xvas=x1-x2;
   yvas=y1-y2;

}
