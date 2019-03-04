# Weather Station Project

Ever make a school project? 
Ever get tired of getting mildly innaccurate weather stats due to the fact that you don't own your own personal weather station? 
Ever write a README and think wtf am I writing this for? 
No one's gonna read it? 
Lol?

This project contains an Android app written with Android Studio. 
All it does is do a GET to my lil webserver every once and a while,
grabbbing a JSON file with weather data. Safe to say it's gonna be 
the next Facebook.

The webserver is pretty cool, because it actually receives data from
the weather station as well as serving pages. Oh yeah, it only serves 2
pages, index.html and data.json. Why? Why? Bc making it cool would be a 
severe waste of my time. The webserver is built using Flask so you know it's 
HOT. BTW it's all on a raspberry pi for blog cred.

The weather station is driven by a poor Arduino Mini that has to listen to a 
pressure sensor, air speed sensor, temp sensor, air humidity sensor, soil humidity
sensor, and it even has a fricken' rain guage. Plus it sends stuff over a NRF24L01+
to the Pi, so you don't need to run flash drives from the station to your PC no more.
Yeah it's also got a solar panel so you can charge it wirelessly with the sun.

If you want more project deets then maybe I'll post it lol depends on if I have time near
finals which I probably wont so dont expect it!...

Thnks by
