/* Processing code */

import processing.serial.*;

Serial myPort;        // The serial port

int[] val = new int[64];

void setup () {
  // set the window size:
  size(800, 800);

  String portName = "COM6";  // Set your port correctly
  myPort = new Serial(this, portName, 115200);
  
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');

  // set inital background:
  background(255);
  rect(0, 0, 800, 800);

  // set stroke line color to red.
  stroke(255,0,0);
  
  //delay for arduino serial reboot.
  delay(2000);
}

void draw () {
    //Clear background for re-drawing.
    background(255);

    //Draw stroke for each frequency 
    for (int i =0; i<64; i++){
      line(i * 5 + 1, height, i * 5 + 1, height - val[i] * 4);
    }
}


void serialEvent (Serial myPort) {
  try{
    
      //Create buffer for data saving
      byte[] inByte = new byte[200];
      
      //Put data into buffer
      myPort.readBytesUntil('\n',inByte);
      
      // convert to an int and map to the screen height:
      for(int i = 0; i<64; i++){
       val[i] = int(inByte[i]);      
      }

  }catch(Exception e){
    println("Err");
  }
}



// 출처: https://geronimob.tistory.com/27 [Geronimo]