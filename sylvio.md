# Suivi des tâches 

## 0. Configuration du projet (en feat avec Evan)

**CONTEXTE** <br /><br />
On souhaitait mettre en place un environnement de développement qui soit facilement a utilisé une fois mis en place. Avec une installations des dépendances rapide et fiable. <br />
On a donc opté pour Conan afin d'installer les dépendances, et CMake pour build le projet. Ensuite on a essayer d'exploiter le projet template donné pour le SFML.

**PROBLEME** <br /><br />
Pour nous aider à configurer le projet avec Conan et CMake on a utilisé nos différents cours où on avait déjà mis en pratique ces outils.
On a reussi a exploité Conan et CMake pour la configuration du projet, mais lors de l'utilisation de l'IDE Rider, on a rencontré de nombreux problèmes.
L'IDE voulait compiler un CMake avec le compilateur gcc, tandis que les commandes conan qu'on avait faite, utilisais msvc comme compilateur.
Ensuite, nous avons dû faire le squelette minimal SFML pour afficher la fenêtre du jeu. Or le squelette fourni était dans une ancienne version de SFML. 

**SOLUTION** <br /><br />
Pour régler le problème avec commande, on a spécifié dans les commandes d'installations qu'il fallait utiliser gcc comme compilateur. On a tous installé MinGW dans une version recente, ce qui nous a donné des versions à jour de gcc, g++
Il a fallut donc l'adapter pour correspondre à la version utilisée dans notre projet. Pour cela, nous donc regardé la doc de SFML.

## 1. Affichage du joueur

Affichage simple d'une image dans la fenêtre. Destiné à être le sprite du joueur.
ça a été assez rapide, sans problème particulier rencontrés.

## 2. Déplacement du joueur 

**CONTEXTE**<br/><br/>
Pour les déplacements du joueur, on souhaitait d'abord mettre celui-ci dans une class car c'est mieux pour le développement. 
On a donc dans un premier temps fait une class puis implémenter les déplacements du joueur dans une fonction update()

**PROBLEME**<br /><br />
La construction du `sf::Sprite` de SFML à besoin forcément d'une texture en paramètre.
Les déplacements du joueur était beaucoup trop rapide et changeait par rapport au FPS.

**SOLUTION**<br /><br/>
Pour régler le problème on a simplement passé une texture au joueur.
Pour les déplacements on a utilisé la même technique que dans Unity (et tous les moteurs de jeu) qui est multiplié la vitesse de déplacement (en px/s) par le temps ecoulé entre 2 frame. Grâce à ça les déplacements n'étaient plus affecté par les FPS.

## 2. VC

