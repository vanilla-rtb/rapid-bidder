# rapid-bidder

Real Time Bidding (RTB) - Demand Side Platform (DSP) - Model project

Open-source model application utilizing  vanilla-rtb stack and Redis.

This is only model to show how vanilla-rtb stack can be included in your cmake project.

You are welcome to make pull requests to complete rappid-bidder with DSP specific business logic thus learning vanilla-rtb library.

Our resources are limited to maintaining  vanilla-rtb stack itself  here https://github.com/venediktov/vanilla-rtb

Even though we periodically update rapid-bidder for now it's not our main priority.

The examples how vanilla-rtb stack can be utilized are here https://github.com/venediktov/vanilla-rtb/tree/master/examples

[vanilla-rtb DSP ecosystem](https://github.com/venediktov/vanilla-rtb/wiki)

[vanilla-rtb Multi-bidder-model-with-communicator-for-Win-notifications](https://github.com/venediktov/vanilla-rtb/wiki/Multi-bidder-model-with-communicator-for-Win-notifications)

[![Join the chat at https://gitter.im/vanilla-rtb/Lobby](https://badges.gitter.im/vanilla-rtb/Lobby.svg)](https://gitter.im/vanilla-rtb/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge) 
[![build ](https://travis-ci.org/venediktov/vanilla-rtb.svg?branch=master)](https://travis-ci.org/venediktov/vanilla-rtb)

Structure ( how we see this structure for DSP ) :
* [/](../../tree/master/) -- the root directory
   * [framework/](https://github.com/venediktov/vanilla-rtb/) -- vanilla-rtb stack
   * [exchange_server/](../../tree/master/exchange_server/) -- exchange server process implementing connection to exchanges
   * [budget/](../../tree/master/budget/) -- compaign management, budget , banker
   * [bidders/](../../tree/master/bidders/) -- all kind of bidders implementation goes here
   * [loaders/](../../tree/master/loaders/) -- all cache loaders as service goes here
   * [UI/](../../tree/master/UI/) -- all admin html files and AngularJS stack go here
   * [etc/](../../tree/master/etc/) -- DSP configuration for all components of application
* [CMakeLists.txt] - cmake file

>This DSP depends on  vanilla-rtb stack which referened via gh-submodule and Redis server ( for user matching ).
>To update to the latest version of vanilla-rtb stack use the following commands \:

* git clone --recursive git@github.com:vanilla-rtb/rapid-bidder.git rapid-bidder
* git submodule update --recursive --remote
* git pull --recurse-submodules


### *(&#x1F4D7;) To build DSP suite of services use following commands in the root of dsp*

### Linux \:
- [x] mkdir Release
- [x] cd Release
- [x] cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/path/to/install .. -G "Unix Makefiles"
- [x] gmake VERBOSE=1
- [x] cd ..
- [x] mkdir Debug
- [x] cd Debug
- [x] cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/path/to/install .. -G "Unix Makefiles"
- [x] gmake VERBOSE=1

## add -DVANILLA_NO_EXAMPLES=1 if you don't want to build vanilla-rtb examples

### Windows \:
*same steps as above for linux , only difference is depending on your environment 
  either Visual Studio or NMake project can be used*
  
- [x] cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/path/to/install .. -G "NMake Makefiles"
- [x] cmake -DCMAKE_BUILD_TYPE=Debug  -DCMAKE_INSTALL_PREFIX=/path/to/install  .. -G "NMake Makefiles"
- [x] cmake -DCMAKE_BUILD_TYPE=Release  -DCMAKE_INSTALL_PREFIX=/path/to/install .. -G "Visual Studio 14 2015"
- [x] cmake -DCMAKE_BUILD_TYPE=Debug    -DCMAKE_INSTALL_PREFIX=/path/to/install .. -G "Visual Studio 14 2015"

## In case your Boost library is not installed under /usr/include/boost add where you boost library installed
to cmake coomand with -DBOOST_ROOT=/where/boost/is/installed

By default if no -DCMAKE_INSTALL_PREFIX  is passed on cmake command everyting will be installed under

```bash
rapid-bidder/Release/install
rapid-bidder/Debug/install
```

### For faster builds invoking multiple make processes  , find number of cores on your system
Linux command \: 
* nproc

4

pass it to your make script like this
```bash
gmake -j4 install
```

### Running  application as individual steps (could be all put in one rapid-bidder.sh)\:
- [x] HTTP-Bidder
  * rapid-bidder/Release/install/bin$ ./http_bidder --config etc/config.cfg
- [x] Starting multiple bidders in one swoop,  currently configured as 5 bidders in config
  * rapid-bidder/Release/install/bin$ ./multi_bidder --config etc/config.cfg
- [x] Cache loader
  * rapid-bidder/Release/install/bin$ ./cache_loader --config etc/config.cfg
- [x] Exchange Handler distributing to multi-bidders via communicator
  * rapid-bidder/Release/install/bin$ ./multi_bidder_exchange_handler --config etc/config.cfg
  
