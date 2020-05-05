# Development

---
## Week Zero

 - **4/14/20** *Began app creation.*
    - Saved images for many game elements.
    - Attempted to get the Cinder Block Choreograph.
    - Emailed code mod about errors regarding the build
        - This was resolved with ChoreographConfig.cmake

## Week One

 - **4/21/20** *Finished setup.*
    - Created an image for a game portal.
    - Added all game images and music.
    - Linked Box2D and Choreograph to the project.
 
 - **4/22/20** *Implemented some basic game functionality.*
    - Randomized the portal location. 
    - Coded bird movement in an arc.
        - TO DO: 
            - [ ] Un-magic the numbers.
            - [x] Restart level after approaching portal.
 
## Week Two

 - **4/26/20** *Updated project based on feedback.*
    - Changed name from my_app to happy_birds
    - Implemented mouseDown() instead of mouseMove()
    - Replaced char array with std::string for certain constants
 
 - **4/27/20** *Began working on win condition.*
    - Separated ramp-making from mouseDown.
    - Brings bird to portal when it is close. 
        - TO DO:
            - [x] Reset the game when you 'win'
            - [ ] Possibly create a level class
            - [x] Create a start page
            - [x] Create pause and restart buttons
            - [x] Add a random float to the ramp
            so it's more random and fun.
            
 - **4/28/20** *Began resetting the level.*
    - Added PROPOSAL.md
    - Resets positions and adds a point when you win
    - Added ResetLevel() function to reset level
    - R key now triggers a reset of the level
    
 - **4/29/20** *Simplified old code.*
    - P key now triggers a pause of the level
    - Streamlined setup() by calling ResetLevel()
    - Removed Box2D from the app
    - Added randomness factor into the ramp
        - TODO: 
            - [x] Show score
            - [x] End game when bird misses

## Week Three

 - **5/3/20** *Began updating project based on feedback.*
    - Created Bird class
    - Added enum class of game states
    
 - **5/4/20** *Continued updating project based on feedback.*
    - Created a starting and ending screen
    - Added weekly headers to DEVELOPMENT.md
    - Rearranged update() for minimal nesting
    - Changed GetManhattanDistance() to GetEuclideanDistance()
    and made it a standalone function
    - Created a header file for constants
    - Wrote a README file with a GIF
        - TODO: 
            - [ ] Finish Bird() class
            - [ ] Create different birds
            - [x] Add `q` as a quit button
            - [x] Add `n` as a new game button?
  
 - **5/4/20** *Made smaller adjustments.*
    - Added a delay before the ending screen
    - Made line comments explaining ending_x_ and ending_y_
    - Made the user's score display during and after the game