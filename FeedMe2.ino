#include <Servo.h>
#include <LiquidCrystal_I2C.h> // Alterado para usar a biblioteca I2C
#include "HX711.h"

// Definições dos pinos
#define DOUT  6
#define CLK   7

Servo servoMotor;

// Definições do LCD
#define endereco  0x27 // Endereço do LCD I2C
#define colunas   16
#define linhas    2

LiquidCrystal_I2C lcd(endereco, colunas, linhas); // Inicialização do LCD

HX711 balanca;

// Variáveis
float peso = 0;
int anguloServo = 0;  // Variável para armazenar o ângulo do servo
float fatorCalibracao = -62 ; // Ajuste este valor conforme a calibração

void setup() {
  // Inicializa a comunicação serial e periféricos
  Serial.begin(9600);
  lcd.init();       // Inicializa a comunicação com o módulo
  lcd.backlight();  // Liga a iluminação do display
  lcd.clear();      // Limpa o display

  // Configura o servo e a balança
  servoMotor.attach(9);  
  balanca.begin(DOUT, CLK);
  balanca.set_scale(fatorCalibracao); // Define o fator de calibração
  balanca.tare(0); // Zera a balança

  lcd.setCursor(0, 0);
  lcd.print("   -=FeedMe=-  ");
  delay(3000);
  lcd.clear();

  Serial.println("Digite 'D' para abrir, 'P' para fechar e 'S' para mostrar peso.");
}

void loop() {
  // Leitura do comando via Serial (IDE do Arduino)
  if (Serial.available()) {
    char comando = Serial.read();
    
    if (comando == 'D' || comando == 'd') {
      // Abrir a porta (servo para 90 graus)
      anguloServo = 45;  // Atualiza a variável com o novo ângulo
      servoMotor.write(anguloServo);  // Move o servo para 90 graus
      lcd.setCursor(0, 1);
      lcd.print("aberta   ");
      Serial.println("Porta aberta");
    } else if (comando == 'P' || comando == 'p') {
      // Fechar a porta (servo para 0 graus)
      anguloServo = 0;  // Atualiza a variável com o novo ângulo
      servoMotor.write(anguloServo);  // Move o servo para 0 graus
      lcd.setCursor(0, 1);
      lcd.print("fechada  ");
      Serial.println("Porta fechada");
    } else if (comando == 'S' || comando == 's') {
      // Leitura do peso
      if (balanca.is_ready()) {
        peso = balanca.get_units(); // Leitura do peso
        lcd.setCursor(0, 0);
        lcd.print("Peso: ");
        lcd.print(peso); // Imprime o peso
        lcd.print(" kg");

        // Imprime o peso no Monitor Serial
        Serial.print("Peso: ");
        Serial.print(peso); // Imprime o peso no Monitor Serial
        Serial.println(" kg");
      } else {
        lcd.setCursor(0, 0);
        lcd.print("Erro balanca");
        Serial.println("Erro: balança não pronta");
      }
    }
    
    // Atualiza o ângulo do servo no LCD
    lcd.setCursor(0, 1);
    lcd.print("Grau: ");
    lcd.print(anguloServo); // Imprime o ângulo do servo no LCD
  }

  delay(500);  // Atraso para evitar atualização excessiva
}
