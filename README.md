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

