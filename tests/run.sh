#!/bin/bash

../build/bin/loop-convert $1 > __x.c
rm __$1

../build/bin/hoist __x.c > __$1
rm __x.c
