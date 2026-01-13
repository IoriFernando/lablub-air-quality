# 🔌 Controle de Alimentação e Aquecimento dos Sensores MQ-135 via MOSFET

## 1. Visão Geral do Sistema

Este circuito tem como objetivo controlar o processo de aquecimento (*burn-in*) de **dois sensores MQ-135**, utilizando uma **fonte externa de 5 V** e um **Arduino Uno** apenas como unidade de controle lógico.

O Arduino **não fornece corrente diretamente aos sensores**, evitando sobrecarga da placa. Em vez disso, ele controla um **MOSFET N-channel (IRF4Z34N)** configurado como chave eletrônica em **low-side**, permitindo ligar e desligar a alimentação dos sensores conforme um **temporizador de 48 horas**.

Durante o aquecimento:

- 🔴 Um **LED indicador** sinaliza que os sensores estão ativos  
- 🖥️ Um **display LCD 16×2 com interface I2C** exibe a contagem regressiva do tempo restante  

---

## 2. Objetivos do Circuito

- Alimentar **dois sensores MQ-135** com uma fonte externa de 5 V  
- Isolar o Arduino da corrente consumida pelos sensores  
- Controlar o liga/desliga dos sensores via **MOSFET**  
- Indicar visualmente o estado de aquecimento com **LED**  
- Exibir o tempo de calibração (**48 horas**) em um **LCD I2C**  

---

## 3. Componentes Utilizados

| Componente | Função |
|----------|------|
| Arduino Uno | Controle lógico e temporização |
| 2× Sensor MQ-135 | Sensores de qualidade do ar |
| MOSFET IRF4Z34N | Chave eletrônica (low-side) |
| Fonte externa 5 V | Alimentação dos sensores |
| LCD 16×2 com I2C | Exibição do temporizador |
| LED + resistor 220 Ω | Indicador de aquecimento |
| Resistor 10 kΩ | Pull-down no gate do MOSFET |
| Resistor 220 Ω | Proteção do gate do MOSFET |

---

## 4. Conexões Elétricas

### 4.1 Sensores MQ-135

| Sensor | Conexão | Destino |
|------|-------|--------|
| MQ-135 #1 | VCC | +5 V da fonte externa |
| MQ-135 #2 | VCC | +5 V da fonte externa |
| MQ-135 #1 e #2 | GND | DRAIN do MOSFET |

> Os dois sensores estão conectados **em paralelo** na alimentação.

---

### 4.2 MOSFET IRF4Z34N (Low-Side Switch)

| Pino MOSFET | Conexão |
|-----------|--------|
| GATE | Arduino D7 (via resistor 220 Ω) |
| SOURCE | GND da fonte externa |
| DRAIN | GND dos sensores MQ-135 |
| Gate–GND | Resistor 10 kΩ (pull-down) |

📌 **Observação:**  
O **GND da fonte externa é comum ao GND do Arduino**, garantindo referência elétrica correta.

---

### 4.3 LED Indicador de Aquecimento

| LED | Conexão |
|----|--------|
| Ânodo | Arduino D8 (via resistor 220 Ω) |
| Cátodo | GND do Arduino |

---

### 4.4 Display LCD I2C

| LCD I2C | Arduino Uno |
|------|-------------|
| SDA | A4 |
| SCL | A5 |
| VCC | 5 V |
| GND | GND |

---

## 5. Diagrama Textual do Circuito

## 6. Funcionamento do Sistema

### 6.1 Inicialização

Ao energizar o sistema:

- O Arduino configura o pino **D7** como saída  
- O MOSFET é ativado (**D7 = HIGH**)  
- Os sensores passam a receber GND e iniciam o aquecimento  
- O LED indicador acende  
- O LCD exibe **48:00:00** e inicia a contagem regressiva  

---

### 6.2 Durante o Aquecimento

- O temporizador decrementa **segundo a segundo**  
- MOSFET permanece ligado  
- Sensores continuam aquecendo  
- LED permanece aceso  
- LCD atualiza o tempo restante  

---

### 6.3 Final da Calibração

Após 48 horas:

- O contador chega a zero  
- Arduino coloca **D7 em LOW**  
- MOSFET desliga → sensores são desligados  
- LED apaga  
- LCD exibe a mensagem:

Calibracao OK
Sensor pronto

yaml
Copiar código

---

## 7. Considerações Técnicas Importantes

- O uso de **fonte externa** evita sobrecarga do regulador do Arduino  
- O controle em **low-side** simplifica o acionamento do MOSFET  
- O resistor **pull-down** garante que o MOSFET permaneça desligado durante reset  
- O sistema permite repetir o processo de calibração sempre que necessário  

---