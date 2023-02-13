#!/bin/bash
DO=./do
T=true
F=false


# do test

echo -e "========== TEST: DO ============"

echo -e "\nSANS OPTION (DISJONCTION)\n"

$DO  $F $F
$DO  $F $T
$DO  $T $F
$DO  $T $T

echo -e "\nOPTION -o (DISJONCTION\n"

$DO -o $F $F
$DO -o $F $T
$DO -o $T $F
$DO -o $T $T

echo -e  "\nOPTION -a (CONJONCTION)\n"

$DO -a $F $F
$DO -a $F $T
$DO -a $T $F
$DO -a $T $T

echo -e  "\nOPTION -c (DISJONCTION + COURT CIRCUIT)\n"

$DO -c $F $F
$DO -c $F $T
$DO -c $T $F
$DO -c $T $T

echo -e  "\nOPTION -oc (DISJONCTION + COURT CIRCUIT)\n"

$DO -oc $F $F
$DO -oc $F $T
$DO -oc $T $F
$DO -oc $T $T

echo -e  "\nOPTION -ac (CONJONCTION + COURT CIRCUIT)\n"

$DO -ac $F $F
$DO -ac $F $T
$DO -ac $T $F
$DO -ac $T $T

echo -e  "\nOPTION -ock (DISJONCTION + COURT CIRCUIT + KILL)\n"

$DO -ock $F $F
$DO -ock $F $T
$DO -ock $T $F
$DO -ock $T $T


echo -e  "\nOPTION -a -c -k (CONJONCTION + COURT CIRCUIT + KILL)"
echo -e "\n( Aussi afin de démontrer que les options peuvent être séparées\n"

echo -e "Lancement de xterm true xeyes\n"
$DO -ack "xterm" $T "xeyes"
echo -e "Lancement de xterm false xeyes\n"
$DO -ack "xterm" $F "xeyes" #Puisque 1er argument faux, xeyes est tué

echo -e  "\nOPTION -ao (ERREUR)\n"

$DO -ao $T $T

echo -e "========== FIN DES TESTS ============="
