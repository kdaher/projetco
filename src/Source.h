//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __PROJETCO_SOURCE_H
#define __PROJETCO_SOURCE_H

#include <omnetpp.h>

namespace projetco {

/**
 * Generates messages; see NED file for more info.
 */

class Source : public cSimpleModule
{
  private:
    cMessage *timerMessage;

  public:
     Source();
     virtual ~Source();
int count;
int k;
 virtual void fwl();
 virtual void calculSink();
/*double sumf;
double sxhl;
double sqi;
double spsh;
double srh;
double old;
double fabst;*/
double fabst;

  protected:
     virtual double ethac (int h,int i ,double rh[]);
     //virtual double wij (int isrc,int ides);
     virtual void flamda (int id);
     // virtual void fwl (int id,int rid);

     virtual void fvh (int id);
     virtual void fuhi (int id);
     virtual void fqi (int id);
     virtual void fpsh (int id);
     virtual void frh (int id);
     virtual void fxhl (int id);


     virtual double dis(int l);
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

}; // namespace

#endif
