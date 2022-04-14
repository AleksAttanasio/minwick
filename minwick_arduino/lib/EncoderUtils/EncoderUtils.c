#define MAX_ENCODER_VALUE 128
#define MIN_ENCODER_VALUE 0
#define ENCODER_STEP 3

const int ENCODER_PIN_BUTTON = 8;
const int ENCODER_PIN_DT = 3;
const int ENCODER_PIN_CLK = 2;


volatile int lastEncoded = 0;
volatile long encoderValue = 0;
long lastencoderValue = 0;
int lastMSB = 0;
int lastLSB = 0;


void updateEncoder(int *state, int *irrigationRateValue, int *waterAmountValue) {
  int MSB = digitalRead(ENCODER_PIN_DT); //MSB = most significant bit
  int LSB = digitalRead(ENCODER_PIN_CLK); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  // TODO organize as function
  switch (*state){
    case 1:
      if (*irrigationRateValue < MIN_ENCODER_VALUE) *irrigationRateValue = MIN_ENCODER_VALUE;
      if (*irrigationRateValue > MAX_ENCODER_VALUE) *irrigationRateValue = MAX_ENCODER_VALUE;
      if (sum == 0b1000) *irrigationRateValue = *irrigationRateValue + ENCODER_STEP;
      if (sum == 0b0010) *irrigationRateValue = *irrigationRateValue - ENCODER_STEP;
      break;

    case 2:
      if (*waterAmountValue < MIN_ENCODER_VALUE) *waterAmountValue = MIN_ENCODER_VALUE;
      if (*waterAmountValue > MAX_ENCODER_VALUE) *waterAmountValue = MAX_ENCODER_VALUE;
      if (sum == 0b1000) *waterAmountValue = *waterAmountValue + ENCODER_STEP;
      if (sum == 0b0010) *waterAmountValue = *waterAmountValue - ENCODER_STEP;
      break;

    default:
      break;
  }
  
  lastEncoded = encoded; //store this value for next time
}