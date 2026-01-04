# 1. Princípio Químico 
Para dominar a aplicação do MQ-135, é imperativo compreender o mecanismo de transdução subjacente, que difere radicalmente dos sensores óticos ou eletroquímicos líquidos. O MQ-135 é classificado como um sensor quimiorresistivo do tipo semicondutor de óxido metálico (MOX - Metal Oxide Semiconductor). O material sensível primário é o Dióxido de Estanho ($SnO_2$), um semicondutor do tipo-n de banda larga (gap de energia $E_g \approx 3.6 eV$).

O princípio de funcionamento baseia-se na modulação da barreira de potencial intergranular na superfície do material policristalino. Em condições normais de atmosfera limpa, o oxigénio molecular ($O_2$) do ar adsorve-se na superfície dos grãos de $SnO_2$. Dependendo da temperatura de operação, estas moléculas de oxigénio capturam eletrões livres da banda de condução do semicondutor, formando espécies iónicas adsorvidas, predominantemente $O^-$ ou $O^{2-}$ em altas temperaturas (entre 200°C e 400°C).

Quando o sensor é exposto a gases redutores (como Amônia, Vapores de Benzeno ou Álcool), ocorre uma reação de oxidação na superfície aquecida. As moléculas do gás redutor reagem com os iões de oxigénio adsorvidos, libertando os eletrões aprisionados de volta para a banda de condução do semicondutor.
## 1.1 Ar limpo
Quando o sensor está quente, mas apenas em ar limpo, o oxigênio da atmosfera gruda na superfície do Dióxido de Estanho.

- O "Roubo" de Elétrons: Esse oxigênio "rouba" elétrons do material.

- O Resultado: Como os elétrons são os transportadores de eletricidade, e eles estão presos pelo oxigênio, a corrente elétrica tem muita dificuldade de passar.

- Estado: Em ar limpo = Resistência Alta.
## 1.2 Presença de gases tóxicos
Quando gases como Amônia ($NH_3$), Álcool, Benzeno ou Fumaça (que o MQ-135 detecta) entram em contato com o sensor, uma reação química de oxirredução acontece.
- 1.As moléculas do gás reagem com o oxigênio que estava grudado na superfície.
- 2.Essa reação faz com que o oxigênio solte os elétrons de volta para o material do sensor.
- 3.Agora que os elétrons estão livres novamente, a corrente elétrica flui facilmente.
- Resultado: Com gás = Resistência Baixa.
<div align="center">
<img src="./processoQuimico.png" alt="Representação de processo químico" width="1000"/>
<br>
  <b>Figura 1:</b> Representação do Processo Químico.
</div>
<hr style="border-top: 5px dashed #8c8b8b; border-bottom: none; border-left: none; border-right: none;">

# 2. Especificações do sensor
A correta engenharia de um sistema de monitorização começa pela interpretação rigorosa das especificações fornecidas pelos fabricantes. Existem variações subtis entre os sensores produzidos pela Hanwei Electronics, Winsen Sensor e outros fabricantes genéricos, mas os parâmetros centrais permanecem consistentes.
## 2.1 Estrutura interna e materiais
- Microtubo Cerâmico ($Al_2O_3$): O núcleo do sensor é um pequeno tubo de óxido de alumínio, escolhido pela sua elevada condutividade térmica e isolamento elétrico.
- Camada Sensível ($SnO_2$): Reveste o tubo cerâmico. É uma camada porosa sinterizada que maximiza a área superficial disponível para a interação gás-sólido. A porosidade é vital para a difusão rápida dos gases, influenciando o tempo de resposta.
- Elétrodo de Medição: Fios de ouro (Au) ou platina (Pt) que conectam a camada sensível aos pinos externos, permitindo a medição da resistência.
- Aquecedor (Heater): Uma bobina de liga Níquel-Crómio (Ni-Cr) inserida dentro do tubo cerâmico. A sua função é manter o sensor na temperatura de operação ideal para a catálise das reações de superfície.
- Rede Anti-Explosão: O sensor é envolto numa malha de aço inoxidável (SUS316 100-mesh) dupla. Como o sensor opera a altas temperaturas e deteta gases inflamáveis, esta rede atua como um flashback arrestor, prevenindo que o calor interno inicie uma combustão no ambiente externo.
## 2.2 Parâmetros elétricos

<div align ="center">

|          Parâmetro         	| Símbolo 	|           Valor especificado          	|                                             Implicação                                            	|
|:--------------------------:	|:-------:	|:-------------------------------------:	|:-------------------------------------------------------------------------------------------------:	|
|    Tensão de aquecimento   	|  $V_H$  	|       $5.0V \pm 0.1V$ (AC ou DC)      	|             Define a temperatura de operação. Desvios de 0.1V alteram a sensibilidade.            	|
|     Tensão de circuito     	|  $V_C$  	|          $5.0V \pm 0.1V$ (DC)         	|             Tensão aplicada ao divisor resistivo. Máx 24V, mas usualmente 5V em MCUs.             	|
| Resistência de aquecimento 	|  $R_H$  	|  $33\Omega \pm 5\%$ (Temp. Ambiente)  	|                 Determina a corrente de aquecimento. $I = V/R \approx 150-160mA$.                 	|
|    Consumo do aquecedor    	|  $P_H$  	|              $\le 950mW$              	|               Consumo elevado. Pode sobrecarregar reguladores lineares de Arduinos.               	|
|    Resistência de carga    	|  $R_L$  	| Ajustável ($10k\Omega$ a $47k\Omega$) 	| Crítico para ajustar a tensão de saída $V_{out}$. Módulos baratos usam 1k$\Omega$ incorretamente. 	|
|    Resistência do sensor   	|  $R_s$  	|       $30k\Omega$ a $200k\Omega$      	|                    Faixa de resistência em condições de teste (100ppm $NH_3$).                    	|
|  Tempo de pré-aquecimento  	|    -    	|            > 24 a 48 Horas            	|                           Necessário para estabilização química inicial.

</div>                   

## 2.3 Curvas de sensibilidade
O MQ-135 é projetado para uma deteção de amplo espectro. As curvas de sensibilidade fornecidas nos datasheets 1 são gráficos log-log que relacionam a concentração de gás (eixo X, em ppm) com a razão de resistência $R_s/R_0$ (eixo Y).

Os gases alvo principais e os seus intervalos de deteção eficazes são:
- Amônia ($NH_3$): 10ppm - 300ppm. O sensor é altamente sensível a amônia, sendo esta frequentemente usada como gás de calibração padrão ($R_0$ definido a 100ppm de $NH_3$).
- Benzeno ($C_6H_6$): 10ppm - 1000ppm. Importante para monitorização de qualidade do ar industrial e tráfego veicular.
- Álcool (Etanol): 10ppm - 300ppm. Causa forte interferência em ambientes domésticos (uso de produtos de limpeza, perfumes).
- **Dióxido de Carbono ($CO_2$)**: 10ppm - 1000ppm (intervalo típico citado, embora o sensor responda a concentrações mais altas).

**Obs**: É fundamental esclarecer uma distinção técnica que muitas vezes confunde iniciantes. O MQ-135 não é um sensor seletivo de $CO_2$. A molécula de $CO_2$ é quimicamente muito estável e não atua como um agente redutor forte na superfície do $SnO_2$ da mesma forma que o $CO$ ou $NH_3$. A sensibilidade ao $CO_2$ reportada no datasheet é muito menor (curva mais plana) do que para outros gases.11
Muitas aplicações usam o MQ-135 para inferir níveis de $CO_2$ baseando-se na correlação entre a ocupação humana (que gera $CO_2$, humidade e outros VOCs) e a resistência do sensor. Esta medida é frequentemente chamada de $eCO_2$ (CO2 estimado). Para medições precisas e absolutas de $CO_2$, sensores NDIR (Infravermelho Não Dispersivo) como o MH-Z19 ou SCD30 são superiores, pois contam fisicamente as moléculas através da absorção de luz.13 O uso do MQ-135 para $CO_2$ deve ser encarado como uma indicação qualitativa de "ar viciado" e não como um instrumento quantitativo de precisão laboratorial.
#  3. Engenharia de Hardware e Conexões
A transição da teoria para a prática envolve a integração do sensor num circuito eletrónico capaz de converter a variação de resistência em dados digitais. A maioria dos utilizadores opta por módulos "breakout" pré-montados, mas estes apresentam falhas de design críticas que exigem correção.
## 3.1 O circuito divisor de tensões
O método padrão para ler o MQ-135 é através de um divisor de tensão. O sensor atua como o resistor superior ($R_s$) e um resistor de carga ($R_L$) atua como o resistor inferior ligado ao terra (GND). A tensão é medida no ponto de junção entre os dois.

<div align="center">
<img src="./circuitoDivisorDeTensao.png" alt="Divisor de tensão" width="1000"/>
<br>
  <b>Figura 2:</b> Circuito divisor de tensões.
</div>

- VCC (5V) $\rightarrow$ Pino A do Sensor
- Pino B do Sensor $\rightarrow$ Pino A0 do Arduino E Resistor $R_L$
- Outra ponta do $R_L$ $\rightarrow$ GND
- Aquecedor (Pinos H) $\rightarrow$ VCC e GND (independente da polaridade).

A tensão de saída analógica ($V_{out}$) lida pelo ADC do Arduino é dada pela lei de Ohm:$$V_{out} = V_c \times \frac{R_L}{R_s + R_L}$$
Desta equação, o microcontrolador deve calcular a resistência instantânea do sensor ($R_s$), que é o parâmetro físico real que varia com o gás:$$R_s = R_L \times \left( \frac{V_c}{V_{out}} - 1 \right)$$

Onde $V_c$ é a tensão de alimentação (assumida 5.0V, mas idealmente medida com precisão para reduzir erros) e $V_{out}$ é a tensão convertida da leitura do ADC (0 a 1023 para 10-bit).

Uma vasta pesquisa em fóruns técnicos e análises de hardware revela um problema sistémico nos módulos MQ-135 de baixo custo (PCB azul ou preto) vendidos em plataformas como AliExpress e eBay. Estes módulos incluem frequentemente um circuito comparador (LM393) para saída digital e um resistor de carga ($R_L$) de apenas 1k$\Omega$ (marcado como "102" no componente SMD).

O datasheet da Winsen recomenda explicitamente um $R_L$ entre 10k $\Omega$ e 47k $\Omega$ (com 20k $\Omega$ sendo típico).Com $R_L = 1k\Omega$ e $R_s$ variando tipicamente entre 30k $\Omega$ e 200k $\Omega$:A tensão de saída $V_{out}$ será extremamente baixa.Exemplo: Se $R_s = 100k\Omega$ e $R_L = 1k\Omega$, $V_{out} \approx 5V \times \frac{1}{101} \approx 0.05V$.Esta tensão de 0.05V corresponde a uma leitura de ADC de apenas ~10 (numa escala de 1023). Isto deixa pouquíssima margem para detetar variações, resultando numa resolução péssima e incapacidade de detetar concentrações baixas de gás. O sensor parecerá "insensível" ou morto.

- Identificação: Localize o resistor marcado com "102" conectado entre o pino AOUT e o GND.

- Remoção: Dessolde este resistor. Se não tiver ferramentas de retrabalho SMD, pode-se cortar a trilha ou destruí-lo cuidadosamente com um alicate de corte fino (com risco de danificar a placa).

- Substituição: Solde um resistor convencional (through-hole) de $22k\Omega$ ou $47k\Omega$ entre o pino AOUT e o GND. $22k\Omega$ é frequentemente citado como um valor ideal para sensibilidade equilibrada em ambientes domésticos.   

- Ajuste no Software: O valor exato do novo resistor (ex: 22000 Ohms) deve ser atualizado no código do firmware, sob a variável RLoad.

# 4. Modelagem Matemática
A transformação da resistência elétrica ($R_s$) em concentração de gás (PPM) requer a aplicação de modelos matemáticos derivados das curvas empíricas do datasheet.

## 4.1 Equação de Potência da Sensibilidade
Ao analisar as curvas de sensibilidade (Fig. 3 do datasheet), observa-se que em escala logarítmica (log-log), a relação entre $R_s/R_0$ e PPM é linear. Isto implica uma relação de lei de potência na escala linear:
$$y = a \cdot x^b$$
Onde:
- $y$ é a razão de resistência $\frac{R_s}{R_0}
- $.$x$ é a concentração em PPM.
- $a$ é o coeficiente linear (intercepto).
- $b$ é o coeficiente exponencial (declive da reta no gráfico log-log).

Para encontrar a concentração $x$ (PPM) a partir da resistência medida:$$x = \left( \frac{y}{a} \right)^{\frac{1}{b}} = \left( \frac{R_s/R_0}{a} \right)^{\frac{1}{b}}$$

## 4.2 Determinação das constantes a e b

Diferentes gases têm diferentes curvas, logo, diferentes valores de $a$ e $b$. Estes valores são obtidos através da regressão de pontos extraídos visualmente dos gráficos do datasheet.
Baseado na biblioteca MQUnifiedsensor e análises da comunidade 4, os valores comuns para o MQ-135 são:

<div align="center">

|   Gás Alvo   	|    a    	|    b    	|
|:------------:	|:-------:	|:-------:	|
|      CO2     	| ~110.47 	| ~-2.862 	|
| Amônia (NH3) 	|  ~102.2 	| ~-2.473 	|
|    Benzeno   	|  ~8.47  	|  ~-3.08 	|
|    Álcool    	| ~77.25  	|  ~-3.18 	|

</div>

## 4.3 Calibração ($R_0$)

A variável $R_0$ é a resistência do sensor numa concentração de referência conhecida. O datasheet define $R_0$ como a resistência a 100ppm de $NH_3$ em ar limpo. Como é impraticável para um utilizador doméstico criar uma atmosfera controlada de 100ppm de amônia, utiliza-se um método alternativo: a calibração pelo ar atmosférico limpo.

O ar exterior fresco tem uma composição relativamente estável de $CO_2$ (aprox. 420 ppm atualmente). O gráfico do datasheet mostra a linha de "Ar" (Air) como uma referência quase horizontal (embora na verdade varie ligeiramente).As bibliotecas definem uma constante RatioMQ135CleanAir (razão $R_s/R_0$ em ar limpo). Para o MQ-135, este valor é frequentemente definido como 3.6.

Coloque o sensor em ambiente exterior, longe de poluentes, por 30 minutos.Meça a resistência $R_s$ média (chamemos de $R_{s\_ar\_limpo}$).Sabendo que em ar limpo a razão $\frac{R_s}{R_0} = 3.6$:$$R_0 = \frac{R_{s\_ar\_limpo}}{3.6}$$Armazene este valor de $R_0$ na memória não volátil (EEPROM) do Arduino. Este valor será a base para todos os cálculos futuros de PPM.