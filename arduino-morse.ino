#define LED 8
#define dot_length 200

struct Character {
  char letter;
  char morse_rep[6];
};


Character alphabet[] = 
{
  {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
  {'F', "..-."}, {'G', "-.."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
  {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
  {'P', ".--."}, {'R', ".-."}, {'S', "..."}, {'T', "-"}, {'U', "..-"},
  {'W', ".--"}, {'V', "...-"}, {'X', "-..-"}, {'Y', "-.-"}, {'Z', "--.."},
  {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"}, {'5', "....."},
  {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."}, {'0', "-----"},
  {' ', " "}, {NULL, NULL}
};

char toupper(char letter) {
  if (letter >= 'a' && letter <= 'z') return (letter - ('a' - 'A')); // return uppercase
  if (letter >= 'A' && letter <= 'Z') return letter;
  if (letter >= '0' && letter <= '9') return letter;
  if (letter == ' ') return letter;
  return NULL;
}

int find_letter(char l) {
  int i = 0;
  char letter = toupper(l);
  if (letter == NULL) return -1;
  while (alphabet[i].letter != NULL) {
    if (alphabet[i].letter == letter) {
      return i;
    }
    i++;
  }
  return -1;
}

void blink_LED(char c){
  if(c == '-'){
    digitalWrite(LED, HIGH);
    delay(3 * dot_length);
    digitalWrite(LED, LOW);
  }
  if(c == '.'){
    digitalWrite(LED, HIGH);
    delay(dot_length);
    digitalWrite(LED, LOW);
  }
  delay(3 * dot_length);
}

void print_letter(char letter) {
  int index = find_letter(letter);
  if (index == -1) {
    return;;
  }
  int i = 0;
  while (alphabet[index].morse_rep[i] != '\0') {
    Serial.println(alphabet[index].morse_rep[i]); 
    blink_LED(alphabet[index].morse_rep[i]);
    i++;
  }
  //printf("\t%c\n", alphabet[index].letter);
  delay(7 * dot_length);
}


void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  String text;
  if(Serial.available() > 0){
    text = Serial.readStringUntil('\n');
    int i = 0;
    while (text[i] != '\0') {
      print_letter(text[i]);
      i++;
    }
  }
}
