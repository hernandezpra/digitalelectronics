# Ricardo Hernandez Digital Electronics
IxD Digital Electronics

# Week 2: Thursday, February 1, 2018

Sensing Color: https://www.allaboutcircuits.com/projects/how-to-sense-color-with-an-arduino/

This project uses photoresistors and phototransistors to sense different colors. The idea would be very useful to sort color inputs and change the date into a variety of outputs.

Here is a project that shows a machine that sorts candy by color: https://www.youtube.com/watch?v=H7HTQai7Wwg
This project uses RGB sensors, IR distance sensors, and motors to sort the color.

Background of Idea: How do you help a blind person navigate a buffet line by helping them identify the contents of the food trays? 

# Week 3: Thursday, February 8, 2018

### Concept
The device I am proposing is an assitive technology that allows blind individuals to recogize food based on detecting color. The context would be a buffet where the individual canot different between the types of food available. Depending on the complexity, it would be interesting to make this project a multi-wearable accessory that also detects distance while in line. It would be interesting to create a device that augments more than one human ability; in this case, sensing distance and perhaps color/light. 

Help blind individuals navigate a buffet line by helping them identify the contents of the food trays while also sensing the distance around the individual. 
  Will need to use some sort of distance sensor: most likely IR technology.
  Will need a color sensor. 

### Concept Sketch

![concept sketch1](https://user-images.githubusercontent.com/35578913/35985586-d3bbc496-0cab-11e8-9e0e-c9487e3cf2ac.jpg)

### Schematic References

Color Sensor
<img width="795" alt="screen shot 2018-02-08 at 9 20 58 am" src="https://user-images.githubusercontent.com/35578913/35987791-8c9f5f36-0cb1-11e8-9041-d18408146e0f.png">

### V1.0: Ultrasonic, IR, Vibration 

![img_8122](https://user-images.githubusercontent.com/35578913/35987931-f8328610-0cb1-11e8-8905-6076483f7250.JPG)

![sku_416860_1](https://user-images.githubusercontent.com/35578913/37172416-8ec72378-22c5-11e8-827d-2b3ce4d79da2.jpg)

![ir sensor](https://user-images.githubusercontent.com/35578913/37172440-9fc946ba-22c5-11e8-985e-4e6726af4671.jpg)

I began testing my idea with a simple ultrasonic sensor with a vibration output to understand different modes of using haptic feedback. After testing this prototype I realized that the ultrasonic sensor does not work very well with soft materials so I changed it to a IR sensor. This allowed for more accurate measurements, however, I had to map out the readings from the sensor to match metric scale data. 

### V1.1: AdaFruit 1356 Color Sensor

![adafruit color sensor](https://user-images.githubusercontent.com/35578913/37172676-545bf226-22c6-11e8-9aaf-1ebd7f7194a6.jpg)

I began experimenting with the AdaFruit 1356 Color Sensor and practiced soldering with it. However, I quickly learned that I am not good a soldering small companents and ended up burning the metal off of the sensor. Who thought that was even possible? Regardless, I went ahead and ordered a different color sensor that came with the male parts instead of requiring soldering. 

### V2.0: TCS3200 Color Sensor (Midterm)

![img_8331](https://user-images.githubusercontent.com/35578913/37173064-72ed9004-22c7-11e8-80f0-6c27bbbabfe7.jpg)

![img_8332](https://user-images.githubusercontent.com/35578913/37173129-9aa45808-22c7-11e8-94e8-0ae8582ccc8a.JPG)

![img_8333](https://user-images.githubusercontent.com/35578913/37173148-a7b1ce4a-22c7-11e8-8f94-a971ae922c25.JPG)

![img_8334](https://user-images.githubusercontent.com/35578913/37173168-b6f3bb02-22c7-11e8-9adf-7a695a5f9021.JPG)

For the midterm presentation I assembled a color sensor with an LED output. Whenever the sensor recognized RGB, the LEDs would light up accordingly. However, the red sensor was not working so I need to troubleshoot that. In addition, I wanted to connect a piezo as an output for the color sensor. If the sensor were to read a red color then the piezo would go off, but only if it were reading red and not any other color. This would allow for different outputs and readings of food color and the outputs could inform the user on what food their looking at. 

