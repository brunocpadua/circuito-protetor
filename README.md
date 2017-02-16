# Circuito Temporizador e Controlador de Corrente 
Projeto final da disciplina de Laboratório de Microcontroladores e Aplicações do Departamento de Computação da UFSCar.

## Proposta 
O projeto consiste de um circuito temporizador e controlador de corrente implementado utilizando Arduino, que utiliza um medidor de corrente não invasivo, ou seja, um medidor que não "interrompe" o circuito para fazer a medição, e um relé para o controle do circuito permitindo ou não a passagem da corrente a partir de dados fornecidos pelo usuário, como tempo de funcionamento do aparelho e corrente máxima desejada (A) por meio de uma interface usando pushbuttons e um display LCD.

<img src="https://github.com/brunoinfo/circuito-protetor/blob/master/Imagens/projeto_circuito_v_09_02.jpg" width="500">

### Proposta inicial e mudanças ao longo do projeto

Inicialmente, foi proposto um circuito que apenas mede a corrente atual a partir do sensor não-invasivo, e quando uma corrente máxima pré-definida fosse atingida, o aparelho seria desligado. Com o passar do tempo, com o aprendizado e o aprofundamento das bibliotecas do Arduino, pensamos também em incluir uma função de temporizador para o circuito, algo que julgamos ser de relevância para um circuito do tipo.

### Materiais
**Arduino MEGA 2560:** a plataforma selecionada para o projeto, que utiliza o microcontrolador da Atmel ATmega 2560.
 
 <img src="https://github.com/brunoinfo/circuito-protetor/blob/master/Imagens/arduino-mega.jpg" width="500">

**LCD Keypad Shield:** consiste de um display LCD 16x2 com backlight azul, 5 botões (select,up,down,right,left) além de um botão de reset, utilizado aqui para receber comandos e exibir informações ao usuário.
 
  <img src="https://github.com/brunoinfo/circuito-protetor/blob/master/Imagens/lcd-shield.jpg" width="500">
  
**Módulo Relé:** é um interruptor eletromecânico, servindo para ligar e desligar dispositivos elétricos a partir da comutação de seus contatos elétricos. Aqui, foi ele utilizado em um módulo especial, que contém além do próprio relé outros componentes para ser possível seu funcionamento no Arduino ou facilitar seu uso (transistor, LED's).
 
  <img src="https://github.com/brunoinfo/circuito-protetor/blob/master/Imagens/modulo-rele.jpg" width="500">
  
**Medidor de Corrente não-invasivo (SCT013 - 20A/1V):** sensor utilizado para medir a corrente do aparelho conectado no Circuito Temporizador e Controlador de Corrente. A corrente máxima que pode ser detectada pode atingir 20A sendo esse sinal lido via analógica em uma porta I/O. Além disso por ser um sensor do tipo não invasivo não há necessidade de interromper o circuito para realizar a medição, há apenas a necessidade de envolver um dos fios de energia para medir a corrente. 
 
 
  <img src="https://github.com/brunoinfo/circuito-protetor/blob/master/Imagens/medidor-nao-invasivo.jpg" width="500">
 
**Outros componentes:** resistores, capacitor, cabos, conectores, entre outros

### Implementação
Para o uso do medidor de corrente não-invasivo, foi utilizada a biblioteca emonLib (https://github.com/openenergymonitor/EmonLib), de monitoramento de energia. Com isso, toda a medição fica a cargo da biblioteca, e a leitura é feita a partir de uma única função. Também foi utilizada a biblioteca LiquidCrystal (https://www.arduino.cc/en/Reference/LiquidCrystal), que já vem inclusa na IDE do Arduino para a criação de uma interface para que o usuário possa visualizar informações e configurar seu funcionamento, sem a necessidade de estar ligado com algum computador.

Junto com o shield LCD, temos um pequeno keypad feito por pushbuttons, onde a leitura de qual botão foi pressionado é feita por apenas um pino analógico pela função *leituraBotao*. Isso é possível pois eles estão ligados por resistores formando um divisor de tensão, como mostra a figura abaixo, assim a cada botão pressionado é lido um valor diferente no pino analógico.

  <img src="https://github.com/brunoinfo/circuito-protetor/blob/master/Imagens/shield-lcd-keypads.jpg" width="500">

Com isso, foi possível criar toda uma interface onde é possível entrar com as horas e os minutos que o usuário deseja manter o equipamento ligado, ou ainda escolher uma corrente máxima (em até uma casa decimal) para o funcionamento seguro do mesmo. Outro detalhe importante, é o uso da função *millis()* (https://www.arduino.cc/en/reference/millis) para medir o tempo. Ela retorna o número de milisegundos desde que o Arduino foi ligado, e com isso podemos usar ela para medir o tempo restante da seguinte forma:

*tempoRestante = tempoSetado - (millis() - tempoInicio)*

onde *tempoSetado* guarda o tempo inicialmente desejado pelo usuário, *tempoInicio* o valor que a função *millis* retornou quando o tempo foi setado (isto é, o "horário" que essa configuração foi feita), e *millis()* retorna o "horário". Vale notar que segundo a referência da função *millis()*, esse valor terá *overflow* se o mesmo ficasse ligado por aproximadamente 50 dias.

Finalmente, o relé é quem faz o papel de chave de liga e desliga do equipamento, com base no tempo restante e corrente atual dentro do intervalo permitido. Por fim, todo o circuito foi montado numa prancheta de madeira, para além de facilitar o manuseio, dar um acabamento de produto ao circuito.

### Grupo
 - Bruno Padua
 - João Guilherme Luchetti 
 - Rafael Uryu
