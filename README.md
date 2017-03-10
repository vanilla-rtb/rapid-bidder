# rapid-dsp

Real Time Bidding (RTB) - Demand Side Platform (DSP)

open-source application utilizing  vanilla-rtb stack.

What differs us from other open-source libraries like RTBkit: our stack is small, easy to adapt to and  completely decoupled.


[our DSP ecosystem](../../wiki)

[Multi-bidder-model-with-communicator-for-Win-notifications](../../wiki/Multi-bidder-model-with-communicator-for-Win-Loss-notifications)

[![Join the chat at https://gitter.im/vanilla-rtb/Lobby](https://badges.gitter.im/vanilla-rtb/Lobby.svg)](https://gitter.im/vanilla-rtb/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge) 
[![build ](https://travis-ci.org/venediktov/vanilla-rtb.svg?branch=master)](https://travis-ci.org/venediktov/vanilla-rtb)

Structure ( how we see this structure for DSP ) :
* [/](../../tree/master/) -- the root directory
   * [framework/](../../tree/master/framework/) -- vanilla-rtb stack
   * [exchange_server/](../../tree/master/exchange_server/) -- exchange server process implementing connection to exchanges
   * [campaign_manager/](../../tree/master/campaign_manager/) -- compaign management service collaborates with bidders
   * [bidders/](../../tree/master/bidder_service/) -- all kind of bidders implementation goes here
   * [loaders/](../../tree/master/loader_service/) -- all cache loaders as service goes here
   * [etc/](../../tree/master/etc/) -- DSP configuration for all components of application
* [CMakeLists.txt] - cmake file

>This DSP depends on  vanilla-rtb stack which referened via gh-submodule.
>To update to the latest version of vanilla-rtb stack use the following commands \:

* git submodule foreach git pull


###*(&#x1F4D7;) To build DSP suite of services use following commands in the root of dsp*

###Linux \:
- [x] mkdir Release
- [x] cd Release
- [x] cmake -DCMAKE_BUILD_TYPE=Release .. -G "Unix Makefiles"
- [x] gmake VERBOSE=1
- [x] cd ..
- [x] mkdir Debug
- [x] cd Debug
- [x] cmake -DCMAKE_BUILD_TYPE=Debug .. -G "Unix Makefiles"
- [x] gmake VERBOSE=1

###Windows \:
*same steps as above for linux , only difference is depending on your environment 
  either Visual Studio or NMake project can be used*
  
- [x] cmake -DCMAKE_BUILD_TYPE=Release .. -G "NMake Makefiles"
- [x] cmake -DCMAKE_BUILD_TYPE=Debug   .. -G "NMake Makefiles"
- [x] cmake -DCMAKE_BUILD_TYPE=Release .. -G "Visual Studio 14 2015"
- [x] cmake -DCMAKE_BUILD_TYPE=Debug   .. -G "Visual Studio 14 2015"


###For faster builds invoking multiple make processes  , find number of cores on your system
Linux command \: 
* nproc

4

pass it to your make script like this
gmake -j4 install

###Running  application as individaul steps (could be all put in one dsp.sh)\:
- [x] HTTP-Bidder
  * dsp/bin/bidder$ ./http_bidder --config etc/config.cfg
- [x] Starting multiple bidders in one swoop,  currently configured as 5 bidders in config
  * dsp/bin/bidders$ ./multi_bidder --config etc/config.cfg
- [x] Cache loader
  * dsp/bin/loader$ ./cache_loader --config etc/config.cfg
- [x] Exchange Handler with HTTP handler or Exchange Handler distributing to multi-bidders via communicator 
  * dsp/bin/exchange$ ./exchange_handler --config etc/config.cfg
