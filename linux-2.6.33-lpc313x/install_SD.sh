#!/bin/bash

make zImage && make modules && make modules_install INSTALL_MOD_PATH=/media/258ab758-e063-41ba-b6aa-50ba495deea4 && cp arch/arm/boot/zImage /media/258ab758-e063-41ba-b6aa-50ba495deea4/
