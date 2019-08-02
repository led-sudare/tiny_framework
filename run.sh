#! /bin/bash

cd `dirname $0`

ruby start_stop_server.rb &

./tiny_framework 192.168.11.20:5510 1234
