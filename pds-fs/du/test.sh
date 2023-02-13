#!/usr/bin/env bash

# Un test pour la commande mdu 
#
# Commandes equivalentes:
#  du -aB 512  ...     | mdu   ...
#  du -aB 512 -L ...   | mdu -L ...
#  du -ab       ...    | mdu -b ...
#  du -ab      -L ...  | mdu -bL ...
#  

# Mon programme
MDU=./mdu

# Fonction qui crée des fichiers d'une certaine taille 
function create_file(){
	dd if=/dev/zero of=$1 bs=1M count=$2
}

# Création de la première arborescence 
mkdir fs_test
mkdir fs_test/dir1
create_file fs_test/file10M.bin 10
create_file fs_test/dir1/file1M.bin 1
create_file fs_test/dir1/file5M.bin 5


# Création de la deuxième arborescence 
# Ici on rajoute des liens symboliques
mkdir fs_test_second
mkdir fs_test_second/dir2
mkdir fs_test_second/empty_directory

create_file fs_test_second/file15M.bin 15
create_file fs_test_second/dir2/file2.bin 2

ln -s ../fs_test/dir1 fs_test_second/slink
ln -s ../fs_test_second/ fs_test_second/link_rec

# Affichage des arborescences 
echo ""
echo "Les tests sont exécutés sur les arborescences suivantes"
tree fs_test
echo ""
tree fs_test_second

#BEGIN
echo "================ TEST 1 ======================"
echo ""
du -aB 512 mdu.c 
echo ""
$MDU mdu.c
echo ""
du -ab  mdu.c 
echo ""
$MDU -b mdu.c

echo ""
echo "================ TEST 2 ======================"
echo ""
du -aB 512 fs_test 
echo ""
$MDU fs_test
echo ""
du -ab fs_test 
echo ""
$MDU -b fs_test
echo ""


echo ""
echo "================ TEST 3 ======================"
echo ""
du -aB 512 fs_test_second
echo ""
$MDU fs_test_second
echo ""
du -ab fs_test_second
echo ""
$MDU -b fs_test_second
echo ""


echo ""
echo "================ TEST 4 ======================"
echo ""
du -aB 512 -L fs_test_second
echo ""
$MDU -L fs_test_second
echo ""
du -ab fs_test_second
echo ""
$MDU -b fs_test_second
echo ""
du -ab -L fs_test_second
echo ""
$MDU -bL fs_test_second
echo ""

# On éfface les dossiers
rm -rvf fs_test
rm -rvf fs_test_second

#EOF
