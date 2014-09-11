Objectifs
=========
Realisation d'une IHM de simulation :
 -  d'oscilloscope (equation de mouvement vibratoire harmonique)
et/ou 
 - d'evolution de population de proies-prédateurs (equations de Lotka-Volterra)

Consignes
=========
1) Recuperer l'archive : 
       /home/TP/modules/sujets/CAI/TkInter/Oscillo-sujet.tgz
2) Detarer l'archive : 
       tar zxvf Oscillo-sujet.tgz  
3) renommer le repertoire  :
       mv Oscillo-sujet Dupond-Dupont-Oscilloscope 
   (pour le binome Dupond-Dupont)
4) A la fin de CHAQUE seance de labo (17:30 au plus tard), deposer une archive de version : 
      cp Dupond-Dupont-Oscilloscope.tgz /home/TP/TPrendu/nedelec/CAI/TkInter
   genere par la commande : 
      tar zcvf Dupond-Dupont-Oscilloscope.tgz Dupond-Dupont-Oscilloscope/
5) Avant de deposer l'archive, VERIFIER qu'elle n'est pas vide et qu'elle contient les bons fichiers :
     tar ztvf Dupond-Dupont-Oscilloscope.tgz
   resultat attendu :
     drwxr-xr-x dupond/dupond   0 2014-09-01 16:58 Dupond-Dupont-Oscilloscope/
     -rw-r--r-- dupond/dupond 1692 2014-09-01 16:58 Dupond-Dupont-Oscilloscope/screen.py
     -rw-r--r-- dupond/dupond 1307 2014-09-01 16:53 Dupond-Dupont-Oscilloscope/timebase.py
     -rw-r--r-- dupond/dupond  649 2014-02-18 14:16 Dupond-Dupont-Oscilloscope/proies.py
     -rwxr-xr-x dupond/dupond 1486 2014-09-01 16:37 Dupond-Dupont-Oscilloscope/oscilloscope.py
     -rw-r--r-- dupond/dupond 1863 2014-09-01 16:50 Dupond-Dupont-Oscilloscope/generator.py
6) la derniere version de l'application est a deposer pour le lundi soir a 17:30
   avant de commencer un nouveau sujet de laboratoire le lendemain.

Attention : le respect des consignes intervient dans la notation !

Premiere version
================
Affichage et contrôle d'un signal (oscilloscope.py) :
 1) creation d'une grille, parametrable, de visualisation (screen.py)
 2) calcul de la courbe d'elongation (generator.py)
 3) affichage de la courbe d'elongation (generator.py, screen.py)
 4) sliders pour parametrer le signal en frequence, amplitude, phase  (generator.py)


Deuxieme version
================
Sauvegarde du parametrage d'un signal :
 5) menu pour sauvegarder, charger des parametres de courbes
      a) dans un nom de fichier par defaut
      b) avec une boite de dialogue
 6) ajouter au menu un item pour la sortie d'application :
      - sans, puis avec boite de dialogue
Menu d'aide :
 7) Boite d'information avec Nom-Prénom, e-mail  des concepteurs de l'application
 
Quatrieme version
=================
Comparaison de signaux :
 8) gestion des signaux (X,Y, X-Y)
 9) reglage de la base de temps (timeBase.py)
 
Version finale
==============
 10) modification des composants en cas de retaillage de la fenetre
 12) visualiser les courbes dans un canevas et la courbe de lissajou dans une autre
 13) animation du spot correspondant a une elongation  (vibration.py, screen.py)

Reutilisation
=============
 14) Reprendre la même IHM avec un autre modele de calcul (equations de Lotka-Volterra et/ou mouvement vibratoire harmonique)
