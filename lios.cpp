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


#include"lios.h"

bool lios( QImage &tau, int x1, int y1,  int x2, int y2, QRgb hillcoloruint )
{
    bool tre=0;
    int skip=20;
    int x, y;
    double ku;
    if( x1<0 ) x1=0;
    if( y1<0 ) y1=0;
    if( x2<0 ) x2=0;
    if( y2<0 ) y2=0;
    int xr=tau.width();
    int yr=tau.height();
    if( x1>=xr-1 ) x1=xr-2;
    if( y1>=yr-1 ) y1=yr-2;
    if( x2>=xr-1 ) x2=xr-2;
    if( y2>=yr-1 ) y2=yr-2;
    ku= double( y2-y1 ) / double( x2-x1 );

    if( ku<1 and ku>-1 )
        {
            if( x2>x1 )
                {

                for( x=x1 ; x<x2 ; x+=skip )
                    {
                        y=( double( x-x1 )*ku )+y1;
                        if( y>=yr )
                            {
                                cout << "  ERROR: lios   1x " << x << " y " << y << endl;
                            }
                        if( tau.pixel( x, y )==hillcoloruint )
                        {
                            return 1;

                        }
                    }

                    for( x=x1 ; x<x2 ; x++ )
                        {
                            y=( double( x-x1 )*ku )+y1;
                            if( y>=yr )
                                {
                                    cout << "  ERROR: lios   1x " << x << " y " << y << endl;
                                }
                            if( tau.pixel( x, y )==hillcoloruint )
                            {
                                return 1;

                            }
                        }

                }
            else
                {

                for( x=x1 ; x>x2 ; x-=skip )
                    {
                        y=( double( x-x1 )*ku )+y1;
                        if( y>=yr )
                            {
                                cout << "  ERROR: lios  2x " << x << " y " << y << " y1=" << y1 << " y2= " << y2 << endl;
                            }
                        if( tau.pixel( x, y )==hillcoloruint )
                        {
                            return 1;

                        }

                    }


                    for( x=x1 ; x>x2 ; x-- )
                        {
                            y=( double( x-x1 )*ku )+y1;
                            if( y>=yr )
                                {
                                    cout << "  ERROR: lios  2x " << x << " y " << y << " y1=" << y1 << " y2= " << y2 << endl;
                                }
                            if( tau.pixel( x, y )==hillcoloruint )
                            {
                                return 1;

                            }

                        }
                }
        }
    else
        {
            ku=double( x2-x1 ) / double( y2-y1 );
            if( y2>y1 )
                {

                for( y=y1 ; y<y2 ; y+=skip )
                        {
                            x=( double( y-y1 )*ku )+x1;

                            if( y>=yr )
                                {
                                    cout << "  ERROR: lios  3x " << x << " y " << y << endl;
                                }
                            if( tau.pixel( x, y )==hillcoloruint )
                            {
                                return 1;

                            }

                        }

                for( y=y1 ; y<y2 ; y++ )
                        {
                            x=( double( y-y1 )*ku )+x1;

                            if( y>=yr )
                                {
                                    cout << "  ERROR: lios  3x " << x << " y " << y << endl;
                                }
                            if( tau.pixel( x, y )==hillcoloruint )
                            {
                                return 1;

                            }

                        }
                }
            else
                {
                for( y=y1 ; y>y2 ; y-=skip )
                    {
                        x=( double( y-y1 )*ku )+x1;
                        if( y>=yr )
                            {
                                cout << "  ERROR: lios  4x " << x << " y " << y << endl;
                            }
                        if( tau.pixel( x, y )==hillcoloruint )
                        {
                            return 1;

                        }


                    }

                    for( y=y1 ; y>y2 ; y-- )
                        {
                            x=( double( y-y1 )*ku )+x1;
                            if( y>=yr )
                                {
                                    cout << "  ERROR: lios  4x " << x << " y " << y << endl;
                                }
                            if( tau.pixel( x, y )==hillcoloruint )
                            {
                                return 1;

                            }


                        }
                }
        }


    return tre;
}
