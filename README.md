# NachOS_Project

### Team K : 

* Jonathan Borne
* Antoine Duquennoy
* Thomas Duverney
* Maxime Isnel

## Planning

* Etape 1: Installation, prise en main, compréhension (2 jours)
* Etape 2: Entrées/Sorties (2 jours)
* Etape 3: Multithreading (2 à 3 jours)
* Etape 4: Mémoire virtuelle (3 jours)
* Documentation (1 jours) Vendredi 22 Décembre
* Etape 5: Gestionnaire de fichiers (4 jours) en parallèle avec étape 6
* Etape 6: Réseaux des Machines (4 jours) en parallèle avec étape 5
* Finir développement manquant (petites fonctionnalités) (~2 jours)
* Préparer soutenance (**Pas de code**) (1 jours)
* Dernier jour: **Soutenance**

## Etapes

* Etape 1 : Mise en place
	* Installer NachOS, comprendre comment il marche. Comprendre comment executer programme utilisateur. Définir différence entre Noyau et Utilisateur.
* Etape 2 : Entrées/Sorties
	* Implémenter les entrées clavier et les sorties a l'écran. **Quatre** fonctions à implémenter: **PutChar**, **GetChar**, **PutString**, **GetString**. Pour cela il faut avoir bien compris les **appels système** de NachOS.
* Etape 3 : Multithreading
	* Permettre à l'utilisateur de faire des programmes multithreadés. Pour ce faire il faut bien comprendre l'*adressage d'un processus* dans NachOS pour le partager entre les threads. 
	* *BONUS*: l'utilisateur doit pouvoir faire de la synchronisation (Mutex?)
* Etape 4 : Mémoire Virtuelle
	* Pouvoir lancer plusieurs processus, implémentation appel système fork(). 
	* *BONUS*: implémenter un petit shell 
* Etape 5 : Systèmes de fichiers
	* Implémenter un système de fichiers qui se rapproche de ce qu'on connait: Hierarchie des dossiers, Dossier courant, Fichiers dans dossier.
	Possibilité d'ouvrir plusieurs dossiers.
* Etape 6 : Réseaux des machines
	* Pouvoir lancer plusieurs machines et établir un lien de communication entre elles. Implémenter aussi un protocole pour que deux machines puissent communiquer.
	* *BONUS*: implémenter un un serveur FTP (transferts de fichiers) ou migration de processus 


## Les Conventions

* Langue : Anglais
* Tabulation : 4 spaces
* Variable : commence par une minuscule
* Types : commence par une majuscule

## Comment on utilise Git ?

Créer une nouvelle branche pour commencer un travail :
```
git checkout -b <BranchName>
```

Changer de branche :
```
git checkout <BranchName>
```

Supprimer une branche :
```
git branch -d <BranchName>
```

Pour ajouter votre travail sur le master :
```
git checkout master
git merge <BranchName>
```

En cas de conflit :
Pour repérer les fichiers en conflit :
```
git status
```
Example de conflit (HEAD correpond à la branche master):
```
<<<<<<< HEAD:Thread.cc
coco
=======
caca
>>>>>>> branch_Thread:Thread.cc
```
Lorsque vous avez résolu les conflits d'un fichier vous pouvez l'ajouter :
```
git add <FILE>
```


## Email Report difficulty

A : cse-nachos@lists.forge.imag.fr

Sujet : [NachOS/Team K] *Sujet*

Body :

Git : https://github.com/ThomasDuverney/The_Nachos_Project

============ GIT COMMIT ============


==== COMMENT REPRODUIRE LE BUG ====


========= RESULTAT ATTENDU =========


========= RESULTAT OBSERVE =========


===== CE QUI A ETE FAIT/ANALYSE =====