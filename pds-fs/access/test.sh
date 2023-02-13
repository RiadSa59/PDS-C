#!/usr/bin/env bash

LONG_NAME=$(for ((i=1; i<=257; i++));do printf "%s" "a";done;printf "\n")

#BEGIN
mkdir dossier_test
touch dossier_test/file

# TEST OK
./maccess -rwxv dossier_test
./maccess -rwxv dossier_test/file


# EACCES
chmod -r dossier_test/file
./maccess -rv dossier_test/file

chmod +r dossier_test/file
chmod -r dossier_test
./maccess -rv dossier_test/file

chmod +r dossier_test

chmod -x dossier_test/file 
./maccess -xv dossier_test/file

chmod +x dossier_test/file
chmod -x dossier_test 
./maccess -xv dossier_test/file

chmod -R +xrw dossier_test

# ELOOP 
ln -s dossier_test/link dossier_test/link 
./maccess -rv link

#ENAMETOOLONG
./maccess -wv $LONG_NAME 
#ENOENT
ln -s dossier_test/file2 dossier_test/link2 #file2 n'existe pas 
./maccess -rv link2

#ENOTDIR
./maccess -rv dossier_test/file/file2

rm -rvf dossier_test
#EOF
