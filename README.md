




## 🧪 Calibração do Sensor MQ-135

O processo de calibração inicial do sensor requer um período de aquecimento
de aproximadamente 48 horas.

Para documentar esse processo, foi desenvolvida uma implementação específica
com display LCD e contador regressivo, disponível na branch:

🔗 `feature/lcd-calibration-timer`




🔌 Ligação dos sensores à fonte 5 V via MOSFET

Objetivo do circuito

Alimentar 2 sensores MQ-135 com fonte externa de 5 V

Arduino não fornece corrente dos sensores, apenas controla quando ligar/desligar via MOSFET

LED indicador acende enquanto sensores estão aquecendo

LCD I2C mostra o contador regressivo de 48 h

2️⃣ Componentes e pinos
Componente	Pino/Conexão	Observações
MQ-135 #1	VCC → Fonte 5 V	Paralelo com MQ-135 #2
MQ-135 #2	VCC → Fonte 5 V	Paralelo com MQ-135 #1
MQ-135 #1 e #2	GND → DRAIN MOSFET	Corte do GND via MOSFET
MOSFET IRF4Z34N	GATE → Arduino D7	Resistor 220Ω em série
MOSFET IRF4Z34N	SOURCE → GND fonte externa	GND comum com Arduino
LED aquecimento	Anodo → Arduino D8	Resistor 220Ω em série
LED aquecimento	Catodo → GND Arduino	Indica aquecimento ativo
LCD I2C	SDA → Arduino SDA	A4 no UNO
LCD I2C	SCL → Arduino SCL	A5 no UNO
LCD I2C	VCC → Arduino 5V	
LCD I2C	GND → Arduino GND	
3️⃣ Explicação detalhada do fluxo de corrente

Fonte 5 V externa: alimenta o VCC dos dois MQ-135

MOSFET em low-side:

DRAIN conecta aos GNDs dos sensores

SOURCE conecta ao GND da fonte externa (que está comum com Arduino)

Gate controlado pelo Arduino (D7) → quando HIGH, MOSFET liga e sensores recebem GND → sensores aquecem

Quando LOW → MOSFET corta GND → sensores desligam

LED indicador de aquecimento:

Conectado ao Arduino (D8 + resistor)

Acende enquanto os sensores estão ligados (D7 HIGH)

LCD I2C: exibe o tempo restante de 48 h

4️⃣ Visualização textual do circuito
Fonte 5V externa
   +-------------------------------+
   |                               |
   |                               |
 MQ-135 #1 VCC                  MQ-135 #2 VCC
   |                               |
   +-----> DRAIN MOSFET IRF4Z34N ----+
SOURCE MOSFET ------------------- GND fonte externa
GND fonte externa ---------------- GND Arduino (comum)

Arduino UNO:
  D7  ---> 220Ω ---> Gate MOSFET IRF4Z34N
  Gate MOSFET --- 10kΩ ---> GND (pull-down)

  D8  ---> 220Ω ---> LED indicador de aquecimento ---> GND Arduino

LCD I2C:
  SDA ---> Arduino A4
  SCL ---> Arduino A5
  VCC ---> Arduino 5V
  GND ---> Arduino GND

5️⃣ Como o circuito funciona na prática

Quando o Arduino liga:

MOSFET D7 HIGH → sensores recebem GND → começam a aquecer

LED aceso → indica “calibração em andamento”

LCD mostra 48:00:00 e começa contagem regressiva

Durante a calibração:

Contador decresce segundo a segundo

LED permanece aceso

MOSFET mantém os sensores ligados

Após 48 horas:

Contador chega a 0

Arduino coloca D7 LOW → MOSFET desliga → sensores desligados

LED apaga → indica fim do aquecimento

LCD mostra mensagem “Calibracao OK / Sensor pronto”






### Controle de Alimentação de Sensores MQ-135

Os sensores são alimentados por uma fonte externa de 5 V (carregador de celular). 
O Arduino atua apenas como chave, controlando um MOSFET IRF4Z34N que liga ou desliga
a alimentação dos sensores de acordo com o timer de 48 horas.

Um LED indica visualmente quando os sensores estão em aquecimento.