#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_NeoMatrix.h>
#include <WS2812Buffer.h>

#ifdef ESP32
#define matrixpin 23
#elif defined(ESP8266)
#define matrixpin D2
#else
#define matrixpin 6
#endif

const int height = 8;
const int width = 32;

Adafruit_NeoMatrix matrix(width, height, matrixpin, 
                          NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                          NEO_GRB + NEO_KHZ800);


void setup()
{
  Serial.begin(57600);
  Serial.println("Setup");
  matrix.begin();
  matrix.setBrightness(40);
  matrix.clear();
}

void waveLayer(WS2812Buffer& matrix_buffer,
               const uint16_t xoffset,
               const uint8_t r, const uint8_t g, const uint8_t b,
               const uint8_t r_bg, const uint8_t g_bg, const uint8_t b_bg)
{
  const float F[] = {1, 0.7, 0.5, 0.3, 0.1, 0};
  const uint16_t nmax = sizeof(F)/sizeof(*F);
  const float rmin = r_bg, gmin = g_bg, bmin = b_bg;
  for(int x = nmax-1;x>=0;--x)
  {
    const float f = F[x];
    const uint16_t col = matrix.Color(max(rmin, float(r)*f), max(gmin, float(g)*f), max(bmin, float(b)*f));

    matrix_buffer.drawLine(xoffset+x, 0, xoffset+x+3, height, col);
    matrix_buffer.drawLine(xoffset-x, 0, xoffset-x+3, height, col);
  }
}

void textWaveLayer(WS2812Buffer& matrix_buffer,
                   const char* const text,
                   const float yoffset,
                   const uint8_t r, const uint8_t g, const uint8_t b)
{
  matrix_buffer.setTextColor(matrix.Color(100, 100, 100));
  matrix_buffer.setCursor(1, 0);
  matrix_buffer.print(text);
  for(int y=0;y<matrix_buffer.height();++y)
  {
    const float f = (1. + sin(float(y + yoffset)/float(matrix_buffer.height()*PI/180.)))/2.;
    const uint16_t col = matrix.Color(f*r, f*g, f*b);
    for(int x=0;x<matrix_buffer.width();++x)
    {
      if(matrix_buffer.getOpacity(x, y) != 0)
        matrix_buffer.writePixel(x, y, col);
    }
  }
}

void doubleWave(const char* const text,
                const uint8_t r1, const uint8_t g1, const uint8_t b1,
                const uint8_t r2, const uint8_t g2, const uint8_t b2,
                const uint8_t r3, const uint8_t g3, const uint8_t b3,
                const float yspeed = 0.03)
{
  static uint8_t xoffset = 0;
  static float yoffset = 0;
  WS2812Buffer matrix_buffer1(width, height);
  WS2812Buffer matrix_buffer2(width, height);

  matrix_buffer1.fillScreen(matrix.Color(r2, g2, b2));
  waveLayer(matrix_buffer1, xoffset, r1, g1, b1, r2, g2, b2);
  textWaveLayer(matrix_buffer2, text, yoffset, r3, g3, b3);
  matrix_buffer1.applyLayer(matrix_buffer2, WS2812Buffer::OVERWRITE);
  matrix_buffer1.writeToMatrix(matrix);
  //matrix.fillScreen(matrix.Color(r1, g1, b1));
  matrix.show();

  ++xoffset;
  if(xoffset>=matrix.width()) 
    xoffset = 0;
  yoffset += yspeed;
}

void loop()
{
  static uint16_t step = 0;
  if(step < 100)
  {
    doubleWave("TEST",
                200, 40, 160,
                40, 8, 40,
                70, 250, 250,
                0.03);
  }
  else if(step < 200)
  {
    doubleWave("TEST",
                70, 250, 250,
                14, 50, 50,
                200, 40, 160,
                0.03);
  }
  else
  {
    step = 0;
  }
  delay(50);
  ++step;
}