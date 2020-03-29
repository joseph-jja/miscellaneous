#! /bin/sh

echo "#define NODE_JS \"`which node`\"" > whichnodejs.h
echo "#define WEATHER_MAP \"`pwd`/weather-api.js\"" >> whichnodejs.h
echo "#define OPEN_WEATHER_MAP \"`pwd`/ow-weather-api.js\"" >> whichnodejs.h


