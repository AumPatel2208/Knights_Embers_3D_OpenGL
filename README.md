# Advanced Games Tech

## top priority
- [ ] change the enemy models to lower poly to reduce file size, as will not have enough space later on


## TO-DO
- [x] Primitive Objects
  - [x] Power ups that scale up and down move around the map
  - [x] transform
- [ ] Camera
  - [ ] just need to limit to a radius/square/cube thing
- [x] Mesh Based object
  - [x] make multiple enemies with movement and different scales and animations
  - [x] the change size when in close enough distance
  - [x] make it so that it agro's and starts moving only when the player is certain distance away
- [x] Commenting
- [ ] Change help Screen
  - [ ] include P to load level 1 and transport the player
  - [ ] explain enemies
  - [ ] write that you can press 1 to start the game and escape to quit
- [ ] Report
  - [ ] mention having the menu as a small camera technique as well
  - [ ] mention that I created the level in blender as well




## Checklist

- [x] intro screen
  - [ ]? top down camera view pan into the gameplay view
  - [ ]? interactible buttons?
- [ ] Primitive based object
  - [ ] with multiple transformations
  - [ ] could have a power up move around the map/scale up and down, stay there for a bit and move around more afterwards
- [ ] Skybox and terrain textures
  - [x] skybox
  - [x] terrain
- [ ] Camera motion technique
  - [x] mostly done
  - [ ] just need to limit to a radius/square/cube thing
  - [ ] like ratchet and clank
    - [ ] strafe and free move
- [ ] Mesh-based object
  - [x] Level
  - [ ] make multiple enemies with movement and different scales and animations
- [ ] Report
- [ ] Source Code Design, organization and coding style
- [ ] Plagiarism Check
- [ ] NPC dialogue
  - [ ] maybe have 2 or 3 choices of branching dialogue (resets on playing the game again). gives you the weapon
    - [ ] offers you the weapon to help you in the journey
    - [ ] or scoffs at you if you dont gain his respect. he gives you the weapon but might say "you'll die out there without this"
- [ ] Light
  - [ ] have a light source around the player, lighting up the scene.
- [ ] Effects
  - [ ] on collision have blood or sparks based on what they hit
  - [ ] have a different coloured blood when the player is hit
  - [ ] add fog on the outside
- [ ] mesh based objects
  - [ ] Level
  - [ ] door (opens and closes) - make it into a gate maybe, opened and closed with a switch
  - [ ] maybe torches
  - [ ] friendly NPC with dialogue
  - [ ] enemies
  - [ ] boss
- [ ] difficulty
  - [ ] difficulty switches maybe based on how much time the player took in the beginning section, or killing a few enemies
  - [ ] it could just have a bell/switch you can activate that ups the health and the attack damage of the enemies
  - [ ] it could just up the difficulty and reset you to the beginning of the level
    - [ ] can be attached to a stop watch showing how long the player has survuved in the game.
    
    
## Documentation checklist
- finite state machines for the enemies
- maybe describe the animation handler or something better if i do come up with something

## Souls-Like Game

- Player
  - weapons (2 weapons)
    - light attack
    - heavy attack
      - charged attack (stretch)
  - shield
    - parry (sound effect when parry)
  - **health**
  - **stamina**
  - **inventory (active item is highlighted)**

- item pickups
  - key items
  - **XP/souls**
  - **power ups**  
    - stamina boost
    - attack boost
- enemies
  - Types
    - Brute
      - killing brute drops a special weapon
    - Fodder
    - Boss Fight
  - Ragdoll
  - Attack player
    - heavy
    - light
  - block attacks
    - can be staggered if they block too much
  - wait before attacking
    - have it on a random time thing maybe
  - Goal
    - find the key to access the door to the boss fight
  - make something cool happen after killing boss
  
- DIFFICULTY
  - enemy
    - health increase
    - damage increase
    - detection vision cone increases
- CHEAT CODE
  - god mode
- **HUD**
  - **all bold things above**
  - **mini map of sorts**


#### Procedurally generated trees
- https://weigert.vsos.ethz.ch/2020/10/19/transport-oriented-growth-and-procedural-trees/

 



Skybox          

negy = bottom

posy = top

negx = left

posx = right

negz = back

posz = front
