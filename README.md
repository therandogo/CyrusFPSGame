This is a small FPS game with a json integration for spawning cubes of different shapes,sizes,rotations and colors in the world.
It uses simple C++ programs and prebuilt assets from the Unreal Engine FPS template.

There are two pieces that mainly govern the boxes and its generation:

The first one being the box itself which is a simple Cube with a dynamic material attached to it during run time to change its colors and a health component for taking damage.
For the damage I decided to go with the basic implementation of TakeAnyDamage (which is overridden in the health component) and ApplyDamage prebuilt in Unreal to increase efficiency.
The box also has a field for score which passes its values to the GameMode to increase the total score that the player has.

The BoxSpawner takes care of the parsing and spawning of the boxes in the actual world, it uses the native UE C++ API for json parsing and fetching from http links.
On recieving the data, it parses through all the object fields storing it as a sruct in an array which is then utilised as the template from which the boxes are spawned in runtime setting paramaters such as,
Color, Health and Score in the boxes.

The Score is managed solely by the GameMode and does the job of adding the selected UIWidget to the currently active pawn in runtime, 
and on destroying a box the score related to the box is automatically added back to the UIWidget using function calls.

The project was relatively simple, yet the json integration proved to be the toughest of the bunch,
as i personally didnt have a lot of experience with Json integration but utilising online resources and a bit of ingeniuty i was able to make it work!

For testing the features simply:
1. open the project by clicking on the uProject files
2. hit yes if it asks to rebuild binaries
3. wait a few seconds for it to rebuild and compile
4. On entering the editor simply hit the play button
5. Everything should work as intended

In the project:
1. First pick up the gun
2. Then simply press LeftClick to shoot your gun
3. Projectiles launched from the gun damages the cubes so keep hitting until they are destroyed
4. Score for the respective cube is added to the UI Widget

Overall this was a very fullfilling and fun project and I would love to pursue more of these experiences in the future!
