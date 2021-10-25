import processing.serial.*;

Serial myPort;        // The serial port

int[] val = new int[128];

void setup () {
  // set the window size:
  size(800, 800);

  String portName = "COM6";
  myPort = new Serial(this, portName, 115200);

  myPort.bufferUntil('\n');

  background(255);
  rect(0, 0, 800, 800);
  stroke(255,0,0);
  noLoop();
  delay(2000);
}

void draw () {
    background(255);

    for (int i =0; i<128; i++){
      line(i*5 + 1, height, i * 5 + 1, height - val[i] * 4);
    }
}


void serialEvent (Serial myPort) {
  try{
      byte[] inByte = new byte[200];
      
      myPort.readBytesUntil('\n',inByte);
      
        // convert to an int and map to the screen height:
        for(int i = 0; i<128; i++){
         val[i] = int(inByte[i]);      
        }
        redraw();

  }catch(Exception e){
    println("Err");
  }
}


// 출처: https://geronimob.tistory.com/27 [Geronimo]