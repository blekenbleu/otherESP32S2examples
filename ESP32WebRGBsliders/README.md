## ESP32WebRGBsliders
  Based on [ESP32_WebRGB_ColorPicker](../ESP32_WebRGB_ColorPicker) with HTML motivated by
  [RANDOM NERD TUTORIALS](https://randomnerdtutorials.com/esp32-async-web-server-espasyncwebserver-library/)  
  .. thanks to `xmlhttprequest` hint from @sierses   

This sketch makes available HTML which, when loaded by a browser, is not reloaded between slider changes.  
Consequently, resulting WS2812 color is not fully determined until after the first 3 sliders have been set.  
