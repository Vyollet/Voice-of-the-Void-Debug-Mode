# Voice of the Void/Unreal Engine Debug Mode
**for resercheing purposes**

Using engine features to interact with a Unreal Engine-based game. Using external DLL injection.

![alt text](img/2.png)

## Features

* Exploits
  * Console F2

   | A few interesting commands |  |
  | ------ | ------ |
  | Toggledebugcamera | Toggles the player controller to the debug camera controller. |
  | Summon | Summon objects. Example: ```Summon prop_gravgun_c```. You can use [this list][secret] to look up object names. |
  | Show staticmeshes/BSP | Disables objects / walls. BSP only shows the result in tutorial level.
  * Game Time (Additional window)
  * Fly
    * Disable Collision
  * Add points
  * Chad mod (Large objects lose weight)
  * No Damage
  * No Draining food
  * No Draining sleep
  * Speed of time
  * Teleport
  * Infinity Fuel
  * Infinity Health

* ESP
  * Names
  * Box
  * Lines
  * Change draw distance

* List Objects (View list visible objects and deleted objects)

* Change Prop position (Teleport objects to player)
* Destroy Prop

## Using
1. Download from realese (DLL and, if you don't have the injector, you will also need the exe file) / Compile project
2. Place the exe file together with the DLL in any convenient place.
3. Start the game
4. Start exe file (Don't need administrator privileges)
5. Press "Insert" in the game for open a start window

## How to Compile
You will need developer tools directly related to Unreal Engine and Voice of the Void. You will have to find them on your own. I do not have permission to distribute them.

1. Clone this repo
2. Put developer tools in "Project2" folder
3. Make sure Realese and x64 are selected
4. Compile

   [secret]: <https://raw.githubusercontent.com/Vyollet/Voice-of-the-Void-Debug-Mode/main/Project2/secrets>