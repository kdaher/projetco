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

package projetco.simulations;

import projetco.Source;
import projetco.Sink;

//
// Sample network, consisting of a source and a sink.
//
network SourceSink
{
    @display("bgb=931,663;bgl=2");
    submodules:


        sink[1]: Sink {
         //   @display("p=548,328");
        }


        source[9]: Source {


           // @display("p=,,,50,50");
        }
    connections:


        source[0].out2++ --> source[4].in2++;
         source[0].in2++ <-- source[1].out2++;
        source[0].out2++ --> sink[0].in2++;//sink
         source[1].in2++ <-- source[2].out2++;
        source[1].out2++ --> source[0].in2++;
         source[1].in2++ <-- source[7].out2++;
        source[1].out2++ --> source[4].in2++;
       //  source[1].in2++ <-- source[3].out2++;
        source[1].out2++ --> sink[0].in2++;//sink
       //  source[1].in2++ <-- source[4].out2++;
        //source[1].out2++ --> source[5].in2++;
        // source[1].in2++ <-- source[5].out2++;
        //source[2].out2++ --> source[6].in2++;
       //  source[2].in2++ <-- source[6].out2++;
        source[2].out2++ --> source[1].in2++;
        // source[2].in2++ <-- source[7].out2++;
        source[2].out2++ --> source[7].in2++;
        // source[2].in2++ <-- source[4].out2++;
        source[3].out2++ --> source[4].in2++;
       source[3].in2++ <-- source[5].out2++;
        source[3].in2++ <-- source[6].out2++;
        source[3].in2++ <-- source[8].out2++;
        //source[3].out2++ --> source[6].in2++;
       //  source[3].in2++ <-- source[6].out2++;
        //source[3].out2++ --> source[7].in2++;
       //  source[3].in2++ <-- source[7].out2++;
        source[4].out2++ --> sink[0].in2++;//sink
        source[4].in2++ <-- source[0].out2++;
        //source[4].out2++ --> source[8].in2++;
         source[4].in2++ <-- source[1].out2++;
         source[4].in2++ <-- source[3].out2++;
       // source[4].out2++ --> sink[0].in2++;
        source[5].out2++ --> source[3].in2++;
        // source[5].in2++ <-- source[7].out2++;
        source[5].out2++ --> source[6].in2++;
        source[5].out2++ --> source[8].in2++;
       //  source[5].in2++ <-- source[8].out2++;
        source[6].out2++ --> source[3].in2++;
        source[6].in2++ <-- source[5].out2++;
        source[6].in2++ <-- source[8].out2++;
        source[7].out2++ --> source[1].in2++;
        source[7].in2++ <-- source[2].out2++;
        source[8].out2++ --> source[3].in2++;
        source[8].out2++ --> source[6].in2++;
        source[8].in2++ <-- source[5].out2++;
       // sink[0].in2++ <-- source[0].out2++;
       // sink[0].in2++ <-- source[1].out2++;
        //sink[0].in2++ <-- source[4].out2++;
        
        	source[0].out++ --> source[4].in++;
         source[4].out++ --> source[0].in++;
       // source[0].out++ --> source[4].in++;
        source[0].out++ --> source[1].in++;
         source[1].out++ --> source[0].in++;
         //source[1].in++ <-- source[3].out++;
        source[1].out++ --> source[2].in++;
         source[2].out++ --> source[1].in++;
        source[1].out++ --> source[4].in++;
         source[4].out++ --> source[1].in++;
        source[1].out++ --> source[7].in++;
         source[7].out++ --> source[1].in++;
        source[2].out++ --> source[1].in++;
         source[1].out++ --> source[2].in++;
        source[2].out++ --> source[7].in++;
         source[7].out++ --> source[2].in++;
        source[3].out++ --> source[4].in++;
         source[4].out++ --> source[3].in++;
        source[3].out++ --> source[5].in++;
         source[5].out++ --> source[3].in++;
         
        source[3].out++ --> source[6].in++;
        source[6].out++ --> source[3].in++;
        source[3].out++ --> source[8].in++;
        source[8].out++ --> source[3].in++;
        source[5].out++ --> source[6].in++;
        source[6].out++ --> source[5].in++;
        source[5].out++ --> source[8].in++;
        source[8].out++ --> source[5].in++;
        source[6].out++ --> source[8].in++;
        source[8].out++ --> source[6].in++;
        source[4].out++ --> sink[0].in++;
        sink[0].out++ --> source[4].in++;
        source[1].out++ --> source[5].in++;
        source[5].out++ --> source[1].in++;
        source[0].out++ --> source[5].in++;
        source[5].out++ --> source[0].in++;
        
        //source[5].out++ --> source[6].in++;
        //source[4].out++ --> source[6].in++;
        
         //source[3].in++ <-- source[6].out++;
        //source[3].out++ --> source[7].in++;
         //source[3].in++ <-- source[7].out++;
        //source[4].out++ --> source[5].in++;
         //source[4].in++ <-- source[5].out++;
        //source[4].out++ --> source[8].in++;
         //source[4].in++ <-- source[8].out++;
       // source[4].out++ --> sink[0].in++;
       // source[4].in++ <-- sink[0].out++;
        //source[5].out++ --> source[7].in++;
         //source[5].in++ <-- source[7].out++;
        //source[5].out++ --> source[8].in++;
         //source[5].in++ <-- source[8].out++;
        //source[6].out++ --> sink[0].in++;
       // source[6].in++ <-- sink[0].out++;
      //  source[7].out++ --> sink[0].in++;
        //source[7].out++ --> source[8].in++;
         //source[7].in++ <-- source[8].out++;
       //source[8].out++ --> sink[0].in++;












}
