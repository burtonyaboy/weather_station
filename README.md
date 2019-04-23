# Weather Station Project

Arduino code listens to various sensors and transmits data via NRF24L01+

Rasberry Pi listens on its own tranceiver and writes data to JSON file

Webserver serves JSON file when requested, simple webpage displays data for convenience

Android app requests JSON file from webserver
