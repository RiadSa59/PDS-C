#!/usr/bin/env bash 

# Mon programme
MCAT=./mcat-scd
TIME_CMD=/usr/bin/time
TIME_OPT="-f %e %U %S"
TIME_FILE=mcat_tm.dat

# Fonction qui crée des fichiers d'une certaine taille 
function create_file (){
	dd if=/dev/urandom of=$1 bs=1M count=$2 
}



# Création de l'arborescence de test
export MCAT_BUFSIZ=1024 
mkdir fs_test
create_file "fs_test/file5.bin" 5 
create_file "fs_test/file1G.bin" 1000 

# Test du programme
$MCAT fs_test/file5.bin > fs_test/file5
$MCAT fs_test/file1G.bin > fs_test/file1G
diff fs_test/file5.bin fs_test/file5 && echo "TEST1: OK"
diff fs_test/file1G.bin fs_test/file1G && echo "TEST2: OK"


# initialisation du fichier de stockage
echo '# real user sys log(size)' > $TIME_FILE
# on teste le programme avec plusieurs tailles de buffer
power_count=0;
for size in `awk 'BEGIN{ for(i=1; i<=8388608; i*=2 ) print i }'`; do
	export MCAT_BUFSIZ=$size
	$TIME_CMD "$TIME_OPT $power_count" $MCAT fs_test/file1G.bin > /dev/null 2>> $TIME_FILE
	power_count=$(($power_count + 1))
done




#EOF
