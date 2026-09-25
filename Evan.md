# Suivi individuel Evan

## #0 Configuration et setup du projet (en feat avec Sylvio)
**CONTEXTE** <br/>
On souhaitait mettre en place un environnement de développement qui soit facilement a utilisé une fois mis en place. Avec une installations des dépendances rapide et fiable. <br />
On a donc opté pour Conan afin d'installer les dépendances, et CMake pour build le projet. Ensuite on a essayer d'exploiter le projet template donné pour le SFML.

**PROBLEME** <br/>
Pour nous aider à configurer le projet avec Conan et CMake on a utilisé nos différents cours où on avait déjà mis en pratique ces outils.
On a reussi a exploité Conan et CMake pour la configuration du projet, mais lors de l'utilisation de l'IDE Rider, on a rencontré de nombreux problèmes.
L'IDE voulait compiler un CMake avec le compilateur gcc, tandis que les commandes conan qu'on avait faite, utilisais msvc comme compilateur.
Ensuite, nous avons dû faire le squelette minimal SFML pour afficher la fenêtre du jeu. Or le squelette fourni était dans une ancienne version de SFML. 

**SOLUTION** <br/>
Pour régler le problème avec commande, on a spécifié dans les commandes d'installations qu'il fallait utiliser gcc comme compilateur. On a tous installé MinGW dans une version recente, ce qui nous a donné des versions à jour de gcc, g++
Il a fallut donc l'adapter pour correspondre à la version utilisée dans notre projet. Pour cela, nous donc regardé la doc de SFML.

## #1 Rotation du joueur
**CONTEXT**<br/>
Le joueur doit pouvoir s'orienter dans la direction dans laquelle il se dirige. S'il se déplace vers la droite de l'écran, il doit d'orienter vers la droite.

**PROBLEMES**<br/>
Il fallait faire cette rotation de façon progressive et non de façon instantanée. Il fallait aussi gérer les déplacements en diagonale (direction haut + gauche, direction bas + droite, ...).

**SOLUTIONS**<br/>
Pour gérer les déplacements en diagonale, il fallut faire des conditions en plus afin de plus ou moins rotationner le joueur pour correspondre à sa direction. Pour la rotation progressive, il a fallut faire en fonction de delta time pour avoir le résultat souhaité. Il a également fallut normaliser l'angle de rotation, entre -180 et 180, afin de ne pas un tour complet pour rien. 

## #2 Limitation des déplacement aux bords de l'écran
**CONTEXTE**<br/>
**PROBLEMES**<br/>
**SOLUTIONS**<br/>

## #3 Ajout d'entités statiques avec leur générateur
**CONTEXTE**<br/>
**PROBLEMES**<br/>
**SOLUTIONS**<br/>

## #4 Ajout du générateur d'ennemies
**CONTEXTE**<br/>
**PROBLEMES**<br/>
**SOLUTIONS**<br/>

## #5 Gestion des différentes scènes
**CONTEXTE**<br/>
**PROBLEMES**<br/>
**SOLUTIONS**<br/>
