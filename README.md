## The Idea:

I haven't been able to fly for a while. I've even had to do a cross-country drive from Colorado to Denver that lasted almost 28 hours nonstop. For this sculpture, I wanted to make an ode to flight, oh how I miss thee. Jokes aside, I thought it would be fun to animate a plane. This was the motivation for the idea.

## The Specifics:

With an idea in mind, it was time to nail down the specifics. I wanted this to be an experience. When you take off in a real plane, the engines vibrate, the pilot announces the take-off--it's a visceral moment. I wanted the sculpture to provide as much of this as possible ( unfortunately that's not that much). First, I wanted the engine to show forward movement or propulsion. I wanted the flaps on the plane to move. I also wanted something to announce the steps of take-off and engage the viewer. I settled on using two motors to control the propeller and flaps. 

## How I Built It:

This project was built using a foam plane, several motors, and some additional components. 

### Materials
- Servo Motor
- DC Motor (My DC motor ended up breaking, so I had to use the Stepper Motor)
- Stepper Motor( Use this if and only if the DC motor breaks)
- Stepper Motor Relay
- LCD Screen
- ESP-32
- Foam Plane

## Hardware

The first step in this project was getting all the movements working. The movements were focused on getting a propeller to spin and the flaps of the airplane to move. For the propeller, I hooked up the DC motor to the ESP-32. Pretty quickly into the testing process, the DC motor started oozing some strange liquid and stopped spinning. I had to jump ship to the stepper motor. The stepper motor required a relay. This was then connected to the ESP-32 and tested. Using the example sketch, I was able to get the stepper motor to rotate. One of the unfortunate parts about losing the DC motor was that the rotation speed of the stepper motor is significantly slower than the DC motor. The faster rotation speed would have given a better effect, however, it is not the end of the world. 

The next step was getting the servo working. The servo's job was to move the flaps of the plane up and down. The rear flaps on a plane are known as elevators as they control the plane's ability to climb and descend. This meant the servo had to have a range of motion that would allow the rear flaps to bend up and down. This was easier than expected. The servo has precise motion control. I set a specific range and the servo kept a consistent range of motion. 

The last piece of hardware for the project was the LCD screen. The screen was used to display comments such as "Take Off" or "Engine Test". This step was easy. I wired up the screen to the ESP-32 as recommended by the tutorial.




## Software

This was the next part of the project. Once all the motors and servos were connected, it was time to code up the story of the takeoff. The general pattern was to have the plane run some engines and flap test, get into take-off position, and then take off. Initially, I thought it might make sense to run this on two separate cores to have the tests going at the same time, but in the end, the story was more interactive when it was run linearly.

For the "throttle test", I have the engine rotate forward and backward as if it is preparing to start up. For the "elevator test", the servo which is connected to the elevators by wire moves across its range of motion back and forth pulling the elevators into different positions. 

In between the tests, the LCD screen is displaying information and the status of the tests. 

All of this code is inserted inside of a function that polls the given class Web API. While the API responds with "FALSE", the plane is in default mode. However, when the API responds with "TRUE", the plane take-off story starts. It takes about a minute to complete the whole story. 

## Enclosure

The enclosure for this project was a foam plane. I had to cut out sections to insert the stepper motor and servos. Also, I had to connect the servo to the elevator by wire. Here are some images:   

### Technical Obstacles

This project was pretty straightforward except for the DC motor issue. I wanted the sculpture to be robust and I think the foam enclosure was very helpful in this arena as it helped protect the scultpure from destructive impacts and falls. 

Here is a video of the final animation: https://youtu.be/mVZthakq6F8


## In Conclusion

This was an incredibly fun project. I was pretty happy with my final project. It was a fun kinetic sculpture that worked consistently without much need for interference or fix-ups. I'll call that a win.

