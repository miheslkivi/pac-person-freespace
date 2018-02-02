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


#ifndef PACINIT_H
#define PACINIT_H
#include<sstream>
#include<QString>
#include<QFont>
#include<QPainter>
#include<QPoint>
#include<iostream>
#include<string>
#include"sprites.h"
#include"gmu.h"
using namespace std;

int pacinith( QList<marj*>  &marlis, QList<boxc*>  &boxclis,  QList<ener*>  &enelis,
              gsett &jgsi, gsvar &jgv ,  QImage &backim_, QGraphicsScene &fieldtt_   )
{
   int ite, ite2;
float xeh, yeh;
   marj *jmarj_;
   boxc *jbox;
   ener *jene;
   QPixmap marjpng( jgsi.marjpicn.c_str()  );
   QPixmap boxcratepng( jgsi.boxcratepicn.c_str() );
   QPixmap enerpng( jgsi.enerpicn.c_str() );

jgsi.berhawidth= marjpng.width()/2;
   jgsi.boxhawidth=boxcratepng.width()/2;
    jgsi.enehawidth=enerpng.width()/2;

   QList<QPixmap> ptau_, bctau_, enetau_;

   ptau_.push_back( marjpng );
   bctau_.push_back( boxcratepng  );
   enetau_.push_back( enerpng );

   int rantv;
   ite=jgv.ber;

   for( ite=0 ; ite<jgsi.iniloop  ; ite++ )

   {

       xeh=( random()%( backim_.width() -200 ) )+100;
       yeh=( random()%( backim_.height()-200 ) )+100 ;

       bool hhh=1;
       if(   backim_.pixel( xeh+20, yeh+20 )==jgsi.meadowc.rgb() )
       {
           rantv= random()%10;
           if( rantv>1 )
           {

               for( ite2=0; ite2< marlis.size() ; ite2++ )
               {
                   if( distancepac( xeh, yeh,  marlis.at( ite2 )->x(), marlis.at( ite2 )->y()  ) <  jgsi .mardis  )
                   {
                       hhh=0;
                       break;
                   }
               }

               for( ite2=0; ite2< boxclis.size() ; ite2++ )
               {
                   if( distancepac( xeh, yeh,  boxclis.at( ite2 )->x(), boxclis.at( ite2 )->y()  ) <  jgsi .marboxdis  )
                   {
                       hhh=0;
                       break;
                   }
               }
               for( ite2=0; ite2< enelis.size() ; ite2++ )
               {
                   if( distancepac( xeh, yeh,  enelis.at( ite2 )->x(), enelis.at( ite2 )->y()  ) <   jgsi .marenedis )
                   {
                       hhh=0;
                       break;
                   }
               }


               if(hhh)
               {
                   jmarj_=new marj( ptau_, &fieldtt_ ) ;
                   jmarj_->setPos( xeh ,  yeh );
                   marlis.append( jmarj_ );
               }
           }
           if( rantv==0)
           {

               for( ite2=0; ite2< boxclis.size() ; ite2++ )
               {
                   if( distancepac( xeh, yeh,  boxclis.at( ite2 )->x(), boxclis.at( ite2 )->y()  ) <  jgsi.boxdis  )
                   {
                       hhh=0;
                       break;
                   }
               }
               for( ite2=0; ite2< marlis.size() ; ite2++ )
               {
                   if( distancepac( xeh, yeh,  marlis.at( ite2 )->x(), marlis.at( ite2 )->y()  ) <  jgsi.marboxdis  )
                   {
                       hhh=0;
                       break;
                   }
               }

               for( ite2=0; ite2< enelis.size() ; ite2++ )
               {
                   if( distancepac( xeh, yeh,  enelis.at( ite2 )->x(), enelis.at( ite2 )->y()  ) <  jgsi.boxenedis  )
                   {
                       hhh=0;
                       break;
                   }
               }

               if( hhh )
               {
                   jbox=new boxc( bctau_,  &fieldtt_ );
                   jbox->setPos( xeh ,  yeh );
                   boxclis.append( jbox );

               }
           }
           if( rantv==1)
           {

               for( ite2=0; ite2< enelis.size() ; ite2++ )
               {
                   if( distancepac( xeh, yeh,  enelis.at( ite2 )->x(), enelis.at( ite2 )->y()  ) <  jgsi.enedis  )
                   {
                       hhh=0;
                       break;
                   }
               }
               for( ite2=0; ite2< boxclis.size() ; ite2++ )
               {
                   if( distancepac( xeh, yeh,  boxclis.at( ite2 )->x(), boxclis.at( ite2 )->y()  ) <  jgsi.boxenedis  )
                   {
                       hhh=0;
                       break;
                   }
               }
               for( ite2=0; ite2< marlis.size() ; ite2++ )
               {
                   if( distancepac( xeh, yeh,  marlis.at( ite2 )->x(), marlis.at( ite2 )->y()  ) <  jgsi.marenedis  )
                   {
                       hhh=0;
                       break;
                   }
               }


               if( hhh )
               {
                   jene=new ener( enetau_,  &fieldtt_ );
                   jene->setPos( xeh ,  yeh );
                   enelis.append( jene );


               }

           }







       }

   }




cout << endl << " berries " << marlis.size() << " ener fuel " << enelis.size() << "  box " << boxclis.size() << endl;

return 1;
}


#endif // PACINIT_H
