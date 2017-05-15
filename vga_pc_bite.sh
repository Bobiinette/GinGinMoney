#!/bin/bash

xrandr --newmode "1024x768-safe" 60.00 1024 1048 1184 1344 768 771 777 806 -HSync -VSync
xrandr --addmode DP2 1024x768-safe
xrandr --output DP2 --mode 1024x768-safe