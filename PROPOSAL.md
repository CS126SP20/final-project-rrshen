# [Happy Birds]

Author: [Rachel]

---

# Proposal
I want to create an Angry Birds-like game where you spawn in a pre-determined
position, your goal spawns in a randomly generated position to your right,
and you use an angle and power level to catapult your bird toward the goal. 

# Background
I've always enjoyed playing aiming games and those that depend on angles;
things like Let it Slide, Chuck the Sheep, Angry Birds, and even physics
simulations. I also watched the Angry Birds movie over the summer and
really enjoyed it. I haven't coded anything similar in the past, but I
think it would be a great to try so I'd know how to in the future.

# External Libraries
I took a look at https://github.com/sansumbrella/Choreograph and
https://github.com/erincatto/Box2D, and one of these libraries would
probably be sufficient to help with the catapulting calculations
necessary for the game. Choreograph seems to deal mostly with large-scale
physical forces such as gravity while Box2D definitely accounts for
collisions. It's unclear as to whether either of them deals with both.

# Timeline
**Week One:** Get the game to display with all of the necessary buttons
registering clicks and the correct position for you as well as randomly
generated goal positions for the goal position. Perhaps code the launcher,
even if what it catapults out doesn't move in a realistic trajectory.

**Week Two:** Incorporate the external physics library(or libraries) to
work with catapulting your bird(?) towards its goal and make sure that
the game is playable. Perhaps create a screen that displays your score.

**Week Three:** Make it possible to use mouse clicks and mouse click duration
instead of inputting your power level and angle and put in a high scores board
that displays after the screen with your current score.

# Stretch Goals
* Make it possible to customize your bird in a separate screen and
have it display with your customizations in game
* Make different kinds of birds, maybe with different trajectories
* Maybe add different terrain that adds levels or blocks your shots
* Display the color of the sky based on the time of day it is
* Import high scores from other players' games so you can compete
* Add an animation that plays when you open the game the first time
explaining your goals and the rules