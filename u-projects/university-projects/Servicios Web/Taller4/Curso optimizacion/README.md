----------------------------------------------------------------
Part I

This is what i could optimize:

* Moved the inlined js function to a separated file and flagged it as async
* Inlined css
* Added the media query for the print.css file
* Move the js script tags after the body tag
* Added the meta to improve the viewport for mobile devices in the layout stage
* Minimized css and js files
* Optimized the size of all images
* Removed a web font because it wasn't helping with performance

I believe i could have done more optimizations, cache some resources for instance, but i didn't really get more points when i tried to do it, maybe i was doing it wrong.

----------------------------------------------------------------
Part II

This is what i could optimize:

* Changed the querySelector to getElementById because is faster according to people
* Deleted some fixed width to help with resizing
* Changed the number of pizzas to be thrown at the div from 200 to a number according to the screen height
* Added a new function called newUpdatePositions in order to use the requestAnimationFrame created by Paul Irish

I tried everything i knew, and i almost got to 60 fps, maybe i could have tried new methods to change the size of the pizza more efficiently but i am a newb and i don't have more time to finish, so unfortunately i had to leave it as it is.