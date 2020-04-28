# Development

---

 - **4/14/20** Began app creation.
    - Saved images for many game elements.
    - Attempted to get the Cinder Block Choreograph.
    - Emailed code mod about errors regarding the build
        - This was resolved with ChoreographConfig.cmake

 - **4/21/20** Finished setup.
    - Created an image for a game portal.
    - Added all game images and music.
    - Linked Box2D and Choreograph to the project.
        - Box2D may be unnecessary now. Remove?
 
 - **4/22/20** Implemented much game functionality.
    - Randomized the portal location. 
    - Implemented bird movement in an arc.
        - TO DO: 
            - Un-magic the numbers.
            - Restart level after approaching portal.
 
 - **4/26/20** Updated project based on feedback.
 
 - **4/27/20** Began working on win condition.
    - Separated ramp-making from mouseDown.
    - Brings bird to portal when it is close. 
        - TO DO:
            - Reset the game when you 'win'.
            - Considering level class but unsure of contents.
            - Considering a start page and pause/restart.
            - Considering a random float to subtract/add
            to the mouse click event so it's more fun.
