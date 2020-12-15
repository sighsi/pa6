WELCOME TO THE COVID TRACKER by Silas Stokes, Connor Dellwo and Daniel Olds

This programs intended purpose is to track covid data in real time (or at least as often
as the api we're using is updated) and then display it on a window. Unfortunetly the 
SDK used to build the API has quite a few dependencies and so makes the system not portable.
If you want to run it or a demonstration - might be easier to have one of us do it for you 
and screenshare. 

The scope of the project was as follows:
     1) get the data via the interenet using the MS's REST SDK and place it in a hashmap
     2) Allow users to sort how that data is portrayed to them
         a) currently allows users to view cases by state and by date in just a text printout on screen
          b) eventually users should be able to view it graphhically (we struggled to get this with SFML)
       3) Allow users to message eachother using a networked chat system.
           a) This part of the project was developed externally and meant to be integrated after the fact
               and thus isn't yet implemented in the GUI
    


    TESTS:

        simply uncomment them from the bottom of the page. 



