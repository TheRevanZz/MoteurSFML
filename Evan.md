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

## #2 Limitation des déplacements aux bords de l'écran

**CONTEXTE**<br/>
Le joueur ne doit pas pouvoir sortir de l'écran lorsqu'il se déplace.

**PROBLEMES**<br/>
Il n'y a pas eu de problème particulier pour cette fonctionnalité. Il fallait simplement prendre en compte les dimensions de la fenêtre pour empêcher le joueur de dépasser les bords de l'écran.

**SOLUTIONS**<br/>
Il a donc fallut ajouter une limitation aux déplacements du joueur afin qu'il ne puisse pas dépasser les bords de la fenêtre.

## #3 Ajout d'entités statiques avec leur générateur

**CONTEXTE**<br/>
Dans le jeu, il y a des entités statiques, notamment des astéroïdes. Ces astéroïdes doivent pouvoir apparaître sur la carte et entrer en collision avec les joueurs.

**PROBLEMES**<br/>
Il fallait tout d'abord créer une classe pour les entités statiques et faire en sorte qu'elles puissent entrer en collision avec les joueurs.<br/>
Il fallait ensuite créer un générateur permettant de faire apparaître aléatoirement un astéroïde sur la carte, avec un temps aléatoire entre 5 et 30 secondes.<br/>
Il fallait également faire en sorte que les astéroïdes soient générés à l'intérieur de la fenêtre et non en dehors. Enfin, les entités statiques devaient être ajoutées dans une liste spécifique, située dans une autre classe, afin de pouvoir entrer en collision avec les joueurs.

**SOLUTIONS**<br/>
Il a donc fallut créer une classe pour les entités statiques et les ajouter au système de collision afin qu'elles puissent entrer en collision avec les joueurs.<br/>
Pour le générateur, on a utilisé un temps aléatoire entre 5 et 30 secondes ainsi qu'une position aléatoire sur la carte. Il a également fallut limiter les positions possibles aux dimensions de la fenêtre afin que les astéroïdes ne puissent pas apparaître en dehors de l'écran.<br/>
Pour pouvoir ajouter les nouveaux astéroïdes dans la liste utilisée pour les collisions, il a fallut récupérer cette liste sous forme de pointeur dans la classe du générateur. Le générateur peut ainsi ajouter directement les nouvelles entités dans la liste.

## #4 Ajout du générateur d'ennemis

**CONTEXTE**<br/>
Le jeu contient également des ennemis qui doivent être générés automatiquement pendant la partie. Le fonctionnement recherché était similaire à celui utilisé pour les entités statiques.

**PROBLEMES**<br/>
La base de la classe des ennemis avait déjà été réalisée par Sylvio. Il fallait donc principalement créer le générateur et l'intégrer au fonctionnement existant.

**SOLUTIONS**<br/>
Pour créer le générateur d'ennemis, on a repris le fonctionnement utilisé pour le générateur d'entités statiques. Il a donc fallut reprendre le même principe pour générer les ennemis et les ajouter dans la liste prévue à cet effet.

## #5 Gestion des différentes scènes

**CONTEXTE**<br/>
Le jeu doit avoir plusieurs scènes, notamment le menu du jeu et la scène principale. Il doit être possible de passer du menu au jeu et du jeu au menu.

_Work in progress_
