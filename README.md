# minishell
## L’objectif de ce projet est de créer un simple shell.

L'objectif du projet est de créer un shell devant:
- Afficher un prompt en l’attente d’une nouvelle commande
- Chercher et lancer le bon executable (basé sur une variable d’environnement PATH
ou en utilisant un path absolu), comme dans bash
- Nous devons implémenter les builtins suivants :
  - echo et l’option ’-n’
  - cd uniquement avec un chemin absolu ou relatif
  - pwd sans aucune option
  - export sans aucune option
  - unset sans aucune option
  - env sans aucune option ni argument
  - exit sans aucune option
-  ; dans la ligne de commande doit séparer les commandes
-  ’ et " doivent marcher comme dans bash, à l’exception du multiligne.
-  Les redirections <, > et “>>” doivent marcher comme dans bash, à l’exception des aggrégations de fd
