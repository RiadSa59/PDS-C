#!/usr/bin/env bash

# Mon programme

make

RESULTAT_DIFF="echo $?"





echo -e "\nCreation des trois fichiers (retour ligne début/milieu/les deux)\n"
touch test_rl_debut.txt test_rl_fin.txt test_rl_debut_et_fin.txt
echo -e "\n a \n b \n c \n d" > test_rl_debut.txt
echo -e "a \n b \n c \n d \n"  > test_rl_fin.txt
echo -e "\n a \n b \n c \n d \n" > test_rl_debut_et_fin.txt

echo -e "RETOUR LIGNE DEBUT\n"
echo "par défaut (10 lignes)"

tail test_rl_debut.txt > resultat_tail.txt
./mtail test_rl_debut.txt > resultat_mtail.txt
diff resultat_tail.txt resultat_mtail.txt
$RESULTAT_DIFF

echo "2 lignes"

tail test_rl_debut.txt -n 2 > resultat_tail.txt
./mtail  test_rl_debut.txt -n 2 > resultat_mtail.txt
diff resultat_tail.txt resultat_mtail.txt
$RESULTAT_DIFF


echo "1 ligne"

tail test_rl_debut.txt  -n 1 > resultat_tail.txt
./mtail  test_rl_debut.txt -n 1 > resultat_mtail.txt
diff resultat_tail.txt resultat_mtail.txt
$RESULTAT_DIFF


echo "0 ligne"

tail test_rl_debut.txt -n 0 > resultat_tail.txt
./mtail  test_rl_debut.tx -n 0 > resultat_mtail.txt
diff resultat_tail.txt resultat_mtail.txt
$RESULTAT_DIFF

echo -e "\nRETOUR LIGNE FIN\n"
echo "par défaut (10 lignes)"

tail test_rl_fin.txt > resultat_tail.txt
./mtail  test_rl_fin.txt > resultat_mtail.txt
diff resultat_tail.txt resultat_mtail.txt
$RESULTAT_DIFF


echo "2 lignes"

tail test_rl_fin.txt -n 2 > resultat_tail.txt
./mtail  test_rl_fin.txt -n 2 > resultat_mtail.txt
diff resultat_tail.txt resultat_mtail.txt
$RESULTAT_DIFF


echo "1 ligne"

tail test_rl_fin.txt  -n 1 > resultat_tail.txt
./mtail  test_rl_fin.txt -n 1 > resultat_mtail.txt
diff resultat_tail.txt resultat_mtail.txt
$RESULTAT_DIFF


echo "0 ligne"

tail test_rl_fin.txt -n 0 > resultat_tail.txt
./mtail  test_rl_fin.tx -n 0 > resultat_mtail.txt
diff resultat_tail.txt resultat_mtail.txt
$RESULTAT_DIFF


echo -e "\nRETOUR LIGNE DEBUT ET FIN\n"
echo "par défaut (10 lignes)"

tail test_rl_debut_et_fin.txt > resultat_tail.txt
./mtail  test_rl_debut_et_fin.txt > resultat_mtail.txt
diff resultat_tail.txt resultat_mtail.txt
$RESULTAT_DIFF


echo "2 lignes"

tail test_rl_debut_et_fin.txt -n 2 > resultat_tail.txt
./mtail  test_rl_debut_et_fin.txt -n 2 > resultat_mtail.txt
diff resultat_tail.txt resultat_mtail.txt
$RESULTAT_DIFF

echo "1 ligne"

tail test_rl_debut_et_fin.txt  -n 1 > resultat_tail.txt
./mtail  test_rl_debut_et_fin.txt -n 1 > resultat_mtail.txt
diff resultat_tail.txt resultat_mtail.txt
$RESULTAT_DIFF

echo "0 ligne"

tail test_rl_debut_et_fin.txt -n 0 > resultat_tail.txt
./mtail  test_rl_debut_et_fin.tx -n 0 > resultat_mtail.txt
diff resultat_tail.txt resultat_mtail.txt
$RESULTAT_DIFF

echo -e "\nSuppression des fichiers .txt de test "

rm -f *.txt

#EOF
