
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






#ifndef GEOME_H
#define GEOME_H
#include<QPointF>

void anglelinepac(double kulmrad, double pit, double &xtu, double &ytu );
double  distancepac( double x1, double y1, double x2, double y2 );
double qpfdistance(QPointF po1, QPointF po2 , float po1p, float po2p);
double degrad(double degreespac);
double raddeg( double rad_kulm );
double angdiffpac(double radang1, double radang2 );
double angdiffabs( double radang1, double radang2 );
double linedistpac( double x1, double y1, double x2, double y2, double px, double py, double &xvas, double &yvas );
double linedistc( double x1, double y1, double x2, double y2, double px, double py );

double rme(double  c, double k );
double katee( double x, double et );
void kda(double x1, double y1,  double x2, double y2  , double &xvas, double &yvas);
double uvas( double x1, double y1, double x2, double y2 );

void vektminus( double x1, double y1, double x2, double y2, double &xvas, double &yvas   );


#endif // GEOME_H
