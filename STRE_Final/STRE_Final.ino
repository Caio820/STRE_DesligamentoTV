#include <IRremote.h>
unsigned int powerIRout[] = {4500,4450,650,1600,600,1650,550,1650,600,500,600,550,550,550,550,550,550,550,600,1600,650,1600,600,1650,600,
                              500,550,550,550,550,600,550,500,600,550,550,550,1650,650,500,550,550,550,550,550,600,500,600,500,600,500,
                              1700,650,500,500,1700,600,1600,650,1600,600,1600,650,1600,600,1600,650};
IRsend irsend;
int led = 3;
int pinopir = 4;
int acionamento;
int vezes;
long tempoAnterior = 0;                                                    //Variável de controle do tempo
long intervalo = 180000;                                                   //Tempo em ms do intervalo a ser executado

void setup() {
  pinMode(led, OUTPUT);
  pinMode(pinopir, INPUT);
  Serial.begin(9600);
}

void loop() { 
  unsigned long tempoAtual = millis();                                     //Tempo atual em ms
  acionamento = digitalRead(pinopir);                                      //Ler o sensor e manda o resultado para a variável
  Serial.println(acionamento);                                             //Saída para verificar o estado do sensor pelo monitor   
  
  if (acionamento == 1){                                                   //Se verificar algum movimento
    delay(5000);                                                           //Esperar 5 segundos, que é 0 tempo que o sensor sai do estado HIGH(1) para o LOW(0)
    acionamento = digitalRead(pinopir);                                    //Realiza uma nova leitura
    while(acionamento != 1 && (tempoAtual - tempoAnterior > intervalo)){   //Enquanto não verificar nenhum movimento e o tempo for menor do que 3 minutos(180000 ms)
      tempoAnterior = tempoAtual;                                          //Salva o tempo atual
      acionamento = digitalRead(pinopir);                                  //Realiza uma nova leitura
    }
    liga_desliga();                                                        //Chama o método para desligar a TV
  }
}

void liga_desliga(){
  Serial.println("Enviando comando");
  irsend.sendRaw(powerIRout, 68, 38);    
}