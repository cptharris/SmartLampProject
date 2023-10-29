# SmartLampProject

### A Guided Project with UCSB IEEE

Started by getting the LED strip set up and working nicely

Fixed the range finder code so that LEDs only come on when rangefinder is activated

Error! once range finder reads less than 100 cm, the light scene goes through whatever it wants to do, but rangefinder is NOT BEING READ. it has to wait for the LED scene to complete. how to fix this?

I need some way to separate the rangefinder code and the LED code. They both need to run concurrently and the LED code needs to turn off the LEDs when the rangefinder code says so.

I incorporated the rangefinder check into the LED code. Every time the LED code moves to the next pixel, the rangefinder is queried and the light strip only turns on if the rangefinder is activated.
