
#include "FFT.h" // include the library
#include "FFT_signal.h"


void setup() {
  Serial.begin(115200); // use the serial port
  char print_buf[300];
  fft_config_t *real_fft_plan = fft_init(FFT_N, FFT_REAL, FFT_FORWARD, fft_input, fft_output);

  for (int k = 0 ; k < FFT_N ; k++)
    real_fft_plan->input[k] = (float)fft_signal[k];

  long int t1 = micros();
  // Execute transformation
  fft_execute(real_fft_plan);
  
  // Print the output
  for (int k = 1 ; k < real_fft_plan->size / 2 ; k++)
  {
    /*The real part of a magnitude at a frequency is followed by the corresponding imaginary part in the output*/
    float mag = sqrt(pow(real_fft_plan->output[2*k],2) + pow(real_fft_plan->output[2*k+1],2))/1;
    float freq = k*1.0/TOTAL_TIME;
    sprintf(print_buf,"%f Hz : %f", freq, mag);
    Serial.println(print_buf);
    if(mag > max_magnitude)
    {
        max_magnitude = mag;
        fundamental_freq = freq;
    }
  }
  long int t2 = micros();
  
  Serial.println();
  /*Multiply the magnitude of the DC component with (1/FFT_N) to obtain the DC component*/
  sprintf(print_buf,"DC component : %f g\n", (real_fft_plan->output[0])/FFT_N);  // DC is at [0]
  Serial.println(print_buf);

  /*Multiply the magnitude at all other frequencies with (2/FFT_N) to obtain the amplitude at that frequency*/
  sprintf(print_buf,"Fundamental Freq : %f Hz\t Mag: %f g\n", fundamental_freq, (max_magnitude)*2/FFT_N);  // N/2 is real and stored at [1]
  Serial.println(print_buf);

  Serial.print("Time taken: ");Serial.print((t2-t1)*1.0/1000);Serial.println(" milliseconds!");
  
  // Clean up at the end to free the memory allocated
  fft_destroy(real_fft_plan);
  
}

void loop() {
  
}
