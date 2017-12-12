# Nachos_Project

Team K : 
  - Jonathan Borne
  - Antoine Duquennoy
  - Thomas Duverney
  - Maxime Isnel

## Les Conventions

- Langue : Anglais
- Tabulation : 4 spaces

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
