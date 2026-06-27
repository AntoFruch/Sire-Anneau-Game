# Sire-Anneau Game

Sire-Anneau Game est un jeu d'action en 2D inspiré de Cyrano de Bergerac. Le joueur incarne Cyrano et traverse plusieurs scènes emblématiques en affrontant des vagues d'ennemis, puis un boss propre à chaque lieu.

Le projet repose sur un moteur maison orienté composants : les scènes, prefabs, entités, collisions, animations, interfaces et comportements de gameplay sont assemblés principalement depuis des fichiers XML.

## Commande à exécuter après pull !

```bash
git submodule update --init --recursive
```
permet de pull le submodule qu'est `engine/`.

## Aperçu

![Menu principal](docs/images/menu-principal.png)

![Combat dans le théâtre](docs/images/devant-theatre.png)

![Bossfight à Arras](docs/images/combat-theatre.png)

## Concept

Le jeu mélange beat'em up, hack'n slash léger et progression par scènes. Chaque zone propose une ambiance différente, des ennemis adaptés et un combat final.

Le ton du jeu reprend l'esprit de Cyrano : panache, duels, théâtre, tirades et affrontements exagérés.

## Scènes principales

### Théâtre

Première arène du jeu. Cyrano affronte les ennemis dans une salle de théâtre avant de combattre le boss Valvert.

### Balcon de Roxane

Scène plus intime et nocturne, centrée autour du balcon de Roxane. Le joueur y affronte des vagues d'ennemis avant le combat contre le Capitaine.

### Siège d'Arras

Grande scène de bataille. Le joueur doit survivre à une pression plus forte, avec davantage d'ennemis simultanés, avant d'affronter le Commandant.

## Fonctionnalités

- Moteur 2D basé sur des `GameObject` et des `Component`.
- Scènes et prefabs déclaratifs en XML.
- Système de collisions, triggers et zones de chargement.
- Animation par arbres d'animation et paramètres.
- Contrôleur joueur, ennemis, boss et spawners.
- Bossfights avec vagues d'ennemis, compteur de progression et HUD dédié.
- Interface TGUI : menu principal, pause, game over, barre de vie et boîte de dialogue.

## Structure

- `src/engine/` : moteur de jeu maison.
- `src/assets/scripts/` : scripts gameplay, UI, ennemis, boss et zones.
- `src/assets/resources/` : scènes, prefabs, textures, animations, polices et configuration.
- `src/test/` : tests unitaires du moteur et des systèmes principaux.
- `uml/` : diagrammes PlantUML et exports.
