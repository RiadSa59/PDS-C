#!/usr/bin/gnuplot

set title "Temps d'execution en dependance de la taille de buffer"
set output 'mcat_tm.png'
set term png size 1024,768
set xlabel "Ordre de la taille du buffer"
set ylabel "Temps d'execution"
plot 'mcat_tm.dat' using 1:4 title 'real' with linespoints,\
     'mcat_tm.dat' using 2:4  title 'user' with linespoints,\
     'mcat_tm.dat' using 3:4   title 'sys' with linespoints,\
