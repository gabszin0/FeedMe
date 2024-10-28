# Projeto Arduino com Servo, LCD e Célula de Carga 🛠️📟

Este código permite controlar um servo-motor e exibir o peso medido por uma célula de carga em um display LCD I2C. Além disso, você pode enviar comandos pelo Monitor Serial para abrir/fechar uma porta controlada pelo servo e visualizar o peso medido! 🎉

## Funcionalidades do Projeto

1. **Controle do Servo-Motor** ⚙️: Use comandos para ajustar a posição do servo (abrir/fechar).
2. **Display LCD I2C** 📟: Exibe o peso atual e o ângulo do servo.
3. **Leitura de Peso** ⚖️: Mede o peso utilizando uma célula de carga e o módulo HX711.
4. **Comandos pelo Monitor Serial** 💻: Envie comandos via Serial para controlar o sistema.

## Estrutura do Código

### Bibliotecas e Definições 🧩

- `Servo.h` — Controle do servo-motor.
- `LiquidCrystal_I2C.h` — Controle do display LCD com comunicação I2C.
- `HX711.h` — Interface com a célula de carga.

### Pinos Utilizados 🔌

- **DOUT** e **CLK** da célula de carga conectados aos pinos 6 e 7.
- **Servo Motor** conectado ao pino 9.
- **Endereço LCD I2C**: `0x27`.

## Variáveis Importantes 📝

- **peso**: armazena o valor de peso medido pela célula de carga.
- **anguloServo**: registra o ângulo atual do servo-motor.
- **fatorCalibracao**: ajuste para calibrar a balança (atualmente em `-62`).

## Comandos Disponíveis 💻

- **`D` ou `d`** — Abre a porta (ajusta o servo para 45 graus).
- **`P` ou `p`** — Fecha a porta (ajusta o servo para 0 graus).
- **`S` ou `s`** — Mostra o peso atual no display LCD e no Monitor Serial.

## Funcionamento do Código

1. **Setup Inicial** ⚙️:
   - Inicia o Serial, o display LCD e o servo-motor.
   - Configura a balança com o fator de calibração e tare (zera a balança).
   - Exibe uma mensagem de boas-vindas no LCD.

2. **Loop Principal** 🔄:
   - Lê os comandos do Monitor Serial.
   - Ajusta a posição do servo ou exibe o peso no LCD e no Serial, dependendo do comando enviado.
   - Mostra o ângulo atual do servo no LCD.

### Exemplo de Uso 📝

1. **Para abrir a porta**: Envie o comando `D` pelo Monitor Serial.
2. **Para fechar a porta**: Envie o comando `P` pelo Monitor Serial.
3. **Para ver o peso**: Envie o comando `S` pelo Monitor Serial.

## Código Completo

```cpp
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
