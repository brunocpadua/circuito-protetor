# Circuito Temporizador e Controlador de Corrente 
Projeto final da disciplina de Laboratório de Microcontroladores e Aplicações do Departamento de Computação da UFSCar.

## Proposta 
O projeto consiste de um circuito temporizador e controlador de corrente implementado utilizando Arduino, que utiliza um medidor de corrente não invasivo, ou seja, um medidor que não "interrompe" o circuito para fazer a medição, e um relé para o controle do circuito permitindo ou não a passagem da corrente a partir de dados fornecidos pelo usuário, como tempo de funcionamento do aparelho e corrente máxima desejada (A) por meio de uma interface usando pushbuttons e um display LCD.

<img src="https://github.com/brunoinfo/circuito-protetor/blob/master/Imagens/projeto_circuito_v_09_02.jpg" width="500">

### Proposta inicial e mudanças ao longo do projeto

Inicialmente, foi proposto um circuito que apenas mede a corrente atual a partir do sensor não-invasivo, e quando uma corrente máxima pré-definida fosse atingida, o aparelho seria desligado. Com o passar do tempo, com o aprendidado e o aprofundamento das bibliotecas do Arduino, pensamos também em incluir uma função de temporizador para o circuito, algo que julgamos ser de relevancia para um circuito do tipo.

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

### Grupo
 - Bruno Padua
 - João Guilherme Luchetti 
 - Rafael Uryu
