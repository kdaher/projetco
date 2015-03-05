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

#include "Sink.h"
#include "Source.h"

namespace projetco {

Define_Module(Sink);
Define_Module(Source);

void Sink::initialize()
{

    cMessage *msg = new cMessage("Iteration");
msg->setKind(0);
    // int out2=gateSize("out2");
     int out =gateSize("out");
     ev<<"out="<<out<<endl;

   for(int i=0;i<out;i++){
         send (msg->dup(),"out",i);}
    lastArrival = simTime();
    iaTimeHistogram.setName("interarrival times");
    arrivalsVector.setName("arrivals");
    arrivalsVector.setInterpolationMode(cOutVector::NONE);
}

void Sink::handleMessage(cMessage *msg)
{//count=0;
    Source *src=new Source();
    src->fwl();
    cMessage *ack = new cMessage("iteration");
    ack->setKind(0);
    simtime_t d = simTime() - lastArrival;
    EV << "Received " << msg->getName() << endl;
    delete msg;

    iaTimeHistogram.collect(d);
    arrivalsVector.record(1);

    lastArrival = simTime();
   // void Source::fwl();
  //  void Source::
   /* int kd= msg->getKind();
        if (kd == 1){
                                        count++;
                          }

                          ev<<"test count"<<endl;
                          ev<<"count="<<count<<endl;


                          if (count==gateSize("in")){

                              for(int i=0;i<gateSize("out");i++){
                              send(ack->dup(),"out",i);}
                              count=0;
                          }*/
    for(int i=0;i<gateSize("out");i++){
                                 send(ack->dup(),"out",i);}



}

void Sink::finish()
{
    recordStatistic(&iaTimeHistogram);
}

}; // namespace
