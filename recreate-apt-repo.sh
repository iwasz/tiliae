#!/bin/bash

TEMP_DIR="/tmp/recreate-apt-repo"

if [ -d $TEMP_DIR ]
then
	rm -Rf $TEMP_DIR
fi

mkdir -p $TEMP_DIR
cd $TEMP_DIR

scp -r iwasz@iwasz.pl:/home/iwasz/domains/iwasz.pl/public_html/deb ./
cd deb
apt-ftparchive packages . > Packages
bzip2 -kf Packages
apt-ftparchive release . > Release
gpg --yes -abs -u 9EDE3F68 -o Release.gpg Release
scp Packages* Release* iwasz@iwasz.pl:/home/iwasz/domains/iwasz.pl/public_html/deb/

cd -
