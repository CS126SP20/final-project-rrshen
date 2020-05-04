# Development

---
## Week Zero

 - **4/14/20** Began app creation.
    - Saved images for many game elements.
    - Attempted to get the Cinder Block Choreograph.
    - Emailed code mod about errors regarding the build
        - This was resolved with ChoreographConfig.cmake

## Week One

 - **4/21/20** Finished setup.
    - Created an image for a game portal.
    - Added all game images and music.
    - Linked Box2D and Choreograph to the project.
 
 - **4/22/20** Implemented much game functionality.
    - Randomized the portal location. 
    - Implemented bird movement in an arc.
        - TO DO: 
            - [ ] Un-magic the numbers.
            - [x] Restart level after approaching portal.
 
## Week Two

 - **4/26/20** Updated project based on feedback.
 
 - **4/27/20** Began working on win condition.
    - Separated ramp-making from mouseDown.
    - Brings bird to portal when it is close. 
        - TO DO:
            - [x] Reset the game when you 'win'
            - [ ] Possibly create a level class
            - [x] Create a start page
            - [x] Create pause and restart buttons
            - [x] Add a random float to the ramp
            so it's more random and fun.
            
 - **4/28/20** Began resetting the level.
    - Added PROPOSAL.md
    - Resets positions and adds a point when you win
    - Added ResetLevel() function to reset level
    - R key now triggers a reset of the level
    
 - **4/29/20** Simplified old code.
    - P key now triggers a pause of the level
    - Streamlined setup() by calling ResetLevel()
    - Removed Box2D from the app
    - Added randomness factor into the ramp
        - TODO: 
            - [ ] Show score
            - [ ] End game when bird misses

## Week Three

 - **5/3/20** Updated project based on feedback.
    - Added Bird class
    - Added enum class of game states
    
 - **5/4/20** Continued updating project.
     - Created a starting and ending page
     - Added weekly headers to DEVELOPMENT.md
     - Rearranged update() for minimal nesting
     - Made GetManhattanDistance() standalone
     - Created a header file for my constants
     - Wrote a README file
        - TODO: 
            - [ ] Finish Bird() class
            - [ ] Create different birds
            - [ ] Add `q` as a quit button