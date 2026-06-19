# Tests moteur à ajouter

Généré par IA (Codex), prompt :

```
fais un readme sous test/ avec la une liste de test a faire sur le moteur. 
Tri par fonctionalités proches
```

L'entièreté des tests implémentés ont été générés par Codex, partie par partie, en suivant la liste ci-dessous. 

## Scène, XML et prefabs

Déjà couvert en grande partie dans `SceneUnitTests.cpp`.

- [x] Charger une scène inexistante doit lever une exception explicite. ([`SceneParsing.MissingSceneFileThrows`](SceneUnitTests.cpp#L57))
- [x] Charger un XML malformé doit lever une exception explicite. ([`SceneParsing.MalformedSceneXmlThrows`](SceneUnitTests.cpp#L66))
- [x] Refuser une scène dont la racine n'est pas `Scene`. ([`SceneParsing.WrongRootThrows`](SceneUnitTests.cpp#L75))
- [x] Charger une scène vide sans crash. ([`SceneParsing.EmptySceneLoads`](SceneUnitTests.cpp#L84))
- [x] Charger un `GameObject` simple. ([`SceneParsing.SingleGameObjectLoads`](SceneUnitTests.cpp#L92))
- [x] Charger des `GameObject` imbriqués. ([`SceneParsing.NestedGameObjectsLoad`](SceneUnitTests.cpp#L100))
- [x] Refuser un enfant inconnu directement sous `Scene`. ([`SceneParsing.UnknownSceneChildThrows`](SceneUnitTests.cpp#L110))
- [x] Refuser un enfant inconnu sous `GameObject`. ([`SceneParsing.UnknownGameObjectChildThrows`](SceneUnitTests.cpp#L119))
- [x] Accepter un nœud `Components` vide. ([`SceneParsing.EmptyComponentsNodeLoads`](SceneUnitTests.cpp#L128))
- [x] Refuser un composant sans attribut `name`. ([`SceneParsing.ComponentWithoutNameThrows`](SceneUnitTests.cpp#L135))
- [x] Refuser un nœud non-`Component` dans `Components`. ([`SceneParsing.NonComponentChildInsideComponentsThrows`](SceneUnitTests.cpp#L144))
- [x] Refuser un composant inconnu. ([`SceneParsing.UnknownComponentThrowsInsteadOfReturningNull`](SceneUnitTests.cpp#L153))
- [x] Charger un prefab et permettre de surcharger son label. ([`SceneParsing.PrefabLoadsAndLabelCanBeOverridden`](SceneUnitTests.cpp#L162))
- [x] Refuser un prefab sans attribut `src`. ([`SceneParsing.PrefabWithoutSrcThrows`](SceneUnitTests.cpp#L172))
- [x] Refuser un fichier prefab manquant. ([`SceneParsing.MissingPrefabFileThrows`](SceneUnitTests.cpp#L181))
- [x] Refuser un prefab dont la racine n'est pas `GameObject`. ([`SceneParsing.PrefabWithWrongRootThrows`](SceneUnitTests.cpp#L190))
- [x] Charger un prefab imbriqué. ([`SceneParsing.NestedPrefabLoads`](SceneUnitTests.cpp#L199))
- [x] Instancier un prefab valide via `Scene::requestInstantiate`. ([`SceneParsing.RequestInstantiateValidPrefabReturnsPointer`](SceneUnitTests.cpp#L209))
- [x] Refuser l'instanciation d'un prefab manquant. ([`SceneParsing.RequestInstantiateMissingPrefabThrows`](SceneUnitTests.cpp#L219))
- [x] Refuser l'instanciation avec un chemin vide. ([`SceneParsing.RequestInstantiateEmptyPathThrows`](SceneUnitTests.cpp#L228))
- [x] Vérifier que les attributs XML de transform (`x`, `y`, `angle`, `sx`, `sy`) sont bien appliqués. ([`SceneParsing.GameObjectTransformXmlAttributesAreApplied`](SceneUnitTests.cpp#L237))
- [x] Vérifier la valeur par défaut d'un `GameObject` quand certains attributs XML sont absents. ([`SceneParsing.GameObjectMissingXmlAttributesUseDefaults`](SceneUnitTests.cpp#L253))
- [x] Vérifier qu'un prefab hérite correctement de ses enfants et composants. ([`SceneParsing.PrefabKeepsItsChildrenAndComponents`](SceneUnitTests.cpp#L269))
- [x] Vérifier que les objets demandés par `requestInstantiate` sont ajoutés au bon moment dans la scène. ([`SceneParsing.RequestInstantiateAddsObjectOnlyOnNextUpdate`](SceneUnitTests.cpp#L288))
- [x] Vérifier qu'il faut appeler `unload()` avant de charger une scène de remplacement. ([`SceneParsing.UnloadMustBeCalledBeforeLoadingAReplacementScene`](SceneUnitTests.cpp#L303))

## GameObject, composants et cycle de vie

- [x] Vérifier que `GameObject::addComponent` assigne bien le pointeur `gameObject` du composant. ([`GameObjectComponents.AddComponentAssignsParentGameObject`](GameObjectUnitTests.cpp#L50))
- [x] Vérifier que `getComponent<T>()` retourne le bon composant quand il existe. ([`GameObjectComponents.GetComponentReturnsExistingComponent`](GameObjectUnitTests.cpp#L61))
- [x] Vérifier que `getComponent<T>()` retourne nullptr quand le composant est absent. ([`GameObjectComponents.GetComponentReturnsNullptrWhenComponentIsMissing`](GameObjectUnitTests.cpp#L71))
- [x] Vérifier que quand plusieurs composants compatibles avec le même type existent, le premier est retourné. ([`GameObjectComponents.GetComponentReturnsFirstCompatibleComponent`](GameObjectUnitTests.cpp#L78))
- [x] Vérifier que `getComponents<T>()` retourne les bons composants quand ils existent. ([`GameObjectComponents.GetComponentsReturnsAllCompatibleComponents`](GameObjectUnitTests.cpp#L91))
- [x] Vérifier que `getComponents<T>()` retourne une liste vide quand le composant est absent. ([`GameObjectComponents.GetComponentsReturnsEmptyListWhenComponentIsMissing`](GameObjectUnitTests.cpp#L110))
- [x] Vérifier que quand plusieurs composants compatibles avec le même type existent, le premier est retourné. ([`GameObjectComponents.GetComponentReturnsFirstCompatibleComponent`](GameObjectUnitTests.cpp#L78))
- [x] Vérifier que `Start()` est appelé une seule fois par composant. ([`GameObjectLifecycle.StartIsCalledOncePerComponentForEachStartCall`](GameObjectUnitTests.cpp#L118))
- [x] Vérifier que `Update()` n'est pas appelé sur un `GameObject` inactif. ([`GameObjectLifecycle.UpdateIsNotCalledOnInactiveGameObject`](GameObjectUnitTests.cpp#L135))
- [x] Vérifier qu'un enfant inactif ne met pas à jour ses composants. ([`GameObjectLifecycle.InactiveChildDoesNotUpdateItsComponents`](GameObjectUnitTests.cpp#L147))
- [x] Vérifier qu'un enfant localement actif est considéré inactif si son parent est inactif. ([`GameObjectLifecycle.ChildIsInactiveWhenParentIsInactive`](GameObjectUnitTests.cpp#L162))
- [x] Vérifier que `destroy()` marque l'objet puis que la scène le supprime au bon moment. ([`GameObjectLifecycle.DestroySelfMarksObjectForDestruction`](GameObjectUnitTests.cpp#L173), [`GameObjectLifecycle.SceneRemovesDestroyedObjectsOnUpdate`](GameObjectUnitTests.cpp#L184))
- [x] Vérifier qu'un objet détruit ne laisse pas de pointeurs invalides dans les managers.
- [x] Vérifier que l'ajout de composant pendant `Start()` ne casse pas l'itération des composants. ([`GameObjectLifecycle.AddingComponentDuringStartDoesNotBreakComponentIteration`](GameObjectUnitTests.cpp#L199))
  - À revoir car c'est pas géré mais le test passe par chance.

## Transform et hiérarchie

- [x] Vérifier la position locale par défaut. ([`TransformBasics.DefaultLocalPositionIsZero`](TransformUnitTests.cpp#L14))
- [x] Vérifier `setLocalPosition`, `move`, `rotate` et `rescale`. ([`TransformBasics.LocalMutatorsUpdateLocalValues`](TransformUnitTests.cpp#L21))
- [x] Vérifier le calcul de position monde avec un parent. ([`TransformHierarchy.WorldPositionIncludesParentPositionAndScale`](TransformUnitTests.cpp#L43))
- [x] Vérifier que la position monde d'un enfant tourne autour du parent quand le parent rotate. ([`TransformHierarchy.WorldPositionRotatesAroundParent`](TransformUnitTests.cpp#L53))
- [x] Vérifier le calcul de rotation monde avec un parent. ([`TransformHierarchy.WorldRotationAddsParentRotation`](TransformUnitTests.cpp#L63))
- [x] Vérifier le calcul d'échelle monde avec un parent. ([`TransformHierarchy.WorldScaleMultipliesParentScale`](TransformUnitTests.cpp#L73))
- [x] Vérifier qu'un enfant change de position monde quand son parent bouge. ([`TransformHierarchy.ChildWorldPositionChangesWhenParentMoves`](TransformUnitTests.cpp#L83))
- [x] Vérifier qu'un changement de parent conserve une hiérarchie cohérente. ([`TransformHierarchy.ChangingParentUpdatesWorldValuesAndNewParentChildren`](TransformUnitTests.cpp#L95))
- [x] Vérifier les cas limites: échelle nulle, rotation négative, plusieurs niveaux d'enfants. ([`TransformHierarchy.EdgeCasesHandleZeroScaleNegativeRotationAndMultipleLevels`](TransformUnitTests.cpp#L114))

## ComponentFactory et enregistrement

- [x] Vérifier qu'un composant enregistré peut être créé par son nom. ([`ComponentFactoryRegistration.RegisteredComponentCanBeCreatedByName`](ComponentFactoryUnitTests.cpp#L35))
- [x] Vérifier qu'un nom inconnu lève une exception claire. ([`ComponentFactoryRegistration.UnknownComponentNameThrowsClearException`](ComponentFactoryUnitTests.cpp#L53))
- [x] Vérifier qu'un enregistrement avec un nom déjà existant lève une exception. ([`ComponentFactoryRegistration.DuplicateRegistrationThrows`](ComponentFactoryUnitTests.cpp#L70))
- [x] Vérifier que les attributs XML sont transmis au constructeur du composant. ([`ComponentFactoryRegistration.XmlAttributesArePassedToComponentCreator`](ComponentFactoryUnitTests.cpp#L90))
- [ ] Vérifier que les composants moteur auto-enregistrés (`Renderer`, `Collider`, `Animator`, etc.) sont disponibles.

## SceneManager et navigation

- [x] Vérifier que `requestLoading` stocke une seule demande de chargement. ([`SceneManagerNavigation.RequestLoadingStoresOnePendingSceneLoad`](SceneManagerUnitTests.cpp#L56))
- [x] Vérifier qu'une deuxième demande de chargement est ignorée si une demande est déjà en attente. ([`SceneManagerNavigation.SecondLoadingRequestIsIgnoredWhileOneIsPending`](SceneManagerUnitTests.cpp#L68))
- [x] Vérifier que `applyRequest` décharge l'ancienne scène avant de charger la nouvelle. ([`SceneManagerNavigation.ApplyRequestUnloadsCurrentSceneBeforeLoadingNextOne`](SceneManagerUnitTests.cpp#L80))
- [x] Vérifier que `freeze()` bloque les updates de gameplay attendus. ([`SceneManagerNavigation.FreezeBlocksGameplayUpdates`](SceneManagerUnitTests.cpp#L93))
- [x] Vérifier que `unfreeze()` reprend les updates. ([`SceneManagerNavigation.UnfreezeResumesGameplayUpdates`](SceneManagerUnitTests.cpp#L106))
- [x] Vérifier que `instantiate()` délègue correctement à la scène courante. ([`SceneManagerNavigation.InstantiateDelegatesToCurrentScene`](SceneManagerUnitTests.cpp#L121))
- [x] Vérifier que `getGui()` retourne le GUI de la scène courante. ([`SceneManagerNavigation.GetGuiReturnsCurrentSceneGui`](SceneManagerUnitTests.cpp#L134))

## Input

- [x] Vérifier le parsing d'un fichier de configuration d'input valide. ([`InputManagerParsing.ValidKeyboardConfigCreatesExpectedActions`](InputUnitTests.cpp#L47))
- [x] Vérifier qu'une action clavier est créée avec la bonne touche. ([`InputActionKeyboard.ButtonActionUsesConfiguredKeyboardKey`](InputUnitTests.cpp#L92), [`InputActionKeyboard.ButtonActionIgnoresOtherKeyboardKeys`](InputUnitTests.cpp#L101))
- [x] Vérifier qu'une action `Vector2D` clavier lit correctement ses quatre directions. ([`InputActionKeyboard.Vector2DActionReadsConfiguredDirections`](InputUnitTests.cpp#L110))
- [x] Vérifier qu'une action inconnue retourne `nullptr` ou une erreur contrôlée selon le contrat voulu. ([`InputManagerParsing.UnknownActionThrowsControlledException`](InputUnitTests.cpp#L56))
- [x] Vérifier qu'un type d'input non supporté lève une exception claire. ([`InputManagerParsing.UnsupportedInputTypeThrowsClearException`](InputUnitTests.cpp#L74))
- [x] Vérifier `wasPerformedThisFrame()` sur une transition relâchée -> appuyée. ([`InputActionKeyboard.WasPerformedThisFrameIsTrueOnlyOnReleasedToPressedTransition`](InputUnitTests.cpp#L153))
- [x] Vérifier que `wasPerformedThisFrame()` ne reste pas vrai plusieurs frames. ([`InputActionKeyboard.WasPerformedThisFrameIsTrueOnlyOnReleasedToPressedTransition`](InputUnitTests.cpp#L153))
- [x] Vérifier `ReadValue<sf::Vector2f>()` pour les actions de mouvement. ([`InputActionKeyboard.Vector2DActionReadsConfiguredDirections`](InputUnitTests.cpp#L110), [`InputActionKeyboard.Vector2DActionClampsOppositeDirections`](InputUnitTests.cpp#L134))
- [x] Vérifier qu'une exception est levée si le fichier de config input est absent ou invalide. ([`InputManagerParsing.InvalidConfigFileThrows`](InputUnitTests.cpp#L65))

## Collisions et physique simple

- [x] Vérifier l'enregistrement et le désenregistrement d'un `Collider` dans `CollisionsManager`. ([`CollisionsManagerPhysics.ColliderRegistersOnStartAndUnregistersOnDestruction`](CollisionUnitTests.cpp#L39))
- [x] Vérifier la détection de collision entre deux rectangles qui se chevauchent. ([`CollisionsManagerPhysics.OverlappingRectanglesAreDetectedByTrigger`](CollisionUnitTests.cpp#L52))
- [x] Vérifier l'absence de collision entre deux rectangles séparés. ([`CollisionsManagerPhysics.SeparatedRectanglesDoNotCollide`](CollisionUnitTests.cpp#L63))
- [x] Vérifier les collisions sur les bords exacts. ([`CollisionsManagerPhysics.SolidRectanglesTouchingEdgesDoNotBlockMovementAway`](CollisionUnitTests.cpp#L71))
- [x] Vérifier qu'un collider trigger appelle son callback sans bloquer le mouvement. ([`CollisionsManagerPhysics.TriggerColliderCallsCallbackWithoutBlockingMovement`](CollisionUnitTests.cpp#L81))
- [x] Vérifier le bon fonctionnement de `CollisionsManager::move()` ([`CollisionsManagerPhysics.MoveReturnsZeroOnAxisBlockedBySolidCollider`](CollisionUnitTests.cpp#L105), [`CollisionsManagerPhysics.MoveKeepsUnblockedAxisWhenOtherAxisIsBlocked`](CollisionUnitTests.cpp#L115), [`CollisionsManagerPhysics.CharacterControllerMoveUsesCollisionsManagerResolution`](CollisionUnitTests.cpp#L158))
- [x] Vérifier qu'un collider inactif ou détruit n'est plus pris en compte. ([`CollisionsManagerPhysics.InactiveColliderIsNotTakenIntoAccount`](CollisionUnitTests.cpp#L125), [`CollisionsManagerPhysics.DestroyedColliderIsNotTakenIntoAccount`](CollisionUnitTests.cpp#L133))
- [x] Vérifier le comportement quand plusieurs colliders sont touchés en même temps. ([`CollisionsManagerPhysics.TriggerReportsMultipleHitColliders`](CollisionUnitTests.cpp#L145))
- [x] Vérifier que les tailles XML du `Collider` sont bien appliquées. ([`CollisionsManagerPhysics.ColliderSizeIsReadFromXml`](CollisionUnitTests.cpp#L176))

## Rendu, camera et ordre d'affichage

- [ ] Vérifier que le XML d'un `Renderer` transmet bien `src`, `sprite_w` et `sprite_h` au composant.
- [ ] Vérifier qu'une texture valide permet à `Renderer::Start()` de réussir.
- [ ] Vérifier qu'une texture manquante provoque une erreur claire.
- [ ] Vérifier qu'un `Renderer` démarré est ajouté au `RenderManager`.
- [ ] Vérifier qu'un `Renderer` détruit est retiré du `RenderManager`.
- [ ] Vérifier qu'un `Renderer` porté par un `GameObject` inactif est ignoré au rendu.
- [ ] Vérifier que l'ordre de rendu est stable quand deux objets ont la même profondeur.
- [ ] Vérifier que l'ordre de rendu respecte la profondeur Y si c'est la règle choisie.
- [ ] Vérifier qu'une caméra démarrée devient la caméra utilisée par le rendu.
- [ ] Vérifier le comportement attendu quand aucune caméra n'existe.
- [ ] Vérifier le comportement attendu quand plusieurs caméras existent.

## Animation

- [ ] Vérifier le parsing d'un arbre d'animation valide.
- [ ] Vérifier qu'un fichier d'animation manquant lève une erreur claire.
- [ ] Vérifier qu'un paramètre booléen déclenche la bonne transition.
- [ ] Vérifier qu'un paramètre numérique déclenche la bonne transition.
- [ ] Vérifier que l'animation courante avance avec `elapsedTime`.
- [ ] Vérifier qu'un event d'animation est appelé à la bonne frame.
- [ ] Vérifier qu'un event d'animation n'est pas appelé plusieurs fois par erreur.
- [ ] Vérifier que deux fichiers différents, avec des labels différents, produisent deux arbres différents au lieu de partager accidentellement le même objet en cache.
- [ ] Vérifier que deux `Animator` peuvent jouer indépendamment.
- [ ] Vérifier le reset d'un paramètre de trigger après consommation.

## UI et documents TGUI

- [x] Vérifier que `UIDocument::Start` récupère le GUI de la scène. ([`UIDocumentBaseBehavior.StartUsesCurrentSceneGui`](UIDocumentUnitTests.cpp#L78))
- [x] Vérifier que `addElement` ajoute le widget au GUI et le garde dans `elements`. ([`UIDocumentBaseBehavior.AddElementStoresWidgetAndAddsItToGui`](UIDocumentUnitTests.cpp#L89))
- [x] Vérifier que le destructeur de `UIDocument` retire tous ses widgets du GUI. ([`UIDocumentBaseBehavior.DestructorRemovesOwnedWidgetsFromGui`](UIDocumentUnitTests.cpp#L101))
- [x] Vérifier qu'un document caché désactive et rend invisibles ses widgets. ([`UIDocumentBaseBehavior.HideDisablesAndHidesAllElements`](UIDocumentUnitTests.cpp#L116))
- [x] Vérifier qu'un document affiche réactive et rend visibles ses widgets. ([`UIDocumentBaseBehavior.ShowEnablesAndShowsAllElements`](UIDocumentUnitTests.cpp#L134))
- [ ] Vérifier l'ordre d'affichage quand plusieurs `UIDocument` coexistent.
- [ ] Vérifier qu'un menu affiche au premier plan psse au-dessus du HUD.
- [ ] Vérifier qu'un bouton TGUI peut demander un changement de scène sans crash.
- [ ] Vérifier que la destruction de scène ne laisse pas de widget TGUI dangling.

## Game loop et intégration minimale

- [ ] Vérifier que `Game` demande le chargement de la scène initiale.
- [ ] Vérifier que la boucle fixe utilise bien le pas de temps attendu.
- [ ] Vérifier que les events SFML sont transmis à TGUI.
- [ ] Vérifier que l'ordre global reste: input/events, update logique, rendu moteur, rendu GUI.
- [ ] Vérifier qu'une fermeture de fenêtre termine proprement la boucle.
- [ ] Vérifier qu'une scène minimale peut être lancée sans composant de gameplay.

## Exceptions et robustesse

- [ ] Vérifier que les erreurs moteur importantes utilisent `IllegalOperationException`.
- [ ] Vérifier que les messages d'erreur contiennent le chemin du fichier concerné quand c'est utile.
- [ ] Vérifier que les pointeurs critiques (`SceneManager::scene`, `UIDocument::gui`, etc.) sont protégés ou échouent clairement.
- [ ] Vérifier les cas de fichiers vides, chemins vides et attributs XML invalides.
- [ ] Vérifier qu'un test invalide ne provoque pas de crash natif non contrôlé.
