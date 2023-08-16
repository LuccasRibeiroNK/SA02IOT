<h1>Documentação da Integração do Sistema</h1>

<h2>Visão Geral</h2>

Este documento descreve os passos de configuração e desenvolvimento da integração do sistema, que combina um sensor de temperatura e umidade, LEDs, um display LCD e uma conexão Wi-Fi para monitorar e exibir as leituras em um servidor na nuvem. O código fonte foi desenvolvido utilizando a plataforma Arduino.
Configuração e Desenvolvimento da Integração.

<h3>Passo 1: Configuração Inicial</h3>

    Instale o ambiente de desenvolvimento Arduino IDE (Integrated Development Environment) em sua máquina, caso ainda não esteja instalado.
    Conecte a placa de desenvolvimento Arduino ao computador por meio do cabo USB.

<h3>Passo 2: Importação de Bibliotecas</h3>

    Abra o Arduino IDE.
    No menu "Sketch", selecione a opção "Incluir Biblioteca" > "Gerenciar Bibliotecas".
    Procure e instale as seguintes bibliotecas:
        LiquidCrystal_I2C: Para controle do display LCD utilizando comunicação I2C.
        DHTesp: Biblioteca para interação com o sensor de temperatura e umidade DHT22.
        WiFi: Biblioteca para configuração e estabelecimento de conexão Wi-Fi.
        HTTPClient: Para realizar requisições HTTP ao servidor na nuvem (ThingSpeak, no caso).

<h3>Passo 3: Configuração das Variáveis</h3>

    Abra o código-fonte fornecido no Arduino IDE.
    Altere as seguintes variáveis de acordo com a sua configuração:
        ssid: Nome da rede Wi-Fi à qual o dispositivo deve se conectar.
        password: Senha da rede Wi-Fi.
        dhtPin: Pino ao qual o sensor de temperatura e umidade DHT22 está conectado.
        primeiroLed: Pino ao qual o primeiro LED está conectado.
        segundoLed: Pino ao qual o segundo LED está conectado.
        buzzerPin: Pino ao qual o buzzer está conectado.
        lcdColumns: Número de colunas do display LCD.
        lcdRows: Número de linhas do display LCD.
        url: URL do servidor na nuvem (ThingSpeak) para envio dos dados.

<h3>Passo 4: Configuração do Display LCD</h3>

    Inicialize o display LCD com o endereço correto utilizando o objeto lcd.
    Configure o backlight do display utilizando o método backlight().
    Limpe o display utilizando o método clear().

Passo 5: Configuração do Wi-Fi

    Inicie a conexão Wi-Fi utilizando o método WiFi.begin(ssid, password).
    Aguarde a conexão ser estabelecida utilizando um loop e WiFi.status().

<h3>Passo 6: Leitura e Envio de Dados</h3>

    Utilize o objeto sensor para configurar o sensor de temperatura e umidade.
    Realize a leitura dos valores de temperatura e umidade utilizando sensor.getTemperature() e sensor.getHumidity().

<h3>Passo 7: Requisição HTTP para o Servidor na Nuvem</h3>

    Crie um objeto HTTPClient para realizar a requisição HTTP.
    Construa a URL completa com os valores de temperatura e umidade.
    Utilize o método client.begin(url) para iniciar a requisição.
    Verifique o código de resposta da API utilizando client.GET() e processe a resposta.

<h3>Passo 8: Exibição de Dados no Display LCD e Controle de LEDs/Buzzer</h3>

    Exiba mensagens de boas-vindas no display utilizando o método exibirMensagemBoasVindas().
    Exiba os valores de temperatura e umidade no display LCD utilizando os métodos lcd.setCursor() e lcd.print().
    Controle os LEDs e o buzzer com base nos valores lidos do sensor.

<h3>Passo 9: Loop Principal</h3>

    Repita o loop principal para atualizar as leituras e o envio de dados a intervalos regulares.
    Utilize delay() para definir os intervalos de atualização.

<h3>Passo 10: Testes e Depuração</h3>

    Carregue o código na placa de desenvolvimento utilizando o botão "Upload" no Arduino IDE.
    Monitore a saída serial utilizando o Monitor Serial para verificar mensagens e possíveis erros.

<h3>Conclusão</h3>

Este documento descreveu os passos de configuração e desenvolvimento da integração do sistema, permitindo a monitoração de temperatura e umidade utilizando um sensor DHT22, exibindo os dados em um display LCD, controlando LEDs e um buzzer e enviando os dados para um servidor na nuvem via requisições HTTP. Certifique-se de adaptar as configurações conforme a sua implementação específica.
