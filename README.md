NestRTD
=======

**C++ RTD client for Nest. Feeds Amibroker.  
Also included is a backfill tool to import VWAP statistics / Nest Plus Data table.**  

  * The tools are based on RTNOW utility by josh1. Read its instructions if needed ( Excel instructions irrelevant ).
    See [RTNOW](http://www.traderji.com/intraday/82733-free-realtime-data-now-nest-odin-trade-tiger-google-yahoo-amibroker-fcharts-ms.html)  
  * Advantages vs RTNOW  
    - No need to use excel  
    - More accurate data as we pick up every callback from RTD  
    - Uses less resources as its native binary  
  * Disadvantages  
    - Only tested with NEST (ZT). May also work with NOW ( change RTDServerProgID value to Now.ScripRTD )  
    - No GUI. Create one if you can and share under GPLv3. Only need to setup some files and run exe anyway  

#### Instructions        
    1. Setup Amibroker DB (intraday settings) and Nest as explained in josh1 RTNOW instructions.
    2. Copy rtd.format, backfill.format to AmiBroker\Formats.
    3. Read and Setup settings.ini in NestRTD / ABBackFill	    
    4. Once setup is done, run the exe ( For Backfill, Fill the data in VWAP.txt/DataTable.txt first )

#### Build
    Build using VC++ 2010 Express. ATL headers and libs taken from Windows Driver kit.

#### Source (GPL v3)
    https://github.com/SpiffSpaceman/AmibrokerFeeder

#### License
    Copyright (C) 2014  SpiffSpaceman

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
