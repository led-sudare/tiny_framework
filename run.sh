#! /bin/bash

cd `dirname $0`

cd ./startstop
ruby app.rb &

cd ../
./tiny_framework 192.168.11.20:5510 1234
