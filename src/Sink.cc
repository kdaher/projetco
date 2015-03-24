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
    count1=0;
    nb=0;
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
{
    int in2 =gateSize("in");
    int kd= msg->getKind();
if (kd == 0){
  count1++;
}
    cMessage *ack = new cMessage("iteration");
    ack->setKind(0);
    int o1= gateSize("out");
    cMessage *keep= new cMessage("keep_data");
    keep->setKind(1);
    Source *src=new Source();
    if (count1==in2){
        count1=0;
    src->fwl(nb+1);
    clock_t t1,t2;
    t1=clock();
    src->calculSink();
    src->enregistrer(nb);
    t2=clock();
    simtime_t d = simTime() - lastArrival;

    //EV << "Received " << msg->getName() << endl;
    delete msg;
    iaTimeHistogram.collect(d);
    arrivalsVector.record(1);

    lastArrival = simTime();
    //ev<<"la difference est"<<src->fabst<<endl;
    if (nb<4000 ){
       // ev<<"Incremente les iterations"<<endl;
        for(int i=0;i<o1;i++){
            send(ack->dup(),"out",i);

              }

        //ev<<"nbs iterations : "<<nb<<endl;
                }

    else{
        ev<<d<<endl;
        src->afficherqi();
        ev<<"arrete les iterations, envoie keep_iteration "<<endl;
        ev<<"nbs iterations : "<<nb<<endl;
        endSimulation ();
                }
    nb++;}
    else {for(int i=0;i<o1;i++){
        send(ack->dup(),"out",i);
          }}

}

void Sink::finish()
{
    recordStatistic(&iaTimeHistogram);
}

}; // namespace
