



int DELAY_LENGTH = 200;                                     //Time for delay
int DIT = DELAY_LENGTH;                                     //Time delay for DIT
int DAH = 3 * DELAY_LENGTH;                                 //Time delay for DAH
int CHAR_SPACE = DELAY_LENGTH;                              //Time delay between DIT and DAH within Character
int LETTER_SPACE = 3 * DELAY_LENGTH - CHAR_SPACE;           //Time delay between letters - minus character space as this will always occur in code
int WORD_SPACE = 7 * DELAY_LENGTH - LETTER_SPACE;           //Time delay between words - minus letter space as this will always occur in the code
int LED = D2;                                               //LED PIN location
int BUTTON_PIN = D3;                                        //BUTTON PIN location


char* characters = "abcdefghijklmnopqrstuvwxyz0123456789";  //List of characters availible for use in word

char* morsemappings[] = {                                        //Array of DITs and DAHs for each character \0 is the null character
    ".-\0",     //a
    "-...\0",   //b
    "-.-.\0",   //c
    "-..\0",    //d
    ".\0",      //e
    "..-.\0",   //f
    "--.\0",    //g
    "....\0",   //h
    "..\0",     //i
    ".---\0",   //j
    "-.-\0",    //k
    ".-..\0",   //l
    "--\0",     //m
    "-.\0",     //n
    "---\0",    //o
    ".--.\0",   //p
    "--.-\0",   //q
    ".-.\0",    //r
    "...\0",    //s
    "-\0",      //t
    "..-\0",    //u
    "...-\0",   //v
    ".--\0",    //w
    "-..-\0",   //x
    "-.--\0",   //y
    "--..\0",   //z
    "-----\0",  //0
    ".----\0",  //1
    "..---\0",  //2
    "...--\0",  //3
    "....-\0",  //4
    ".....\0",  //5
    "-....\0",  //6
    "--...\0",  //7
    "---..\0",  //8
    "----.\0",  //9
};



char* message = "Jerome\0";                             //Message to send to LED in Morse Code


void setup() {

pinMode(LED, OUTPUT);                                   //Setup for LED Output
pinMode(BUTTON_PIN, INPUT_PULLUP);                      //Setup for BUTTON_PIN input

}

void loop() {


    if (digitalRead(BUTTON_PIN) == LOW) {               //Start Loop when button is pressed

        int size = strlen(message);                     //retrieve the string length of the message

        //loop through the message
        for (int i = 0; i < size; i++)                  //Cycle through each letter in the string message
        {
    
            const char* ch = strchr(characters, tolower(message[i]));    // Convert to lower case letters
            if (ch != NULL)                                             // If the character is not a null \0 then continue
                {
                    int index = (int)(ch - characters);                 //retrieve the index of the entered character
                    const char* morseSymbols = morsemappings[index];         //retrieve the mapping index of DITs and DAHs from the morsecode map index
                    int count = strlen(morseSymbols);                   //How many DITs and DAHs in the morsecode map

                    for (int i = 0; i < count; i++)                     //Cycle through each DIT or DAH
                        {
                            digitalWrite(LED, HIGH);                    //Turn LED On
        
                            int symbolTime;                             //Varible for if DIT or DAH delay to be used
                            char symbol = morseSymbols[i];              //Define if DIT or DAH
                            if (symbol == '.')                          //If statement to set the delay to DIT or DAH
                            symbolTime = DIT;
                            else
                            symbolTime = DAH; 
        
                            delay(symbolTime);                          //Delay by selected symbolTime DIT or DAH
                            digitalWrite(LED, LOW);                     //Turn LED Off
                            delay(CHAR_SPACE);                          //Delay between character DIT or DAH
                        }
                    delay(LETTER_SPACE);                //Delay for Space Between Letters less previous space included in space between DIT or DAH
                }
        }
        delay(WORD_SPACE);                              //Delay between words less 

    } 
    else 
    {
        digitalWrite(LED, LOW);                         //If button not pressed the LED is off
    }
}