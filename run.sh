#!/bin/bash

bin/loop-convert $1 > x.c
rm __$1
bin/hoist x.c > __$1
rm x.c
