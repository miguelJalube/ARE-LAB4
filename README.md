# Laboratoire 05 - Utilisation d'un timer avec les interruptions

## Build project

Project for the Terasic DE1-Soc board

This projects uses timer and IRQ on the HPS.

How to run the project:
    - compile Quartus project (located in hard/eda/DE1_SoC.qpf)
    - open Arm Development Studio, open the corresponding project located in soft/proj
    - Load the board with the .sof file (with python3 script setup_de1_soc.py), 
    - Compile the source files and load the processor
    - Run


folder structure:
    - doc: documentation
    - hard: files related to hardware, ie VHDL source and simulation files, Quartus and Qsys project
    - publi: publications
    - soft: files related to software, ie linux files and project, Altera Monitor Program source and project files

## Objectifs du laboratoire

Ce laboratoire vise à utiliser un timer avec les interruptions du HPS (Hard Processor System). L'objectif principal est de mettre en œuvre un timer du HPS, de générer des interruptions à partir de celui-ci, et de comprendre le mécanisme des interruptions sur la Cyclone V SoC. Le projet se base sur les spécifications des périphériques PIO (Parallel Input/Output) connectés sur le bus AXI lightweight HPS-to-FPGA.

## Spécifications

Le projet utilise le même plan d'adressage que celui du laboratoire 2, avec des périphériques PIO connectés sur le bus AXI lightweight HPS-to-FPGA. La configuration des périphériques PIO 0 et PIO 1 est détaillée, spécifiant les bits connectés et les modes de configuration.

### Plan d'adressage

- 0x00_0000 – 0x00_0003 : Constante ID 32 bits (Read only)
- 0x00_0004 - 0x00_00FF : reserved
- 0x00_0100 - 0x00_011F : Périphérique PIO 0 pour interrupteurs (switch), leds et boutons (KEY).
- 0x00_0120 - 0x00_013F : Périphérique PIO 1 pour les 4 afficheurs 7 segments (HEX0, HEX1, HEX2 et HEX3).
- 0x00_0140 – 0x1F_FFFF : not used

### Configuration utilisée dans le périphérique PIO 0

- PIO Bits 31 24 23 20 19 10 9 0
- E/S connectés : unused Key (3…0) Leds (9…0) Switch (9…0)
- Configuration :
  - Ports configurés en mode "Bidirectionnel".
  - "Individual bit set/clear output register" activé.
  - "Edge capture register" désactivé.
  - "Generate IRQ" désactivé.
  - Les switchs et Leds sont actifs à l’état haut. Les keys sont actifs à l’état bas.

### Configuration utilisée dans le périphérique PIO 1

- PIO Bits 31 28 27 21 20 14 13 7 6 0
- E/S connectés : unused Hex3 (6…0) Hex2 (6…0) Hex1 (6…0) Hex0 (6…0)
- Configuration :
  - Ports configurés en mode "Bidirectionnel".
  - "Individual bit set/clear output register" activé.
  - "Edge capture register" désactivé.
  - "Generate IRQ" désactivé.
  - Les afficheurs 7 segments sont actifs à l’état bas.

### Timer du HPS

- Utilisation du timer module 0 piloté par la clock OSC1.
- Fréquence de la clock OSC1 : 25MHz.

## Programme

Le but est de créer un minuteur à la dixième de seconde (0.1s) avec la valeur courante affichée sur les afficheurs 7 segments. Les boutons (KEY) et interrupteurs (SW) permettent d'initialiser la valeur de départ du minuteur, ainsi que de démarrer et arrêter celui-ci.

### Spécifications du fonctionnement

Au démarrage, le programme doit remplir les conditions suivantes :

- Les 10 leds sont éteintes.
- Les afficheurs 7 segments Hex0, Hex1, Hex2 et Hex3 affichent la valeur 0000.
- Afficher la constante ID au format hexadécimal dans la console de ARM-DS.
- Le minuteur est arrêté.

Pendant l'exécution du programme, les actions suivantes doivent être respectées :

- Pression sur KEY0 : Démarrage du minuteur.
- Pression sur KEY1 : Arrêt du minuteur.
- Pression sur KEY2 : Chargement d'une nouvelle valeur de départ du minuteur.
  - La valeur de SW7-0 est utilisée comme nouvelle valeur de départ en seconde, variant de 0 à 255 secondes.
  - Cette valeur de départ est copiée sur les Leds 7-0 et affichée sur les afficheurs 7 segments (Hex3, 2, 1 et 0) au format décimal à la dixième de seconde (0.1s). Hex3, 2 et 1 affichent la valeur en seconde et Hex0 affiche le dixième de seconde.

L'affichage doit respecter les conditions suivantes :

- Lorsque le minuteur s'exécute, à chaque 100ms, l'affichage de la valeur sur les 7 segments est mis à jour.
- L'état de la Led8 représente si le minuteur est actif ou non.
- Lors de chaque interruption du timer (chaque 100ms), un toogle de la Led9 est effectué.

## Travail demandé


1. Rechercher dans la documentation du HPS (cyclone-v_hps_trm_5v4.pdf) les informations concernant l'utilisation du timer module 0. Identifier les configurations nécessaires pour son utilisation avec les interruptions.
2. Rechercher dans la documentation du HPS : Quel est le numéro de la ligne d'interruption GIC qui correspond au timer à utiliser ?
3. Étudier la documentation concernant la mise en œuvre des interruptions GIC dans le HPS (cyclone-v_hps_interrupt_manual_GIC_18.1.pdf).
4. Sur Cyberlearn, récupérer l'archive du projet et la décompresser. Puis générer le bitstream du projet.
5. Lors de la création de votre projet dans ARM-DS, respecter les informations données dans le document (Utilisation_armds_avec_interruption.pdf).
6. Écrire vos fonctions C qui permettent d'initialiser votre timer et de l'utiliser. Pour les autres périphériques (Leds, switchs, boutons, afficheurs 7 segments), vous pouvez utiliser vos fonctions développées pendant le laboratoire 2.
7. Écrire les fonctions d'initialisation et de configuration des interruptions.
   - Compléter la fonction config_GIC() du fichier exceptions.c fourni. La fonction doit configurer le GIC pour utiliser l'interruption du timer.
   - Compléter la routine d'interruption \_\_cs3\_isr\_irq() du fichier exceptions.c fourni. La routine d'interruption doit être la plus rapide possible.
   - Écrire une routine d'interruption hps\_timer\_ISR() dédiée aux interruptions du timer.
8. Tester les interruptions sur la carte DE1-SoC en complétant l'application principal.
   - Appeler les différentes fonctions d'initialisation écrites

